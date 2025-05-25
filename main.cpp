#include <iostream>
#include <chrono>

#include "chip8.cpp"

int main(int argc, char *argv[]) {
	Chip8 chip = new Chip8;

	chip.loadProgram(//...//);
	chip.emulationCycle();

	
}
