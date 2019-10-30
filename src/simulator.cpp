#include <map>
#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <sstream>
#include <fstream>
#include "memory.cpp"

Memory mainMem;

void divideString(const std::vector<int>& v, uint32_t& address);


int main(int argc, char *argv[1] ) {

    std::string binaryFileName = argv[1];
    std::cerr << binaryFileName << std::endl;

    std::ifstream binaries(argv[1], std::ios::binary|std::ios::in);
    binaries.open("/Users/rishil/Desktop/MIPS/MIPS/"+binaryFileName);
    std::vector<char> tempBinaryHolder;

    char temp;

    while(binaries >> temp){
     tempBinaryHolder.push_back(temp);
     std::cout << temp;
  }

  std::vector<int> vectorOfInts; //THIS IS THE BOI YOU WANT TO SPLIT INTO 32 BITS

  for(int i = 0; i < tempBinaryHolder.size(); i++){
    if(tempBinaryHolder[i] == 48){
       vectorOfInts.push_back(0);
    }
    else{
      vectorOfInts.push_back(1);
    }
  }

	uint32_t address = 0x10000000;

  divideString(vectorOfInts, address);

  std::cout << "MEMORY AT 0x10000000 " << mainMem.read_from_memory(0x10000000) << std::endl;
  std::cout << "MEMORY AT 0x10000004 " << mainMem.read_from_memory(0x10000004) << std::endl;
  std::cout << "MEMORY AT 0x10000008 " << mainMem.read_from_memory(0x10000008) << std::endl;

}

void divideString(const std::vector<int>& v, uint32_t& address) {
	std::vector<std::vector<int> > instruction_set;
	for(int i=0; i<v.size(); i+=32) {
		std::vector<int> instruction;
		for(int j=0; j<32; j++) {
			instruction.push_back(v[i+j]);
		}
		instruction_set.push_back(instruction);
	}
	for(int x=0; x<instruction_set.size(); x++) {
		int word=0;
		for(int y=0; y<instruction_set[x].size(); y++) {
			word=word+(instruction_set[x][y]<<(31-y));
		}
		std::cout << word << std::endl;
    mainMem.write_to_memory(word,address);
    address = address + 4;
	}
}
