#include "pcap_reader.h"
#include <assert.h>
#include <stdio.h>


uint16_t get_ntol(uint16_t val) {
	static const unsigned char litte[] = { 0xD4, 0xC3, 0xB2, 0xA1 };
	if (*(int*)litte == 0xA1B2C3D4) {
		return ((val & 0xff00) >> 8) + ((val & 0x00Cff) << 8);
	}
	return val;
};

// Ethernet Type

#define ETHERNET_TYPE_IPV4	0x0800
#define ETHERNET_TYPE_ARP	0x0806
#define ETHERNET_TYPE_RARP	0x0835
#define ETHERNET_TYPE_IPV6	0x86DD


// Pcap packet of ethernet
struct pcap_packet_ethernet {
	char dmac[6];
	char smac[6];
	uint16_t type;
	char* playload;
};


// Pcap Ethernet Packet
class PcapPacketEthernet: public PcapPacket {
public:
	~PcapPacketEthernet();
	virtual void init(uint32_t sec, uint32_t sec2, uint32_t caplen, uint32_t orilen, char* data);
	void printMac(char* mac)const;
	void printType(uint16_t type)const;
protected:
	void printData() const;
};


PcapPacket* PcapPacketFactory::getPacket(uint32_t linktype) {
	PcapPacket* packet = NULL;
	switch (linktype) {
	case LINKTYPE_ETHERNET:
		packet = new PcapPacketEthernet();
		break;
	default:;
	}
	return packet;
}


PcapPacketEthernet::~PcapPacketEthernet() {}

void PcapPacketEthernet::init(uint32_t sec, uint32_t sec2, uint32_t caplen, uint32_t orilen, char* data)
{
	PcapPacket::init(sec, sec2, caplen, orilen, data);

	pcap_packet_ethernet* pak = (pcap_packet_ethernet*)this->data;
	pak->type = get_ntol(pak->type);
}

void PcapPacketEthernet::printMac(char *mac)const
{
	assert(mac);
	printf("%.2hhX:%.2hhX:%.2hhX:%.2hhX:%.2hhX:%.2hhX", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

void PcapPacketEthernet::printType(uint16_t type) const
{
	switch (type) {
	case ETHERNET_TYPE_IPV4:
		printf("IPV4");
		break;
	case ETHERNET_TYPE_ARP:
		printf("ARP");
		break;
	case ETHERNET_TYPE_RARP:
		printf("RARP");
		break;
	case ETHERNET_TYPE_IPV6:
		printf("IPV6");
		break;
	default:
		printf("Unknown %X", (uint32_t)type);
	}
}

void PcapPacketEthernet::printData() const
{
	pcap_packet_ethernet* pak = (pcap_packet_ethernet*)data;
	printf("dst ");
	printMac(pak->dmac);
	printf("\tsrc ");
	printMac(pak->smac);
	printf("\t");
	printType(pak->type);
}
