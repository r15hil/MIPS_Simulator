#ifndef REGISTER_HPP
#define REGISTER_HPP


#include <map>
#include <math.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

class Registers{
public:
	Registers();
	int getReg(const int& index);
	void setReg(const int& value, const int& index);
	void setHi(const int& value);
	void setLo(const int& value);
	int getHi();
	int getLo();
	uint32_t getPC();
	void setPC(const uint32_t&);
	friend class Memory;
	//friend class rTypeInstruction;

private:
	std::vector<int> registers;
	uint32_t progCounter;
	int hi;
	int lo;
};

#endif
