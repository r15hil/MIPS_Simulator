#include "memory.hpp"


 const uint32_t Memory::ADDR_NULL=0x00000000;
 const uint32_t Memory::ADDR_NULL_END=0x00000004;	//0x00000004 ~ 0x10000000: length 0xFFFFFFC
 const uint32_t Memory::ADDR_INSTR=0x10000000;	//0x10000000 ~ 0x11000000: length 0x1000000
 const uint32_t Memory::ADDR_INSTR_END=0x11000000;	//0x11000000 ~ 0x20000000: length=0xF000000
 const uint32_t Memory::ADDR_DATA=0x20000000;
 const uint32_t Memory::ADDR_DATA_END=0x24000000;	//0x24000000 ~ 0x30000000: length=0xC000000
 const uint32_t Memory::ADDR_GETC=0x30000000;
 const uint32_t Memory::ADDR_PUTC=0x30000004;

Memory::Memory() {
	MMmap.insert(std::make_pair(ADDR_DATA,0));

}

void Memory::write_to_memory(const char& value, const uint32_t& address) {
	MMmap[address] = value;
}

int Memory::read_from_memory(const uint32_t& address) {
	int val0=(uint32_t)MMmap[address]<<24;
	int val1=(uint32_t)(MMmap[address+1]<<16)&0x00FFFFFF;
	int val2=(uint32_t)(MMmap[address+2]<<8)&0x0000FFFF;
	int val3=(uint32_t)(MMmap[address+3])&0x000000FF;
	int word=val0+val1+val2+val3;
	return word;
}

bool Memory::in_memory(const uint32_t& address) {
	if(MMmap.find(address)==MMmap.end()) {
		return false;
	}
	return true;
}

int Memory::read_byte(const uint32_t& address) {
    int val=MMmap[address];
    return val;
}
