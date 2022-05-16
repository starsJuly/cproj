#include "pcap_reader.h"
#include <stdio.h>
#include <ctime>
#include <assert.h>
#include <errno.h>

#ifdef _WIN32
#include <Winsock.h>

void ErrorExit(LPCTSTR lpszFunction);
#define errExit ErrorExit

#else

void errExit(const TCHAR* funcName);

#endif

#define MAGIC_VALUE 0xA1B2C3D4
#define MAGIC_VALUE_2 0xA1B23C4D

PcapReader::PcapReader(const TCHAR *fileName)
	:m_map(fileName), _cur(NULL), 
	_header(NULL), _packet_header(NULL), 
	_packet_data(NULL), _caplen(0)
{
	m_map.map(0, m_map.fileSize(), &m_block);
	_cur = (char*)m_block.base;
}

PcapReader::~PcapReader() {}

void PcapReader::next(size_t step)
{
	_cur += step;
}

int PcapReader::peek(size_t step) {
	char* _peek = _cur + step;
	return ((_peek >= (char*)m_block.base) 
			&& (_peek < (char*)m_block.base + m_block.size));
}

int PcapReader::check_cur()
{
	return peek(0);
}

void PcapReader::pcap_read_pcap_header()
{
	if (!peek(sizeof(pcap_header) - 1)) {
		errExit(TEXT("[pcap_read_pcap_header] pcap header not matcheds"));
	}

	_header = (pcap_header*)_cur;

	next(sizeof(pcap_header));
}

void PcapReader::pcap_read_packet_header()
{
	if (!peek(sizeof(pcap_packet_header) - 1)) {
		errExit(TEXT("[pcap_read_packet_header] packet header not matched"));
	}

	_packet_header = (pcap_packet_header*)_cur;

	uint32_t _sec = get(_packet_header->timestamp._sec), 
			_sec2 = get(_packet_header->timestamp._sec2);
	time_t _stamp = ( (time_t)_sec 
					+ (check_microsecond()? (_sec2/1000000L) : (_sec2 / 1000000000L)) );

	unsigned int msec = (unsigned int)(_sec2 % ( check_microsecond()? 1000000L : 1000000000L) );

	tm *tm = localtime(&_stamp);

	static char buffer[256]{};

	if (tm) {
		strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm);
	}
	else {
#ifdef _WIN32
		sprintf(buffer, "unknown %llX", _stamp);
#else
		sprintf(buffer, "unknown %lX", _stamp);
#endif
	}

	_caplen = get(_packet_header->caplen);
	printf("[%s.%d] %d B\n", buffer, msec, _caplen);

	next(sizeof(pcap_packet_header));
}

void PcapReader::pcap_read_packet_data()
{
	if (!peek(_caplen - 1)) {
		errExit(TEXT("[pcap_read_packet_data] packet data not matched"));
	}
	// TODO
	next(_caplen);
}

int PcapReader::check_magic()
{
	assert(_header);

	return ( MAGIC_VALUE == _header->magic 
			 || MAGIC_VALUE_2 == _header->magic );
}

int PcapReader::check_microsecond()
{
	assert(_header);
	return MAGIC_VALUE == _header->magic;
}

uint32_t PcapReader::get(uint32_t v)
{
	if (check_magic()) {
		return v;
	}

	return (  ((v & 0xff000000)>>24) 
			+ ((v&0x00ff0000)>>12) 
			+ ((v&0x0000ff00)<<12) 
			+ ((v&0x000000ff)<<24) );
}

void PcapReader::pcap_read() {
	pcap_read_pcap_header();
	while (check_cur()) {
		pcap_read_packet_header();
		if (_caplen) pcap_read_packet_data();
	}
}