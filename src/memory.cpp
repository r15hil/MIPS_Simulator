#include <iostream>
#include <map>

class Memory{
public:
	Memory();
	void write_to_memory(const int& value, const uint32_t& address);
	int read_from_memory(const uint32_t& address);
	bool in_memory(const uint32_t& address);
	//friend class Registers;

private:
	std::map<uint32_t,char> MMmap;
	static const uint32_t ADDR_NULL=0x00000000;
	static const uint32_t ADDR_NULL_END=0x00000004;
	//0x00000004 ~ 0x10000000: length 0xFFFFFFC
	static const uint32_t ADDR_INSTR=0x10000000;
	//0x10000000 ~ 0x11000000: length 0x1000000
	static const uint32_t ADDR_INSTR_END=0x11000000;
	//0x11000000 ~ 0x20000000: length=0xF000000
	static const uint32_t ADDR_DATA=0x20000000;
	static const uint32_t ADDR_DATA_END=0x24000000;
	//0x24000000 ~ 0x30000000: length=0xC000000
	static const uint32_t ADDR_GETC=0x30000000;
	static const uint32_t ADDR_PUTC=0x30000004;
	friend class bit_op;
};

Memory::Memory() {
	MMmap.insert(std::make_pair(ADDR_DATA,0));
}

void Memory::write_to_memory(const int& value, const uint32_t& address) {
	std::cout << "og value is " << value << std::endl;
	int mask0=0xFF000000;
	char val0=(mask0&value)>>24;
	int mask1=0x00FF0000;
	char val1=((mask1&value)<<8)>>24;
	int mask2=0x0000FF00;
	char val2=((mask2&value)<<16)>>24;
	int mask3=0x000000FF;
	char val3=((mask3&value)<<24)>>24;
	if(in_memory(address)) {
		MMmap[address]=val0;
		MMmap[address+1]=val1;
		MMmap[address+2]=val2;
		MMmap[address+3]=val3;
	}else{
		MMmap.insert(std::make_pair(address,val0));
		//std::cout << "In address " << address << " is " << +MMmap[address] << std::endl;
		MMmap.insert(std::make_pair(address+1,val1));
		//std::cout << "In address " << address+1 << " is " << +MMmap[address+1] << std::endl;
		MMmap.insert(std::make_pair(address+2,val2));
		//std::cout << "In address " << address+2 << " is " << +MMmap[address+2] << std::endl;
		MMmap.insert(std::make_pair(address+3,val3));
		//std::cout << "In address " << address+3 << " is " << +MMmap[address+3] << std::endl;
	}
}

int Memory::read_from_memory(const uint32_t& address) {
	int val0=MMmap[address]<<24;
	//std::cout << std::bitset<32>(val0) << std::endl;
	int val1=(MMmap[address+1]<<16)&0x00FFFFFF;
	//val1=val1&0x00FFFFFF;
	//std::cout << std::bitset<32>(val1) << std::endl;
	int val2=(MMmap[address+2]<<8)&0x0000FFFF;
	//val2=val2&0x0000FFFF;
	//std::cout << std::bitset<32>(val2) << std::endl;
	int val3=(MMmap[address+3])&0x000000FF;
	//val3=val3&0x000000FF;
	//std::cout << std::bitset<32>(val3) << std::endl;
	int word=val0+val1+val2+val3;
	return word;
}

bool Memory::in_memory(const uint32_t& address) {
	if(MMmap.find(address)==MMmap.end()) {
		return false;
	}
	return true;
}
