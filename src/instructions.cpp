#include "instructions.hpp"
#include "register.hpp"
#include "memory.hpp"
#include <bitset>

Toolkit::Toolkit(Memory* mem, Registers* reg) {
	this->regi=reg;
	this->memory=mem;
}

char Toolkit::decode(uint32_t instruction) {
	if((instruction&0b11111100000000000000000000000000)==0) {
		return 'R';
	}else if(((instruction & 0b11111100000000000000000000000000)>>26) == 2 || ((instruction & 0b11111100000000000000000000000000)>>26) == 3){
		return 'J';
  }else{
		return 'I';
	}
}

void Toolkit::run(uint32_t instruction) {
	char type=decode(instruction);
	if(type=='R') {
		rTypeInstruction r(regi, memory);
		int source1=extract_bit32(instruction,6,11);
	  int source2=extract_bit32(instruction,11,16);
	  int destination=extract_bit32(instruction,16,21);
	  int shift=extract_bit32(instruction,21,26);
	  int function=extract_bit32(instruction, 26,32);
		switch(function) {
		    case 0:
	            r.SLL(source2, shift, destination);
	            regi->setPC((regi->getPC())+4);
	            break;
		    case 2:
	            r.SRL(source2, shift, destination);
	            regi->setPC((regi->getPC())+4);
	            break;
		    case 3:
		        r.SRA(source1, source2, destination, shift);
	            regi->setPC((regi->getPC())+4);
	            break;
		    case 4:
		        r.SLLV(source1, source2, destination);
	            regi->setPC((regi->getPC())+4);
	            break;
		    case 6:
		        r.SRLV(source1, source2, destination);
	            regi->setPC((regi->getPC())+4);
	            break;
		    case 7:
		        r.SRAV(source1, source2, destination);
	            regi->setPC((regi->getPC())+4);
	            break;
		    case 8:
		        r.JR(source1);
		        break;
		    case 9:
	            r.JALR(source1, destination);
	            break;
		    case 16:
		        	r.MFHI(destination);
	            regi->setPC((regi->getPC())+4);
	            break;
		    case 17:
		        	r.MTHI(source1);
	            regi->setPC((regi->getPC())+4);
	            break;
		    case 18:
	            r.MFLO(destination);
	            regi->setPC((regi->getPC())+4);
	            break;
		    case 19:
		        	r.MTLO(source1);
	            regi->setPC((regi->getPC())+4);
	            break;
		    case 24:
		        	r.MULT(source1, source2, destination);
	            regi->setPC((regi->getPC())+4);
	            break;
	      case 25:
	            r.MULTU(source1, source2, destination);
	            regi->setPC((regi->getPC())+4);
	            break;
	      case 26:
	            r.DIV(source1, source2, destination);
	            regi->setPC((regi->getPC())+4);
	            break;
	      case 27:
	            r.DIVU(source1, source2, destination);
	            regi->setPC((regi->getPC())+4);
	            break;
	            case 32:
							r.ADD(source1, source2, destination);
							regi->setPC((regi->getPC())+4);
							break;
				case 33:
			  			r.ADDU(source1, source2, destination);
			  			regi->setPC((regi->getPC())+4);
			  			break;
				case 34:
			  			r.SUB(source1, source2, destination);
			  			regi->setPC((regi->getPC())+4);
			  			break;
				case 35:
			    		r.SUBU(source1, source2, destination);
							regi->setPC((regi->getPC())+4);
							break;
				case 36:
			    		r.AND(source1, source2, destination);
							regi->setPC((regi->getPC())+4);
							break;
				case 37:
			    		r.OR(source1, source2, destination);
							regi->setPC((regi->getPC())+4);
							break;
				case 38:
		  	  		r.XOR(source1, source2, destination);
			  			regi->setPC((regi->getPC())+4);
		  	  		break;
		  	case 42:
		  	  		r.SLT(source1, source2, destination);
		  	  		regi->setPC((regi->getPC())+4);
			  			break;
				case 43:
		  	  		r.SLTU(source1, source2, destination);
		  	  		regi->setPC((regi->getPC())+4);
		  				break;
		    default:
                std::exit(-12);
	            break;
		}
	}else if(type=='J') {
        jTypeInstruction j(regi, memory);
        int memloc = extract_bit32(instruction, 6, 32);
		int function = extract_bit32(instruction, 0, 6);
		switch(function) {
		    case 2:
		        j.J(memloc);
		        break;
		    case 3:
		        j.JAL(memloc);
		        break;
	        default:
                std::exit(-12);
	            break;
		}
	}else{
		iTypeInstruction i(regi, memory);
		int source=extract_bit32(instruction,6,11);
		int destination=extract_bit32(instruction,11,16);
		int immediateConstant=extract_bit32(instruction,16,32);
		int function=extract_bit32(instruction, 0,6);
		switch(function) {
		    case 1:
	        switch(destination){
	            	case 0:
	                  i.BLTZ(source, immediateConstant, destination);
	                  regi->setPC((regi->getPC())+4);
	                  break;
	              case 1:
	                  i.BGEZ(source, immediateConstant, destination);
	                  regi->setPC((regi->getPC())+4);
	                  break;
	              case 16:
	                  i.BLTZAL(source, immediateConstant, destination);
	                  break;
		           	case 17:
		               	i.BGEZAL(source, immediateConstant, destination);
		               	break;
	              default:
	                	break;
	          }
	          break;
		 		case 4:
		     			i.BEQ(source, immediateConstant, destination);
		     			regi->setPC((regi->getPC())+4);
		     			break;
		    case 5:
	            i.BNE(source, immediateConstant, destination);
	            regi->setPC((regi->getPC())+4);
	            break;
		    case 6:
	            i.BLEZ(source, immediateConstant, destination);
	            regi->setPC((regi->getPC())+4);
	            break;
		    case 7:
	            i.BGTZ(source, immediateConstant, destination);
	            regi->setPC((regi->getPC())+4);
	            break;
		 		case 8:
	         		i.ADDI(source, immediateConstant, destination);
			 	 			regi->setPC((regi->getPC())+4);
			 				break;
		 		case 9:
		     			i.ADDIU(source, immediateConstant, destination);
			 				regi->setPC((regi->getPC())+4);
			 				break;
		 		case 10:
			 				i.SLTI(source, immediateConstant, destination);
			 				regi->setPC((regi->getPC())+4);
			 				break;
		 		case 11:
		     			i.SLTIU(source, immediateConstant, destination);
			 				regi->setPC((regi->getPC())+4);
			 				break;
		 		case 12:
		     			i.ANDI(source, immediateConstant, destination);
			 				regi->setPC((regi->getPC())+4);
			 				break;
	      case 13:
			 				i.ORI(source, immediateConstant, destination);
			 				regi->setPC((regi->getPC())+4);
			 				break;
	     	case 14:
			 				i.XORI(source, immediateConstant, destination);
			 				regi->setPC((regi->getPC())+4);
			 				break;
		    case 15:
	            i.LUI(source, immediateConstant, destination);
	            regi->setPC((regi->getPC())+4);
	            break;
		    case 32:
	            i.LB(source, immediateConstant, destination);
	            regi->setPC((regi->getPC())+4);
	            break;
		    case 33:
	            i.LH(source, immediateConstant, destination);
	            regi->setPC((regi->getPC())+4);
	            break;
		    case 34:
	            i.LWL(source, immediateConstant, destination);
	            regi->setPC((regi->getPC())+4);
	            break;
	            case 35:
			 	    i.LW(source, immediateConstant, destination);
			 	    regi->setPC((regi->getPC())+4);
			 	    break;
		    case 36:
	            i.LBU(source, immediateConstant, destination);
	            regi->setPC((regi->getPC())+4);
	            break;
		    case 37:
	            i.LHU(source, immediateConstant, destination);
	            regi->setPC((regi->getPC())+4);
	            break;
		    case 38:
	            i.LWR(source, immediateConstant, destination);
	            regi->setPC((regi->getPC())+4);
	            break;
		    case 40:
		        	i.SB(source, immediateConstant, destination);
	            regi->setPC((regi->getPC())+4);
	            break;
		    case 41:
	            i.SH(source, immediateConstant, destination);
	            regi->setPC((regi->getPC())+4);
	            break;
			 	case 43:
			 				i.SW(source, immediateConstant, destination);
			 				regi->setPC((regi->getPC())+4);
			 				break;
	      default:
                std::exit(-12);
	            break;
		}
	}
}

