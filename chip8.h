#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

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

		Processor()
		{	
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
			opcode = memory[pc] << 8 | memory[pc+1];

			switch(opcode & 0xF000){

				case(0x0): 
					switch(opcode & 0x0F00) {
						case(0x0):
							//...//
					}
					break;

				case(0x1000):
					pc = opcode & 0x0FFF;
					break;

				case(0x2000):
					stack[sp] = pc;
					sp++;
					pc = opcode & 0x0FFF;
					break;

				case(0x3000): // 3XNN
					int x = opcode & 0x0F00;
					int n = opcode & 0x00FF;

					if (V[x] == n) {
						pc+= 4;
					}
					break;
				
				case(0x4000):
					short int x = opcode & 0x0F00;
					short int n = opcode & 0x00FF;

					if (V[x] != n) {
						pc += 4;
					}
					break;

				case(0x5000):
					short int x = opcode & 0x0F00;
					short int y = opcode & 0x00F0;

					if (V[x] == V[y]) {
						pc+=4;
					}
					break;

				case(0x6000):
					V[opcode & 0x0F00] = 0x00FF;
					break;

				case(0x7000):
					V[opcode & 0x0F00] += 0x00FF;
					break;

				case(0x8000):
					short int x = opcode & 0x0F00;
					short int y = opcode & 0x00F0;

					switch(opcode & 0x000F) {

						case(0x0000):
							V[x] = V[y];
							break;
						case(0x0001):
							V[x] = V[x] | V[y];
							break;
						case(0x0002):
							V[x] = V[x] & V[y];
							break;
						case(0x0003):
							V[x] = V[x] ^ V[y];
							break;
						case(0x0004): // ***TODO:Adjust both += and -= cases for over and under flow.
							uint8_t temp = V[x];	
							V[x] += V[y];
							V[0xF] = (V[x] < temp) ? 1 : 0;
							break;
						case(0x0005):
							uint8_t temp = V[x];
							V[0xF] = (V[y] > V[x]) ? 1 : 0;
							V[x] -= V[y];
							break;
						case(0x0006):
							V[0xF] = V[x] & 0x1;
							V[x] = V[x] >> 1;
							break;
						case(0x0007):
							uint8_t temp = V[x];
							V[0xF] = (V[x] > V[y]) ? 1 : 0;
							V[x] = V[y] - V[x];
							break;
						case(0x000E):
							V[0xF] = (V[x] & 0x80 == 0x80) ? 1 : 0;
							V[x] = V[x] << 1;
							break;
						default:
							break;
					}

				case(0x9000):

					if (V[x] != V[y]) {
						pc += 4;
					}
					break;

				case(0xA000):

					I = opcode & 0x0FFF;
					break;

				case(0xB000):
					pc = (opcode & 0x0FFF) + V[0];
					break;

				case(0xC000):

					std::random_device rnd;
					std::mt19937 gen(rnd());
					std::uniform_int_distribution<> dist(0,255);

					uint8_t num = static_cast<uint8_t>(dist(gen));
					uint8_t x = opcode & 0x0F00;
					unsigned int NN = opcode & 0x00FF;

					V[x] = num & NN;

					break;

				case(0xD000):
					


			}


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

