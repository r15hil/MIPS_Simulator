#include "register.hpp"

Registers::Registers() {
  for(int i = 0; i < 32; i++){
		registers.push_back(0);
	}
	progCounter = 0x10000000;
}

int Registers::getReg(const int& index) {
	return registers[index];
}

void Registers::setReg(const int& value, const int& index) {
	if(index == 0){
		registers[0] = 0;
	}else{
		registers[index]=value;
	}
}

uint32_t Registers::getPC() {
	return progCounter;
}

void Registers::setPC(const uint32_t& setter) {
	progCounter=setter;
}

void Registers::setHi(const int& value) {
	hi=value;
}

int Registers::getHi() {
	return hi;
}

void Registers::setLo(const int& value) {
	lo=value;
}

int Registers::getLo() {
	return lo;
}
