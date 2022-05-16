#ifndef PACKET_DATA_READER_H_
#define PACKET_DATA_READER_H_

/// Provide interface for parsing packet
/// data from pcap file
class PacketDataParser {
public:
	virtual ~PacketDataParser() = 0;
	virtual void parse(void* data, size_t size)const = 0;

};


#endif