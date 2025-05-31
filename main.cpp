#include <iostream>
#include <chrono>
#include <SDL2/SDL.h>
#include <string>


#include "chip8.cpp"

// each key mapped to the array index
uint8_t keymap[16] = {
	SDLK_x,
	SDLK_1,
	SDLK_2,
	SDLK_3,
	SDLK_q,
	SDLK_w,
	SDLK_e,
	SDLK_a,
	SDLK_s,
	SDLK_d,
	SDLK_z,
	SDLK_c,
	SDLK_4,
	SDLK_r,
	SDLK_f,
	SDLK_v
}

int main(int argc, char *argv[]) {

	if (argc != 2) {
		std::cout << "ERROR: Usage: ./run <filename>";
		return -2;
	}
	
	// Set up chip and load specified file to memory
	Chip8 chip(); 

	std::string program = argv[1];
	if (chip.loadProgram(program)) { 
		std::cout << "ERROR: " << program << " not recognised";
		return -1;
	}

	// SDL display setup

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "ERROR: SDL Init Error";
		return -5;
	}

	SDL_Window *display = SDL_CreateWindow("Welcome", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 320, SDL_WINDOW_SHOWN);
	if (display == nullptr) {
		std::cout << "Error displaying output window";
		return -3;
	}

	SDL_Renderer *renderer = SDL_Renderer(display, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		std::cout << "Error initializing renderer";
		return -4;

	}


	while(true) {

		chip.emulationCycle();

	// TODO: Set up keyboard inputs using SDL_EVENT



		if (chip.draw) {
			int pixel_size = 10;

			for (int i = 0; i < 32; i++) {
				for (int j = 0; j < 64; j++) {

					SDL_Rect pixel = {
						.h = pixel_size;
						.w = pixel_size;
						.x = i * 10;
						.y = j * 10;
					};
					if (chip.display[i][j] == 1) {
						SDL_SetRenderDrawColor(renderer, 0,0,0, 255);
					} else {
						SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					}

					SDL_RenderFillRect(renderer, &pixel); 
				}
			}

			SDL_RenderPresent(renderer);
			chip.draw = false;
		}

		if (delay_timer > 0) { delay_timer-- };
		if (sound_timer > 0) { sound_timer-- };

		SDL_Delay(16);
	}	
}

