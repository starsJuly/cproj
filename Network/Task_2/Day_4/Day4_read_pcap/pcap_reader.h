#ifndef PCAP_READER_H_
#define PCAP_READER_H_

#include "filemapping.h"



struct pcap_header {
	uint32_t magic;
	uint16_t version_major;
	uint16_t version_minor;
	uint32_t thiszone;
	uint32_t sigfigs;
	uint32_t snaplen;
	uint32_t linktype;
};

struct pcap_packet_header {
	struct {
		uint32_t _sec;
		uint32_t _sec2;
	} timestamp;
	uint32_t caplen;
	uint32_t orilen;
};

class PcapReader {
public:
	PcapReader(const TCHAR* fileName);
	~PcapReader();
	void pcap_read();

protected:
	void next(size_t step = 1);
	int peek(size_t step = 1);
	int check_cur();
	void pcap_read_pcap_header();
	void pcap_read_packet_header();
	void pcap_read_packet_data();
	int check_magic();
	int check_microsecond();
	uint32_t get(uint32_t v);

	FileMappingReader m_map;
	FileMappingBlock m_block;
	char* _cur;
	pcap_header* _header;
	pcap_packet_header* _packet_header;
	char* _packet_data;
	uint32_t _caplen;
};
#endif