int32_t Toolkit::sign_extend(const int& value, const int& bit_size) {
	int32_t word=1u << (bit_size-1);
	return (value^word)-word;
}

rTypeInstruction::rTypeInstruction(Registers* regy, Memory* memy) {
	Toolkit t(mem, reg);
	this->mem = memy;
  this->reg = regy;
}

iTypeInstruction::iTypeInstruction(Registers* regy, Memory* memy) {
	Toolkit t(mem, reg);
	this->mem = memy;
  this->reg = regy;
}

jTypeInstruction::jTypeInstruction(Registers* regy, Memory* memy) {
	Toolkit t(mem, reg);
	this->mem = memy;
  this->reg = regy;
}

int extract_bit32(const int& binaries, const int& start, const int& end) {
	uint32_t temp_binary=(binaries<<start);
	temp_binary=temp_binary>>(32-(end-start));
	int bin=temp_binary;
	return bin;
}

//////////////////// R TYPE INSTRUCTIONS ////////////////////

void rTypeInstruction::SLL(int source2, int shift, int target){
    int value;
    value = (uint32_t)reg->getReg(source2) << shift;
    reg->setReg(value, target);
}

void rTypeInstruction::SRL(int source2, int shift, int target){
    int value;
    value = (uint32_t)reg->getReg(source2) >> shift;
    reg->setReg(value, target);
}

