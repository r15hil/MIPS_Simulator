#include "instructions.hpp"
#include "register.hpp"
#include "memory.hpp"

Toolkit::Toolkit(Memory* mem, Registers* reg) {
	this->regi=reg;
	this->memory=mem;
}

char Toolkit::decode(uint32_t instruction) {
	if((instruction&0b11111100000000000000000000000000)==0) {
		return 'R';
	}else if(((instruction&0b11111100000000000000000000000000)>>26)==1) {
		return 'J';
	}else{
		return 'I';
	}
}

void Toolkit::execute(uint32_t instruction) {
	char type=decode(instruction);
	if(type=='R') {
		rTypeInstruction r(regi, memory);
	}else if(type=='I') {
		iTypeInstruction i(regi, memory);
	}else{
		jTypeInstruction j(regi, memory);
	}
}

void rTypeInstruction::run(uint32_t instruction) {
	int source1=extract_bit32(instruction,6,11);
  int source2=extract_bit32(instruction,11,16);
  int destination=extract_bit32(instruction,16,21);
  int shift=extract_bit32(instruction,21,26);
	int function=extract_bit32(instruction, 26,32);
	switch(function) {
		case 8:
			JR(source1);
			break;
		case 32:
			ADD(source1, source2, destination);
			reg->setPC((reg->getPC())+4);
			break;
		case 33:
		  ADDU(source1, source2, destination);
		  reg->setPC((reg->getPC())+4);
			break;
		case 34:
		  SUB(source1, source2, destination);
			reg->setPC((reg->getPC())+4);
			break;
		case 35:
			SUBU(source1, source2, destination);
			reg->setPC((reg->getPC())+4);
			break;
		case 36:
		  AND(source1, source2, destination);
			reg->setPC((reg->getPC())+4);
			break;
		case 37:
		  OR(source1, source2, destination);
			reg->setPC((reg->getPC())+4);
			break;
		case 38:
	  	XOR(source1, source2, destination);
		  reg->setPC((reg->getPC())+4);
	  	break;
		case 42:
	  	SLT(source1, source2, destination);
	  	reg->setPC((reg->getPC())+4);
		  break;
		case 43:
	  	SLTU(source1, source2, destination);
	  	reg->setPC((reg->getPC())+4);
	  	break;
	}
}

void iTypeInstruction::run(uint32_t instruction) {
	source=extract_bit32(instruction,6,11);
	destination=extract_bit32(instruction,11,16);
	immediateConstant=extract_bit32(instruction,16,32);
	int function=extract_bit32(instruction, 0,6);
	switch(function) {
	 case 8:
     ADDI(source, immediateConstant, destination);
		 reg->setPC((reg->getPC())+4);
		 break;
	 case 9:
	   ADDIU(source, immediateConstant, destination);
		 reg->setPC((reg->getPC())+4);
		 break;
	 case 10:
		 SLTI(source, immediateConstant, destination);
		 reg->setPC((reg->getPC())+4);
		 break;
	 case 11:
	   SLTIU(source, immediateConstant, destination);
		 reg->setPC((reg->getPC())+4);
		 break;
	 case 12:
	   ANDI(source, immediateConstant, destination);
		 reg->setPC((reg->getPC())+4);
		 break;
		case 13:
		 ORI(source, immediateConstant, destination);
		 reg->setPC((reg->getPC())+4);
		 break;
		case 14:
		 XORI(source, immediateConstant, destination);
		 reg->setPC((reg->getPC())+4);
		 break;
	}
}

void jTypeInstruction::run(uint32_t instruction){
  memloc=instruction;
	int function=extract_bit32(instruction, 26,32);
	switch(function) {}
}

rTypeInstruction::rTypeInstruction(Registers* regy, Memory* memy) {
	this->mem = memy;
  this->reg = regy;
	run(memy->read_from_memory(reg->getPC()));
	std::cout << "value in r pc: " << memy->read_from_memory(reg->getPC()) << std::endl;
}

iTypeInstruction::iTypeInstruction(Registers* regy, Memory* memy) {
	this->mem = memy;
  this->reg = regy;
	run(memy->read_from_memory(reg->getPC()));
}

jTypeInstruction::jTypeInstruction(Registers* regy, Memory* memy) {
	this->mem = memy;
  this->reg = regy;
	run(memy->read_from_memory(reg->getPC()));
}

int extract_bit32(const int& binaries, const int& start, const int& end) {
	uint32_t temp_binary=(binaries<<start);
	temp_binary=temp_binary>>(32-(end-start));
	int bin=temp_binary;
	return bin;
}

