#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <iostream>
#include <vector>
#include <map>

class Memory{
public:
	Memory();
	void write_to_memory(const char& value, const uint32_t& address);
	int read_from_memory(const uint32_t& address);
	bool in_memory(const uint32_t& address);
    int read_byte(const uint32_t& address);
	friend class Registers;

private:
	std::map<uint32_t,char> MMmap;
	static const uint32_t ADDR_NULL;
	static const uint32_t ADDR_NULL_END;	//0x00000004 ~ 0x10000000: length 0xFFFFFFC
	static const uint32_t ADDR_INSTR;	//0x10000000 ~ 0x11000000: length 0x1000000
	static const uint32_t ADDR_INSTR_END;	//0x11000000 ~ 0x20000000: length=0xF000000
	static const uint32_t ADDR_DATA;
	static const uint32_t ADDR_DATA_END;	//0x24000000 ~ 0x30000000: length=0xC000000
	static const uint32_t ADDR_GETC;
	static const uint32_t ADDR_PUTC;
};

#endif
