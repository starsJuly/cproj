#include "pcap_reader.h"

int main() {
	// Read
	PcapReader reader(TEXT("day3.pcap"));
	Pcap* pcap = reader.pcap_read();
	// Print
	if (pcap) pcap->print();
	// Exit
	delete pcap;
	return 0;
}