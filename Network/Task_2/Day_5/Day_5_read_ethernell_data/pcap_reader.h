#ifndef PCAP_READER_H_
#define PCAP_READER_H_

#include "filemapping.h"
#include <vector>

// Magic number value

#define MAGIC_VALUE 0xA1B2C3D4
#define MAGIC_VALUE_2 0xA1B23C4D

// Link type 

#define LINKTYPE_NULL
#define LINKTYPE_ETHERNET 1
#define LINKTYPE_AX25
// TODO




/// Pcap 头
struct pcap_header {
	uint32_t magic;				// magic number
	uint16_t version_major;		// version major
	uint16_t version_minor;		// version minor
	uint32_t thiszone;			// gmt to local correction
	uint32_t sigfigs;			// accuracy of timestamps
	uint32_t snaplen;			// maximum length of each packet(octets)
	uint32_t linktype;			// link layer type of packets
};

/// Pcap 包头
struct pcap_packet_header {
	struct {
		uint32_t _sec;			// timestamp(seconds)
		uint32_t _sec2;			// timestamp(microseconds or nanoseconds)
	} timestamp;				// timestamp
	uint32_t caplen;			// captured packet length
	uint32_t orilen;			// original packet length.
};


/// Pcap Packet 类型，包含Packet的信息
class PcapPacket {
public:
	/// PcapPacket构造函数，在调用init函数时再进行初始化
	PcapPacket();
	/// 打印到标准输出
	virtual void print() const final;

	virtual ~PcapPacket();
	/// 初始化函数，初始化Packet头，深复制Packet数据，然后在析构时释放
	virtual void init(uint32_t sec, uint32_t sec2, uint32_t caplen, uint32_t orilen, char* data);
protected:
	/// 打印Packet头信息
	virtual void printHeader(bool isNano = false) const final;
	/// 打印Packet数据信息
	virtual void printData() const;

	pcap_packet_header header;	// packet header
	char* data;					// packet data
};


/// PcapPacket 工厂类，由linktype决定获取对象类型
class PcapPacketFactory {
public:
	/// 创建Packet对象，如果传入不支持的linktype，返回NULL
	static PcapPacket* getPacket(uint32_t linktype);
};


/// Pcap 类型，包含一个Pcap文件的Pcap头、Pcap包的信息
class Pcap {
public:
	Pcap( uint32_t magic, uint16_t major, 
		  uint16_t minor, uint32_t thiszone, 
		  uint32_t sigfigs, uint32_t snaplen, 
		  uint32_t linktype);
	~Pcap();

	void appendPacket(PcapPacket* packet);
	void print();
protected:
	pcap_header header;					// pcap header
	std::vector<PcapPacket*> packets;	// pcap packets
};


/// Pcap Reader类，从Pcap文件读取Pcap信息
class PcapReader {
public:
	/// 构造函数，如果filename文件映射失败会输出错误信息并终止程序
	PcapReader(const TCHAR* fileName);
	~PcapReader();
	/// 读取并解析pcap文件数据，如果成功返回一个Pcap对象，失败会输出错误信息并终止程序
	Pcap* pcap_read();

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

	FileMappingReader m_map;	// filemapping
	FileMappingBlock m_block;	// mapped block of file
	char* _cur;					// cursor

	// cache

	pcap_header* _header;
	pcap_packet_header* _packet_header;
	char* _packet_data;

	uint32_t _caplen;
	uint32_t _linktype;

	// result

	Pcap* _pcap;
};


/// 网络(大端)到本地字节序转换
uint16_t get_ntol(uint16_t);


#endif