//////////////////// R TYPE INSTRUCTIONS ////////////////////
void rTypeInstruction::ADD(int source1, int source2, int target){ //overflow if -ve and -ve = 0 or +ve OR +ve and +ve = -ve
  int value;
  value = reg->getReg(source1) + reg->getReg(source2);
  if((reg->getReg(source1) > 0 && reg->getReg(source2) > 0 && value <= 0) || (reg->getReg(source1) < 0 && reg->getReg(source2) < 0 && value >= 0)){
    throw -10;
  }
  reg->setReg(value, target);
}

void rTypeInstruction::ADDU(int source1, int source2, int target){ //R TYPE
    int value;
    value = reg->getReg(source1) + reg->getReg(source2);
    reg->setReg(value, target);
}

void rTypeInstruction::AND(int source1, int source2, int target){
  int value;
  value = reg->getReg(source1) & reg->getReg(source2);
}

void rTypeInstruction::JR(uint32_t source1){ //COULD BE DANGEROUS SINCE IF UINT NOT PASSED IN
	int forward_pc=(reg->getPC())+4;
	int forward_inst=mem->read_from_memory(forward_pc);
	run(forward_inst);
	int new_pc=reg->getReg(source1);
	reg->setPC(new_pc);
}

void rTypeInstruction::OR(int source1, int source2, int target){
  int value;
  value = reg->getReg(source1) | reg->getReg(source2);
  reg->setReg(value, target);
}

void rTypeInstruction::SUB(int source1, int source2, int target){  //overflow if (+A) − (−B) = −C ,,,, (−A) − (+B) = +C
  int value;
  value = reg->getReg(source1) - reg->getReg(source2);
  if((reg->getReg(source1) > 0 && reg->getReg(source2) < 0 && value < 0) || (reg->getReg(source1) < 0 && reg->getReg(source2) > 0 && value > 0)){
    throw -10;
  }
  reg->setReg(value, target);
}

void rTypeInstruction::SUBU(int source1, int source2, int target){
  int value;
  value = reg->getReg(source1) - reg->getReg(source2);
  reg->setReg(value, target);
}

void rTypeInstruction::XOR(int source1, int source2, int target){
  int value;
  value = reg->getReg(source1) ^ reg->getReg(source2);
  reg->setReg(value, target);
}

void rTypeInstruction::SLT(int source1, int source2, int target){
  if(reg->getReg(source1) < reg->getReg(source2)){
    reg->setReg(1, target);
  }
  else{
    reg->setReg(0, target);
  }
}

void rTypeInstruction::SLTU(int source1, int source2, int target){
  if(abs(reg->getReg(source1)) < abs(reg->getReg(source2))){
    reg->setReg(1, target);
  }
  else{
    reg->setReg(0, target);
  }
}

/////////////////// ---------------------////////////////////

/////////////////// I TYPE INSTRUCTIONS ////////////////////

void iTypeInstruction::ADDI(int source1, int immediate, int target){ //overflow if -ve and -ve = 0 or +ve OR +ve and +ve = -ve
  int value;
  value = reg->getReg(source1) + immediate;
  if((reg->getReg(source1) > 0 && immediate > 0 && value <= 0) || (reg->getReg(source1) < 0 && immediate < 0 && value >= 0)){
    throw -10;
  }
  reg->setReg(value, target);
}

void iTypeInstruction::ADDIU(int source1, int immediate, int target){ //I TYPE
    int value;
    value = reg->getReg(source1) + immediate;
    reg->setReg(value, target);
}

void iTypeInstruction::ANDI(int source1, int immediate, int target){
  int value;
  value = reg->getReg(source1) & immediate;
  reg->setReg(value, target);
}

void iTypeInstruction::ORI(int source1, int immediate, int target){
  int value;
  value = reg->getReg(source1) | immediate;
  reg->setReg(value, target);
}

void iTypeInstruction::XORI(int source1, int immediate, int target){
  int value;
  value = reg->getReg(source1) ^ immediate;
  reg->setReg(value, target);
}

void iTypeInstruction::SLTI(int source1, int immediate, int target){
  if(reg->getReg(source1) < immediate){
    reg->setReg(1, target);
  }
  else{
    reg->setReg(0, target);
  }
}

void iTypeInstruction::SLTIU(int source1, int immediate, int target){
  if(abs(reg->getReg(source1)) < abs(immediate)){
    reg->setReg(1, target);
  }
  else{
    reg->setReg(0, target);
  }
}