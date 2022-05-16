#include "pcap_reader.h"

int main() {
	PcapReader reader(TEXT("day3.pcap"));
	reader.pcap_read();
	return 0;
}