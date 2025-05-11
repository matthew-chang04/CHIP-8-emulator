#include <fstream>
#include <iostream>

unsigned char chip8_fontset[80] =
{ 
  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
  0x20, 0x60, 0x20, 0x20, 0x70, // 1
  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

class Processor {
	public:
		unsigned short opcode;
		uint8_t memory[4096];

		uint8_t V[16];

		unsigned short I;
		unsigned short p;
		uint16_t stack[16];
		uint16_t sp;

		uint8_t delay_timer;
		uint8_t sound_timer;

		uint8_t display[64 * 32];
		uint8_t key[16];

		void initialize() {
			
			std::fill(std::begin(memory), std::end(memory), 0);
			std::fill(std::begin(stack), std::end(stack), 0);
			std::fill(std::begin(V), std::end(V), 0);
			std::fill(std::begin(key), std::end(key), 0);

			opcode = 0;
			sp = 0;
			I = 0;
			p = 0x200;

			uint8_t mc = 0x50;
			for (int i = 0; i < 80; i++) {
				memory[mc] = chip8_fontset[i];
				mc++;
			}


		}

		void emulationCycle() {

			// Fetch opcode


			// Translate opcode


			// Execute opcode


			// Update Timers
		}

		bool loadGame(std::string& file) {

			std::ifstream game(file, str::ios::binary | str::ios::ate);
			if (!game.isopen()) return false;

			std::streamsize size = game.tellg();
			file.seekg(0, std::ios::beg);

			if (size > 4096 - 0x200) return false;

			game.read(&memory[p], size);
			return true;
		}

}

