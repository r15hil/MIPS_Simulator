#ifndef INSTRUCTIONS_HPP
#define INSTRUCTIONS_HPP

#include <iostream>
#include "register.hpp"
#include "memory.hpp"
#include "instructions.hpp"

int extract_bit32(const int& binaries, const int& start, const int& end);


class Toolkit{
public:
	Toolkit(Memory* mem, Registers* reg);
	void execute(uint32_t instruction);
	char decode(uint32_t instruction);
	int32_t sign_extend(const int& value, const int& bit_size);
private:
	Memory* memory;
	Registers* regi;
};


class rTypeInstruction{
public:
	rTypeInstruction(Registers* regy, Memory* memy);
	void run(uint32_t instruction);

  void ADD(int source1, int source2, int target);
	void ADDU(int source1, int source2, int target);
	void AND(int source1, int source2, int target);
	void JR(uint32_t source1);
	void OR(int source1, int source2, int target);
	void SUB(int source1, int source2, int target);
	void SUBU(int source1, int source2, int target);
	void XOR(int source1, int source2, int target);
  void SLT(int source1, int source2, int target);
	void SLTU(int source1, int source2, int target);
private:
	Memory* mem;
	Registers* reg;
};

class iTypeInstruction{
public:
	iTypeInstruction(Registers* regy, Memory* memy);
  void run(uint32_t instruction);

	void ADDI(int source1, int immediate, int target);
	void ADDIU(int source1, int immediate, int target);
	void ANDI(int source1, int immediate, int target);
	void ORI(int source1, int immediate, int target);
	void XORI(int source1, int immediate, int target);
	void SLTI(int source1, int immediate, int target);
	void SLTIU(int source1, int immediate, int target);
	void SW(int source1, int immediate, int target);
	void LW(int source1, int immediate, int target);
private:
  int source;
  int destination;
  int immediateConstant;
	Memory* mem;
	Registers* reg;
};

class jTypeInstruction{
public:
	jTypeInstruction(Registers* regy, Memory* memy);
	void run(uint32_t instruction);
private:
  int memloc;
	Memory* mem;
	Registers* reg;
};

#endif
