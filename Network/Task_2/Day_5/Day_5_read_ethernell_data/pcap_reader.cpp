#include "pcap_reader.h"
#include <stdio.h>
#include <ctime>
#include <assert.h>
#include <errno.h>
#include <memory.h>

#ifdef _WIN32
#include <Winsock.h>

void ErrorExit(LPCTSTR lpszFunction);
#define errExit ErrorExit

#else

void errExit(const TCHAR* funcName);

#endif

PcapReader::PcapReader(const TCHAR *fileName)
	:m_map(fileName), _cur(NULL), 
	_header(NULL), _packet_header(NULL), 
	_packet_data(NULL), _caplen(0),
	_linktype(0), _pcap(0)
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
	
	_pcap = new Pcap( _header->magic, // keep original value here
					  get(_header->version_major),
					  get(_header->version_minor),
					  get(_header->thiszone),
					  get(_header->sigfigs),
					  get(_header->snaplen),
					  (_linktype = get(_header->linktype)) );
	next(sizeof(pcap_header));
}

void PcapReader::pcap_read_packet_header()
{
	if (!peek(sizeof(pcap_packet_header) - 1)) {
		errExit(TEXT("[pcap_read_packet_header] packet header not matched"));
	}

	_packet_header = (pcap_packet_header*)_cur;

	_caplen = get(_packet_header->caplen);

	next(sizeof(pcap_packet_header));
}

void PcapReader::pcap_read_packet_data()
{
	if (!peek(_caplen - 1)) {
		errExit(TEXT("[pcap_read_packet_data] packet data not matched"));
	}

	PcapPacket* packet = PcapPacketFactory::getPacket(_linktype);

	if (packet == NULL) {
		errExit(TEXT("[pcap_read_packet_data] unknown packet data"));
	}

	packet->init( get(_packet_header->timestamp._sec), 
				  get(_packet_header->timestamp._sec2), 
				  get(_packet_header->caplen), 
				  get(_packet_header->orilen), 
				  (_packet_data = _cur) );

	_pcap->appendPacket(packet);

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

Pcap* PcapReader::pcap_read() {
	if (_pcap) return _pcap;
	pcap_read_pcap_header();
	
	while (check_cur()) {
		pcap_read_packet_header();
		if (_caplen) pcap_read_packet_data();
	}
	return _pcap;
}

PcapPacket::PcapPacket():header(), data(NULL) {}

void PcapPacket::print() const
{
	printHeader();
	printf("\t");
	printData();
}

PcapPacket::~PcapPacket()
{
	if (data) delete []data;
}

void PcapPacket::init(uint32_t sec, uint32_t sec2, uint32_t caplen, uint32_t orilen, char* data)
{
	header.timestamp._sec = sec;
	header.timestamp._sec2 = sec2;
	header.caplen = caplen;
	header.orilen = orilen;
	this->data = new char[caplen];
	memcpy(this->data, data, caplen);
}

void PcapPacket::printHeader(bool isNano) const
{

	time_t _stamp = ((time_t)header.timestamp._sec);

	unsigned int msec = header.timestamp._sec2;

	tm* tm = localtime(&_stamp);

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

	printf("[%s.%.*d] %d B", buffer, (isNano ? 9 : 6), msec, header.caplen);
}

void PcapPacket::printData() const
{
	char* cur = data,
		* end = data + header.caplen;
	while (cur != end) {
		printf("%.2hhX", *cur);
		++cur;
	}
}

Pcap::Pcap( uint32_t magic, uint16_t major, 
			uint16_t minor, uint32_t thiszone, 
			uint32_t sigfigs, uint32_t snaplen, 
			uint32_t linktype) 
	: header{ magic, major, 
			  minor, thiszone, 
			  sigfigs, snaplen, 
			  linktype }, packets() {}

Pcap::~Pcap()
{
	auto iter = packets.begin();
	while (iter != packets.end()) {
		delete* iter;
		++iter;
	}
}

void Pcap::appendPacket(PcapPacket* packet)
{
	packets.push_back(packet);
}

void Pcap::print()
{
#ifdef _WIN64
	printf("The number of packets: %llu\n", packets.size());
#else
	printf("The number of packets: %lu\n", packets.size());
#endif
	auto iter = packets.begin();
	while (iter!=packets.end()) {
		(*iter)->print();
		printf("\n");
		++iter;
	}
}
