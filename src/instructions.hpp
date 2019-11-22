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
	void run(uint32_t instruction);
	friend class rTypeInstruction;
	friend class iTypeInstruction;
	friend class jTypeInstruction;
private:
	Memory* memory;
	Registers* regi;
};


class rTypeInstruction{
public:
	rTypeInstruction(Registers* regy, Memory* memy);
	void run(uint32_t instruction);

	void SLL(int source2, int shift , int target);
  void SRL(int source2, int shift , int target);
  void SRLV(int source1, int source2, int target);
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
	void MFHI(int destination);
  void MFLO(int destination);
  void MTHI(int source1);
  void MTLO(int source1);
  void DIV(int source1, int source2, int target);
  void DIVU(int source1, int source2, int target);
  void MULT(int source1, int source2, int target);
  void MULTU(int source1, int source2, int target);
  void SLLV(int source1, int source2, int target);
  void SRA(int source1, int source2, int target, int shift);
  void SRAV(int source1, int source2, int target);
  void JALR(int source1, int target);
	friend class Toolkit;

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
  void BEQ(int source1, int immediate, int target);
  void BNE(int source1, int immediate, int target);
  void BGEZ(int source1, int immediate, int target);
  void BGEZAL(int source1, int immediate, int target);
  void BGTZ(int source1, int immediate, int target);
  void BLEZ(int source1, int immediate, int target);
  void BLTZ(int source1, int immediate, int target);
  void BLTZAL(int source1, int immediate, int target);
  void LB(int source1, int immediate, int target);
  void LBU(int source1, int immediate, int target);
  void LH(int source1, int immediate, int target);
  void LHU(int source1, int immediate, int target);
  void LUI(int source1, int immediate, int target);
  void LWL(int source1, int immediate, int target);
  void LWR(int source1, int immediate, int target);
  void SB(int source1, int immediate, int target);
  void SH(int source1, int immediate, int source2);
	friend class Toolkit;
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
	void JAL(int memloc);
    void J(int memloc);

	friend class Toolkit;
private:
  int memloc;
	Memory* mem;
	Registers* reg;
};

#endif
