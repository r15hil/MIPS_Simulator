#include <map>
#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <fstream>
#include "memory.hpp"
#include "instructions.hpp"
#include "register.hpp"

int main(int argc, char *argv[] ) {
  Memory* mainMem = new Memory;
  Registers* registerset = new Registers;
  std::string binaryFileName = argv[1];
  std::cerr << binaryFileName << std::endl;

  std::ifstream binaries(binaryFileName, std::ios::binary|std::ios::ate);


  int size = binaries.tellg();
  char* Char = new char[size];
  binaries.seekg(0, std::ios::beg);
  binaries.read(Char, size);
  binaries.close();

  uint32_t address = 0x10000000;

  for(int i=0; i<size; i++){
    mainMem->write_to_memory(Char[i], address);
    address++;
  }

  delete[] Char;
  Toolkit tool(mainMem, registerset);
  int counter;

  while(registerset->getPC()!=0){
   	uint32_t j=registerset->getPC();
   	uint32_t instruction=mainMem->read_from_memory(j);
    tool.run(instruction);
  	if(registerset->getPC() == 0) {
      std::exit(registerset->getReg(2) & 0xFF);
    }
  }
  std::exit(registerset->getReg(2) & 0xFF);
	delete mainMem;
	delete registerset;
}
