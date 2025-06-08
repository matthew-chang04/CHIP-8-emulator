#include <fstream>
#include <iostream>
#include <random>
#include <array> 

class Chip8 {
	private:
		unsigned short opcode;
		std::array<uint8_t, 4096> memory;

		std::array<uint8_t, 16>  V;

		unsigned short I;
		unsigned short pc;

		std::array<uint16_t, 16> stack;
		uint16_t sp;

	public:
		bool draw;

		std::array<std::array<uint8_t, 64>, 32> display;
		std::array<uint8_t, 16> key;

		bool loadProgram(const std::string&);
		Chip8();
		void emulationCycle();

		uint8_t delay_timer;
		uint8_t sound_timer;
};

