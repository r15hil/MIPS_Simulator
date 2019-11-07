#include <map>
#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <fstream>
#include "memory.hpp"
#include "instructions.hpp"
#include "register.hpp"

//char instructionType(const int& instruction);

int main(int argc, char *argv[] ) {
  Memory* mainMem = new Memory;
  Registers* registerset = new Registers;
  std::string binaryFileName = argv[1];
  std::cerr << binaryFileName << std::endl;

  std::ifstream binaries(binaryFileName, std::ios::binary|std::ios::ate);
  // binaries.open("/Users/rishil/Desktop/MIPS/MIPS/"+binaryFileName);
  // std::vector<char> tempBinaryHolder;

  int size = binaries.tellg();
  char* Char = new char[size];
  binaries.seekg(0, std::ios::beg);
  binaries.read(Char, size);
  binaries.close();

  std::cerr << "Size: " << size << std::endl;

  uint32_t address = 0x10000000;

  for(int i=0; i<size; i++){
    mainMem->write_to_memory(Char[i], address);
    address++;
  }

  delete[] Char;

  ////////////////////////  TESTS /////////////////////////////
  registerset->setReg(10, 2);
  registerset->setReg(0x10000010,4);
  registerset->setReg(15,3);
  ////////////////////////  TESTS /////////////////////////////



	Toolkit tool(mainMem, registerset);
  while((registerset->getPC())<address){
   	uint32_t j=registerset->getPC();
   	uint32_t instruction=mainMem->read_from_memory(j);
		char type=tool.decode(instruction);
   	if(type=='R') {
    	rTypeInstruction rType(registerset, mainMem);
      std::cerr << " did it create?" << std::endl;
   	}else if(type=='J') {
    	jTypeInstruction jType(registerset, mainMem);
   	}else if(type=='I') {
    	iTypeInstruction iType(registerset, mainMem);
   	}
    std::cerr << "hello: "<< registerset->getPC() << std::endl;
  }

  std::cerr << "REGISTER 1: " << registerset->getReg(1) << "--Expected 25" << std::endl;
  std::cerr << "REGISTER 4: " << registerset->getReg(4) << "--Expected next numebr" << std::endl;
  std::cerr << "REGISTER 5: " << registerset->getReg(5) << "--Expected 25" << std::endl;
  std::cerr << "PC: " << registerset->getPC() << std::endl;

	exit(-10);
}
// char instructionType(const int& instruction) {
// 	if((instruction&0b11111100000000000000000000000000)==0) {
// 		return 'R';
// 	}else if(((instruction&0b11111100000000000000000000000000)>>26)==1) {
// 		return 'J';
// 	}else{
// 		return 'I';
// 	}
// }