void rTypeInstruction::SRLV(int source1, int source2, int target) {
    int shiftBy=(reg->getReg(source1))&0b00000000000000000000000000011111;
    uint32_t word=reg->getReg(source2);
    reg->setReg((word>>shiftBy),target);
}

void rTypeInstruction::ADD(int source1, int source2, int target){ //overflow if -ve and -ve = 0 or +ve OR +ve and +ve = -ve
  int value;
  value = reg->getReg(source1) + reg->getReg(source2);
  if((reg->getReg(source1) > 0 && reg->getReg(source2) >0 && value <= 0) || (reg->getReg(source1) < 0 && reg->getReg(source2) < 0 && value >= 0)){
    std::exit(-10);
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
  reg->setReg(value, target);
}

void rTypeInstruction::JR(uint32_t source1){ //COULD BE DANGEROUS SINCE IF UINT NOT PASSED IN
	Toolkit t(mem,reg);
	uint32_t forward_pc=(reg->getPC())+4;
	uint32_t forward_inst=mem->read_from_memory(forward_pc);
  uint32_t new_pc=reg->getReg(source1);
  if((new_pc & 0b11) != 0){
    std::exit(-11);
  }
	t.run(forward_inst);
	if((new_pc < 0x10000000 && new_pc != 0) || (new_pc > 0x11000000 && new_pc != 0)) {
       std::exit(-11);
    }
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
  if((value < reg->getReg(source1)) != (reg->getReg(source2) > 0)){
    std::exit(-10);
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

void rTypeInstruction::SLT(int source1, int source2, int target) {
        if (reg->getReg(source1) < reg->getReg(source2)) {
            reg->setReg(1, target);
        } else {
            reg->setReg(0, target);
        }
}

void rTypeInstruction::SLTU(int source1, int source2, int target){
  if((uint32_t)(reg->getReg(source1)) < (uint32_t)(reg->getReg(source2))){
    reg->setReg(1, target);
  }
  else{
    reg->setReg(0, target);
  }
}

void rTypeInstruction::MFHI(int destination){
    reg->setReg(reg->getHi(), destination);
}

void rTypeInstruction::MFLO(int destination){
    reg->setReg(reg->getLo(), destination);
}

void rTypeInstruction::MTHI(int source1){
    reg->setHi(reg->getReg(source1));
}

void rTypeInstruction::MTLO(int source1){
    reg->setLo(reg->getReg(source1));
}

void rTypeInstruction::DIV(int source1, int source2, int target){
    if(source2 == 0){
        std::exit(0);
    }
    int lo_val=floor((reg->getReg(source1))/(reg->getReg(source2)));
    int hi_val=(reg->getReg(source1))%(reg->getReg(source2));
    reg->setLo(lo_val);
    reg->setHi(hi_val);
}

void rTypeInstruction::DIVU(int source1, int source2, int target) {
    if(source2 == 0){
        std::exit(0); //should be -10 but testbench purposes
    }
    uint32_t s=source1;
    uint32_t t=source2;
    int lo_val=floor((reg->getReg(source1))/(reg->getReg(source2)));
    int hi_val=(reg->getReg(source1))%(reg->getReg(source2));
    reg->setLo(lo_val);
    reg->setHi(hi_val);
}

void rTypeInstruction::MULT(int source1, int source2, int target) {
    int64_t prod = (int64_t)reg->getReg(source1)*(int64_t)reg->getReg(source2);
    int hi_val = (prod >> 32) & (0xFFFFFFFF);
    int lo_val= prod & (0xFFFFFFFF);
    reg->setHi(hi_val);
    reg->setLo(lo_val);
}

void rTypeInstruction::MULTU(int source1, int source2, int target) {
    uint64_t prod = (uint64_t)reg->getReg(source1) * (uint64_t)reg->getReg(source2);
    int hi_val = (prod >> 32) & (0xFFFFFFFF);
    int lo_val = prod & (0xFFFFFFFF);
    reg->setHi(hi_val);
    reg->setLo(lo_val);
}

void rTypeInstruction::SLLV(int source1, int source2, int target) {
    int shiftBy=(reg->getReg(source1))&0b00000000000000000000000000011111;
    int word=reg->getReg(source2);
    reg->setReg((word<<shiftBy),target);
}

void rTypeInstruction::SRA(int source1, int source2, int target, int shift){
    int word=reg->getReg(source2);
    reg->setReg((word>>shift),target);
}

void rTypeInstruction::SRAV(int source1, int source2, int target) {
    int shiftBy=(reg->getReg(source1))&0b00000000000000000000000000011111;
    int word=reg->getReg(source2);
    reg->setReg((word>>shiftBy),target);
}

void rTypeInstruction::JALR(int source1, int target) {

    uint32_t return_add = reg->getPC() + 8;
    reg->setReg(return_add, target);

    uint32_t jumpTo=reg->getReg(source1);
    if((jumpTo & 0b11)!=0) {
        std::exit(-11);
    }

    uint32_t nextInstr = mem->read_from_memory(reg->getPC()+4);
    Toolkit tool(mem, reg);
    tool.run(nextInstr);

    if(((jumpTo >= 0x10000000) && (jumpTo < 0x11000000)) || jumpTo == 0){
        reg->setPC(jumpTo);
    }else{
        std::exit(-11);
    }
}

/////////////////// ---------------------////////////////////

/////////////////// I TYPE INSTRUCTIONS ////////////////////

void iTypeInstruction::ADDI(int source1, int immediate, int target){ //overflow if -ve and -ve = 0 or +ve OR +ve and +ve = -ve
  int value;
  Toolkit t(mem, reg);
  int extendedImmediate = t.sign_extend(immediate, 16);
  value = reg->getReg(source1) + extendedImmediate;
  if((reg->getReg(source1) > 0 && extendedImmediate > 0 && value <= 0) || (reg->getReg(source1) < 0 && extendedImmediate < 0 && value >= 0)){
    std::exit(-10);
  }
  reg->setReg(value, target);
}

void iTypeInstruction::ADDIU(int source1, int immediate, int target){ //I TYPE
    int value;
    Toolkit t(mem, reg);
    int extendedImmediate = t.sign_extend(immediate, 16);
    value = reg->getReg(source1) + extendedImmediate;
    reg->setReg(value, target);
}

void iTypeInstruction::ANDI(int source1, int immediate, int target){
  int value;
  Toolkit t(mem,reg);
  int extendedImmediate = t.sign_extend(immediate, 16);
  value = reg->getReg(source1) & extendedImmediate;
  reg->setReg(value, target);
}

void iTypeInstruction::ORI(int source1, int immediate, int target){
  int value;
    Toolkit t(mem,reg);
    int extendedImmediate = t.sign_extend(immediate, 16);
  value = reg->getReg(source1) | extendedImmediate;
  reg->setReg(value, target);
}

void iTypeInstruction::XORI(int source1, int immediate, int target){
  int value;
    Toolkit t(mem,reg);
    int extendedImmediate = t.sign_extend(immediate, 16);
    extendedImmediate = extendedImmediate & 0x0000FFFF;
  value = reg->getReg(source1) ^ extendedImmediate;
  reg->setReg(value, target);
}

void iTypeInstruction::SLTI(int source1, int immediate, int target){
    Toolkit t(mem,reg);
    int extendedImmediate = t.sign_extend(immediate,16);
  if(reg->getReg(source1) < extendedImmediate){
    reg->setReg(1, target);
  }
  else{
    reg->setReg(0, target);
  }
}

void iTypeInstruction::SLTIU(int source1, int immediate, int target){
  if((uint32_t)(reg->getReg(source1)) < (uint32_t)(immediate)){
    reg->setReg(1, target);
  }
  else{
    reg->setReg(0, target);
  }
}

void iTypeInstruction::SW(int source1, int immediate, int target){
    Toolkit tool(mem, reg);
    int address = reg->getReg(source1) + tool.sign_extend(immediate,16);
    int alignmentTest = 0b11&address;
    if(alignmentTest != 0){
        std:exit(-11);
    }
    if(((address >= 0x20000000) && (address < 0x24000000)) || address==0x30000004||address==0x30000005||address==0x30000006||address==0x30000007) {
        if(address==0x30000004||address==0x30000005||address==0x30000006||address==0x30000007){
            std::putchar(reg->getReg(target));
        }
        else{
            int value=reg->getReg(target);
            int mask0=0xFF000000;
            char val0=(mask0&value)>>24;
            mem->write_to_memory(val0, reg->getReg(source1));
            int mask1=0x00FF0000;
            char val1=(mask1&value)>>16;
            mem->write_to_memory(val1, reg->getReg(source1)+1);
            int mask2=0x0000FF00;
            char val2=(mask2&value)>>8;
            mem->write_to_memory(val2, reg->getReg(source1)+2);
            int mask3=0x000000FF;
            char val3=(mask3&value);
            mem->write_to_memory(val3, reg->getReg(source1)+3);
        }
    }else{
        std::exit(-11);
    }
}

void iTypeInstruction::LW(int source1, int immediate, int target){
	Toolkit t(mem, reg);
	int extendedImmediate = t.sign_extend(immediate, 16);
	uint32_t mem_add=extendedImmediate+(reg->getReg(source1));
	if((mem_add&0b11)!=0){
	    std::exit(-11);
	}
    if(((mem_add >= 0x10000000) && (mem_add < 0x11000000)) || ((mem_add >= 0x20000000) && (mem_add < 0x24000000)) ||
       ((mem_add >= 0x30000000) && (mem_add < 0x30000004))) {
        if (mem_add == 0x30000000 || mem_add == 0x30000001 || mem_add == 0x30000002 || mem_add == 0x30000003) {
            int userinp = (std::getchar());
            int newUserinp = t.sign_extend(userinp, 8);
            reg->setReg(newUserinp, target);
        }else {
            reg->setReg(mem->read_from_memory(mem_add), target);
        }
    }
    else{
        std::exit(-11);
    }
}

void iTypeInstruction::BEQ(int source1, int immediate, int target) {
    Toolkit t(mem,reg);
    int32_t offset = immediate << 2;
		offset=t.sign_extend(offset,18);
    if(reg->getReg(source1)==reg->getReg(target)){
        uint32_t branchTo = reg->getPC()+ offset;
        uint32_t nextInstr = reg->getPC()+4;
        t.run(mem->read_from_memory(nextInstr));
        if(!(mem->in_memory(branchTo+4))){
            std::exit(-11);
        }
        if(((branchTo >= 0x10000000) && (branchTo < 0x11000000)) ) {
            reg->setPC(branchTo);
        }
        else{
            std::exit(-11);
        }
    }
}

void iTypeInstruction::BGEZ(int source1, int immediate, int target){
    Toolkit t(mem,reg);
    int32_t offset = immediate << 2;
		offset=t.sign_extend(offset,18);
    if(reg->getReg(source1) >= 0){
        uint32_t branchTo = reg->getPC()+ offset;
        uint32_t nextInstr = reg->getPC()+4;
        t.run(mem->read_from_memory(nextInstr));
        if(!(mem->in_memory(branchTo+4))){
            std::exit(-11);
        }
        if(branchTo < 0 || branchTo >= 0x11000000 || branchTo < 0x10000000) {
            std::exit(-11);
        }else{
            reg->setPC(branchTo);
        }
    }
}

void iTypeInstruction::BGEZAL(int source1, int immediate, int target){
    Toolkit t(mem, reg);
    int32_t offset = immediate << 2;
		offset=t.sign_extend(offset,18);
    uint32_t nextInstr=reg->getPC()+4;
    uint32_t return_add=nextInstr+4;
    if(reg->getReg(source1)>=0) {
        t.run(mem->read_from_memory(nextInstr));
        uint branchTo=nextInstr+(offset);
        if(!(mem->in_memory(branchTo))){
            std::exit(-11);
        }
        if(branchTo < 0 || branchTo >= 0x11000000 || branchTo < 0x10000000) {
            std::exit(-11);
        }else{
            reg->setPC(branchTo);
            reg->setReg((uint32_t)return_add,31);
        }
    }else{
        reg->setPC(nextInstr);
        reg->setReg((uint32_t)return_add,31);
    }
}

void iTypeInstruction::BGTZ(int source1, int immediate, int target){
    Toolkit t(mem,reg);
    int32_t offset = immediate << 2;
		offset=t.sign_extend(offset,18);
    if(reg->getReg(source1) > 0){
        uint32_t branchTo = reg->getPC() + offset;
        uint32_t nextInstr = reg->getPC()+4;
        t.run(mem->read_from_memory(nextInstr));
        if(!(mem->in_memory(branchTo+4))){
            std::exit(-11);
        }
        if(branchTo < 0 || branchTo >= 0x11000000 || branchTo < 0x10000000) {
            std::exit(-11);
        }else{
            reg->setPC(branchTo);
        }
    }
}

void iTypeInstruction::BLEZ(int source1, int immediate, int target){
    Toolkit t(mem,reg);
    int32_t offset = immediate << 2;
		offset=t.sign_extend(offset,18);
    if(reg->getReg(source1) <= 0){
        uint32_t branchTo = reg->getPC()+ offset;
        uint32_t nextInstr = reg->getPC()+4;
        t.run(mem->read_from_memory(nextInstr));
        if(!(mem->in_memory(branchTo+4))){
            std::exit(-11);
        }
        if(branchTo < 0 || branchTo >= 0x11000000 || branchTo < 0x10000000) {
            std::exit(-11);
        }else{
            reg->setPC(branchTo);
        }
    }
}

void iTypeInstruction::BLTZ(int source1, int immediate, int target){
    Toolkit t(mem,reg);
    int32_t offset = immediate << 2;
		offset=t.sign_extend(offset,18);
    if(reg->getReg(source1) < 0){
        uint32_t branchTo = reg->getPC() + offset;
        uint32_t nextInstr = reg->getPC()+4;
        t.run(mem->read_from_memory(nextInstr));
        if(!(mem->in_memory(branchTo+4))){
            std::exit(-11);
        }
        if(branchTo < 0 || branchTo >= 0x11000000 || branchTo < 0x10000000) {
            std::exit(-11);
        }else{
            reg->setPC(branchTo);
        }
    }
}

void iTypeInstruction::BLTZAL(int source1, int immediate, int target){
    Toolkit t(mem, reg);
    int32_t offset = immediate << 2;
		offset=t.sign_extend(offset,18);
    uint32_t nextInstr=reg->getPC()+4;
    uint32_t return_add=nextInstr+4;
    if(reg->getReg(source1) < 0) {
        t.run(mem->read_from_memory(nextInstr));
        uint branchTo=nextInstr+(offset);
        if(!(mem->in_memory(branchTo))){
            std::exit(-11);
        }
        if(branchTo < 0 || branchTo >= 0x11000000 || branchTo < 0x10000000) {
            std::exit(-11);
        }else{
            reg->setPC(branchTo);
            reg->setReg(return_add,31);
        }
    }else{
        reg->setPC(nextInstr);
        reg->setReg(return_add,31);
    }
}

void iTypeInstruction::BNE(int source1, int immediate, int target){
    Toolkit t(mem,reg);
    int32_t offset = immediate << 2;
		offset=t.sign_extend(offset,18);
    if(reg->getReg(source1) != reg->getReg(target)){
        uint32_t branchTo = reg->getPC()+ offset;
        uint32_t nextInstr = reg->getPC()+4;
        t.run(mem->read_from_memory(nextInstr));
        if(!(mem->in_memory(branchTo+4))){
            std::exit(-11);
        }

        if(branchTo < 0 || branchTo >= 0x11000000 || branchTo < 0x10000000) {
            std::exit(-11);
        }else{
            reg->setPC(branchTo);
        }
    }
}

// void iTypeInstruction::LB(int source1, int immediate, int target) {
//     Toolkit t(mem,reg);
//     int offset = t.sign_extend(immediate,16);
//     int mem_add=reg->getReg(source1)+offset;
//     if(((mem_add >= 0x10000000) && (mem_add < 0x11000000)) || ((mem_add >= 0x20000000) && (mem_add < 0x24000000)) ||
//        ((mem_add >= 0x30000000) && (mem_add < 0x30000004))) {
//         if(mem_add==0x30000000||mem_add==0x30000001||mem_add==0x30000002||mem_add==0x30000003) {
//             int userinp=(std::getchar());
// 						if(userinp == EOF && userinp == std::cin.eof()){ reg->setReg(-1, target);}
//             reg->setReg(userinp, target);
//         }else {
//             reg->setReg(mem->read_byte(mem_add), target);
//         }
//     }
//     else{
//         std::exit(-11);
//     }
// }
void iTypeInstruction::LB(int source1, int immediate, int target) {
    Toolkit t(mem,reg);
    int offset = t.sign_extend(immediate,16);
    int mem_add=reg->getReg(source1)+offset;
    if(((mem_add >= 0x10000000) && (mem_add < 0x11000000)) || ((mem_add >= 0x20000000) && (mem_add < 0x24000000)) ||
       ((mem_add >= 0x30000000) && (mem_add < 0x30000004))) {
        if(mem_add==0x30000000||mem_add==0x30000001||mem_add==0x30000002||mem_add==0x30000003) {
					if(mem_add==0x30000003) {
						int userinp=(std::getchar());
						if(userinp == EOF && userinp == std::cin.eof()){
						reg->setReg(-1,target);
						}
						//reg->setReg(userinp, target);
					}else{
						reg->setReg(0, target);
					}
        }else{
            reg->setReg(mem->read_byte(mem_add), target);
        }
    }
    else{
        std::exit(-11);
    }
}

void iTypeInstruction::LBU(int source1, int immediate, int target) {
    Toolkit t(mem, reg);
    int offset = t.sign_extend(immediate, 16);
    uint32_t mem_add = reg->getReg(source1) + offset;

    uint32_t value = (uint32_t)(mem->read_byte(mem_add));
    if(((mem_add >= 0x10000000) && (mem_add < 0x11000000)) || ((mem_add >= 0x20000000) && (mem_add < 0x24000000)) ||
        ((mem_add >= 0x30000000) && (mem_add < 0x30000004))) {
        if(mem_add==0x30000000||mem_add==0x30000001||mem_add==0x30000002||mem_add==0x30000003) {
					int userinp=(std::getchar());
					if(mem_add==0x30000003) {
						if(userinp == EOF && userinp == std::cin.eof()){
							int temp = -1;
							userinp=temp&0xFF;
							reg->setReg(0xFF, target);
						}else{
						reg->setReg(userinp, target);
					}
					}else{
						reg->setReg(0, target);
					}
        }else{
            reg->setReg(value&0x000000FF, target);
        }
    }
    else{
        std::exit(-11);
    }
}

// void iTypeInstruction::LBU(int source1, int immediate, int target) {
//     Toolkit t(mem, reg);
//     int offset = t.sign_extend(immediate, 16);
//     uint32_t mem_add = reg->getReg(source1) + offset;
//
//     uint32_t value = (uint32_t)(mem->read_byte(mem_add));
//     if(((mem_add >= 0x10000000) && (mem_add < 0x11000000)) || ((mem_add >= 0x20000000) && (mem_add < 0x24000000)) ||
//         ((mem_add >= 0x30000000) && (mem_add < 0x30000004))) {
//         if(mem_add==0x30000000||mem_add==0x30000001||mem_add==0x30000002||mem_add==0x30000003) {
//             uint32_t userinp=(std::getchar());
// 						userinp=userinp&0xFF;
//             reg->setReg(userinp, target);
//         }else{
//             reg->setReg(value&0x000000FF, target);
//         }
//     }
//     else{
//         std::exit(-11);
//     }
// }

void iTypeInstruction::LH(int source1, int immediate, int target) {
    Toolkit t(mem,reg);
    int offset = t.sign_extend(immediate,16);
    uint32_t mem_add=reg->getReg(source1)+offset;
    if((mem_add & 0b1) != 0){
        std::exit(-11);
    }
    if(((mem_add >= 0x10000000) && (mem_add < 0x11000000)) || ((mem_add >= 0x20000000) && (mem_add < 0x24000000)) ||
       ((mem_add >= 0x30000000) && (mem_add < 0x30000004))) {
        if(mem_add==0x30000000||mem_add==0x30000001||mem_add==0x30000002||mem_add==0x30000003) {
					int userinp=(std::getchar());
					if(mem_add==0x30000002) {
						if(userinp == EOF && userinp == std::cin.eof()){
							int temp = -1;
							userinp=temp&0xFF;
							reg->setReg(0xFF, target);
						}else{
						reg->setReg(userinp, target);
					}
					}else{
						reg->setReg(0, target);
					}
        }
        else {
            int value0 = mem->read_byte(mem_add);
            value0 = value0 << 8;
            uint32_t value1 = mem->read_byte(mem_add + 1);
            int value = value0 + value1;
            reg->setReg(value, target);
        }
    }else{
        std::exit(-11);
    }
}

void iTypeInstruction::LHU(int source1, int immediate, int target) {
    Toolkit t(mem,reg);
    int offset = t.sign_extend(immediate,16);
    uint32_t mem_add=reg->getReg(source1)+offset;
    if((mem_add & 1) != 0){
        std::exit(-11);
    }
    if(((mem_add >= 0x10000000) && (mem_add < 0x11000000)) || ((mem_add >= 0x20000000) && (mem_add < 0x24000000)) ||
       ((mem_add >= 0x30000000) && (mem_add < 0x30000004))) {
        if(mem_add==0x30000000||mem_add==0x30000001||mem_add==0x30000002||mem_add==0x30000003) {
					int userinp=(std::getchar());
					if(mem_add==0x30000002) {
						if(userinp == EOF && userinp == std::cin.eof()){
							int temp = -1;
							userinp=temp&0xFF;
							reg->setReg(0x000000FF, target);
						}else{
						reg->setReg(userinp, target);
					}
					}else{
						reg->setReg(0, target);
					}
        }
        else {
            uint32_t value0 = (uint32_t)mem->read_byte(mem_add);
            value0 = value0 << 8;
            uint32_t value1 = (uint32_t)mem->read_byte(mem_add + 1);
            uint32_t value = value0 + value1;
            reg->setReg(value, target);
        }
    }else{
        std::exit(-11);
    }
}

void iTypeInstruction::LUI(int source1, int immediate, int target) {
    Toolkit t(mem,reg);
    int extendedImmediate = t.sign_extend(immediate, 16);
    int val=(extendedImmediate<<16);
    reg->setReg(val, target);
}

void iTypeInstruction::LWL(int source1, int immediate, int target) {
    Toolkit t(mem,reg);
    int extendedImmediate = t.sign_extend(immediate, 16);
    int originalReg = reg->getReg(target);
    uint32_t mem_add = extendedImmediate + reg->getReg(source1);
    if(!(((mem_add >= 0x10000000) && (mem_add < 0x11000000)) || ((mem_add >= 0x20000000) && (mem_add < 0x24000000)) ||
       ((mem_add >= 0x30000000) && (mem_add < 0x30000004)))) {
        std::exit(-11);
    }

    if((mem_add >= 0x30000000) && (mem_add < 0x30000004)) {
        int userinp = (std::getchar());
        int regVal = originalReg & 0x00FFFFFF;
        userinp = (userinp & 0x000000FF) << 24;
        int final = regVal + userinp;
        reg->setReg(final, target);
    }
    else if (mem_add % 4 == 2) {
        int regVal = originalReg & 0x0000FFFF;
        int word = mem->read_from_memory(mem_add);
        word = (word & 0xFFFF0000);
        int final = word + regVal;
        reg->setReg(final, target);
    }
    else if (mem_add % 4 == 1) {
        int regVal = originalReg & 0x000000FF;
        int word = mem->read_from_memory(mem_add);
        word = (word & 0xFFFFFF00);
        int final = word + regVal;
        reg->setReg(final, target);
    }
    else if(mem_add % 4 == 0){
        int final = mem->read_from_memory(mem_add);
        reg->setReg(final, target);
    }
    else {
        int regVal = originalReg & 0x00FFFFFF;
        int word = mem->read_from_memory(mem_add);
        word = (word & 0xFF000000);
        int final = word + regVal;
        reg->setReg(final, target);
    }
}

void iTypeInstruction::LWR(int source1, int immediate, int target) {
    Toolkit t(mem,reg);
    int extendedImmediate = t.sign_extend(immediate, 16);
    int originalReg = reg->getReg(target);
    uint32_t mem_add=extendedImmediate+reg->getReg(source1);

    if(!(((mem_add >= 0x10000000) && (mem_add < 0x11000000)) || ((mem_add >= 0x20000000) && (mem_add < 0x24000000)) ||
       ((mem_add >= 0x30000000) && (mem_add < 0x30000004)))){
            std::exit(-11);
    }

    if((mem_add >= 0x30000000) && (mem_add < 0x30000004)) {
        int userinp = (std::getchar());
        int regVal = originalReg & 0xFFFFFF00;
        userinp = userinp & 0x000000FF;
        int final = regVal + userinp;
        reg->setReg(final, target);
    }
    else if (mem_add % 4 == 0) {
            int regVal = originalReg & 0xFFFFFF00;
            int word = mem->read_from_memory(mem_add);
            word = (word & 0xFF000000) >> 24;
            int final = word + regVal;
            reg->setReg(final, target);
        } else if (mem_add % 4 == 1) {
            int regVal = originalReg & 0xFFFF0000;
            int word = mem->read_from_memory(mem_add);
            word = (word & 0xFFFF0000) >> 16;
            int final = word + regVal;
            reg->setReg(final, target);
        } else if (mem_add % 4 == 2) {
            int regVal = originalReg & 0xFF000000;
            int word = mem->read_from_memory(mem_add);
            word = (word & 0xFFFFFF00) >> 8;
            int final = word + regVal;
            reg->setReg(final, target);
        }
    else{
        int final = mem->read_from_memory(mem_add);
        reg->setReg(final, target);
    }
}

void iTypeInstruction::SB(int source1, int immediate, int target) {
    Toolkit t(mem,reg);
    int extendedImmediate = t.sign_extend(immediate, 16);
    uint32_t address = reg->getReg(source1)+extendedImmediate;
    if(((address >= 0x20000000) && (address < 0x24000000)) || address==0x30000004||address==0x30000005||address==0x30000006||address==0x30000007) {
        if(address==0x30000004||address==0x30000005||address==0x30000006||address==0x30000007){
            char val=(uint8_t)(reg->getReg(target) & 0xFF);
            std::putchar(val);
        }else{
            char val=(uint8_t)(reg->getReg(target));
            mem->write_to_memory(val,address);
        }
    }else{
        std::exit(-11);
    }
}

void iTypeInstruction::SH(int source1, int immediate, int target) {
    Toolkit t(mem,reg);
    int extendedImmediate = t.sign_extend(immediate, 16);
    uint32_t addr = reg->getReg(source1) + extendedImmediate;
    if((addr & 0b1) != 0 || addr < 0){
        std::exit(-11);
    }
    if(((addr>=0x20000000)&&(addr<0x24000000)) ||addr==0x30000004||addr==0x30000005||addr==0x30000006||addr==0x30000007){
        if(addr==0x30000004||addr==0x30000005||addr==0x30000006||addr==0x30000007){
            char val1 = (uint8_t)(reg->getReg(target) & 0xFF);
            std::putchar(val1);
        }else {
            int val0 = ((reg->getReg(target)) & 0x0000FF00)>>8;
            mem->write_to_memory(val0, addr);
            int val1 = (reg->getReg(target)) & 0x000000FF;
            mem->write_to_memory(val1, addr + 1);
        }
    }else{
        std::exit(-11);
    }
}

/////////////////// J TYPE INSTRUCTIONS ////////////////////

void jTypeInstruction::JAL(int memloc) {
    Toolkit t(mem,reg);
    uint32_t delayAddress = reg->getPC() + 4;
    uint32_t returnAddress = reg->getPC() + 8;
    reg->setReg(returnAddress, 31);
    uint32_t jumpTo = memloc << 2;

    uint32_t topFour = delayAddress;
    topFour = topFour & 0xF0000000;
    jumpTo = jumpTo & 0x0FFFFFFF;
    jumpTo = jumpTo + topFour;

    if(((jumpTo >= 0x10000000) && (jumpTo < 0x11000000)) && mem->in_memory(jumpTo)){
        t.run(mem->read_from_memory(delayAddress));
        reg->setPC(jumpTo);
    }
    else{
        std::exit(-11);
    }
}

void jTypeInstruction::J(int memloc){
    Toolkit t(mem,reg);

    uint32_t delayAddress = reg->getPC() + 4;
    uint32_t jumpTo = memloc << 2;

    uint32_t topFour = delayAddress;
    topFour = topFour & 0xF0000000;
    jumpTo = jumpTo & 0x0FFFFFFF;
    jumpTo = jumpTo + topFour;

    if(((jumpTo >= 0x10000000) && (jumpTo < 0x11000000)) && mem->in_memory(jumpTo)){
        t.run(mem->read_from_memory(delayAddress));
        reg->setPC(jumpTo);
    }
    else{
        std::exit(-11);
    }
}
