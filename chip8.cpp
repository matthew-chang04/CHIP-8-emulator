#include <fstream>
#include <iostream>
#include <random>

#include "chip8.h"

Chip8::Chip8() {
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

void Chip8::emulationCycle() {

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
			} else {
				pc += 2;
			}
			break;
		
		case(0x4000):
			short int x = opcode & 0x0F00;
			short int n = opcode & 0x00FF;

			if (V[x] != n) {
				pc += 4;
			} else {
				pc += 2;
			}
			break;

		case(0x5000):
			short int x = opcode & 0x0F00;
			short int y = opcode & 0x00F0;

			if (V[x] == V[y]) {
				pc+=4;
			} else {
				pc += 2;
			}
			break;

		case(0x6000):
			V[opcode & 0x0F00] = 0x00FF;

			pc += 2;
			break;

		case(0x7000):
			V[opcode & 0x0F00] += 0x00FF;

			pc += 2;
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
				case(0x0004): 
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

			pc += 2;

		case(0x9000):

			if (V[x] != V[y]) {
				pc += 4;
			} else {
				pc += 2;
			}
			break;

		case(0xA000):

			I = opcode & 0x0FFF;

			pc += 2;
			break;

		case(0xB000):
			pc = (opcode & 0x0FFF) + V[0];

			pc += 2;
			break;

		case(0xC000):

			std::random_device rnd;
			std::mt19937 gen(rnd());
			std::uniform_int_distribution<> dist(0,255);

			uint8_t num = static_cast<uint8_t>(dist(gen));
			uint8_t x = opcode & 0x0F00;
			unsigned int NN = opcode & 0x00FF;

			V[x] = num & NN;

			pc += 2;
			break;

		case(0xD000):
			
			uint8_t x = (opcode & 0x0F00) >> 8;
			uint8_t y = (opcode & 0x00F0) >> 4;

			uint8_t n = (opcode & 0x000F);

			uint8_t xPos = V[x];
			uint8_t yPos = V[y];

			V[0xF] = 0;


			for (int row = 0; row < n; row++) {
				uint8_t spriteRow = memory[I + row];

				for (int col = 0; col < 8; col++) {

					if (spriteRow & (0x80 >> col) != 0) {

						int xPix = xPos +col;
						int yPix = yPos + row;

						if (display[yPix][xPix] == 1) {
							V[0xF] = 1;
						}

						display[yPix][xPix] ^= 1;
					}	
				}
			}

			pc += 2;
			break;

		case(0xE000):

			switch(opcode & 0x00F0) {
				uint8_t x = opcode & 0x0F00;

				case(0x0090):
					if (V[x] & 0x0F) {
						pc += 4;
					} else {
						pc += 2;
					}
					break;

				case(0x00A0):
					
					if (!V[x] & 0x0F) {
						pc += 4;
					} else {
						pc += 2;
					}
					break;
			}
			break;

		case(0xF000):

			switch(opcode & 0x00FF) {

				uint8_t x = opcode & 0x0F00;

				case(0x0007):
					V[x] = delay_timer;
					break;

				case(0x000A):
					V[x] = sound_timer;
					break;

				case(0x0015):
					delay_timer = V[x];
					break;

				case(0x0018):
					sound_timer = V[x];
					break;

				case(0x001E):
					I += V[x];
					break;

				case(0x0029):	
					I = 0x50 + (V[x] & 0x0F) * 5;
					break;

				case(0x0033):
					uint8_t val = V[x];

					memory[I] = val / 100;
					memory[I + 1] = (val / 10) % 10;
					memory[I + 2] = val % 10;

					break;
				case(0x0055):
					
					for (int i = 0; i <= x; i++) {
						memory[I + i] = V[i];
					}
					break;

				case(0x0065):
					
					for (int i = 0; i <= x; i++) {
						V[i] = memory[I + i];
					}
					break;
			}
	}
}

bool Chip8::loadProgram(std::string& file) {

	std::ifstream game(file, str::ios::binary | str::ios::ate);
	if (!game.isopen()) return false;

	std::streamsize size = game.tellg();
	file.seekg(0, std::ios::beg);

	if (size > 4096 - 0x200) return false;

	game.read(&memory[p], size);
	return true;
}



