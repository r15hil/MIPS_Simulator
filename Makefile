simulator:
	g++ src/simulator.cpp src/register.cpp src/memory.cpp src/instructions.cpp -o bin/mips_simulator

testbench:
	chmod u+x bin/mips_testbench
