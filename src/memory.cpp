#include "memory.hpp"

Memory::Memory() {
	MMmap.insert(std::make_pair(ADDR_DATA,0));
}

void Memory::write_to_memory(const char& value, const uint32_t& address) {
	MMmap[address] = value;
}

int Memory::read_from_memory(const uint32_t& address) {
	int val0=MMmap[address]<<24;
	int val1=(MMmap[address+1]<<16)&0x00FFFFFF;
	int val2=(MMmap[address+2]<<8)&0x0000FFFF;
	int val3=(MMmap[address+3])&0x000000FF;
	int word=val0+val1+val2+val3;
	return word;
}

bool Memory::in_memory(const uint32_t& address) {
	if(MMmap.find(address)==MMmap.end()) {
		return false;
	}
	return true;
}