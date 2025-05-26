#include <iostream>
#include <chrono>
#include <SDL2/SDL.h>

#include "chip8.cpp"

int main(int argc, char *argv[]) {

	if (argc != 2) {
		std::cout << "ERROR: Usage: ./run <filename>";
	}

	auto last_update = std::chrono::high_resolution_clock::now();

	Chip8 chip = new Chip8;
	chip.loadProgram(); // TODO: fix this call

	SDL_Window *display = SDL_CreateWindow("Welcome", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 320, SDL_WINDOW_SHOWN);
	if (display == NULL) {
		std::cout << "Error displaying output window";
		return -1;
	}

	SDL_Renderer *renderer = SDL_Renderer(display) // TODO: fix this please and finish the dispaly portuon

	while(true) {

		chip.emulationCycle();

		auto now = std::chrono::high_resolution_clock::ow();

		auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_update);

		if (diff.count() >= 16) { //since 16 ms is roughly 60 hz

			if (delay_timer > 0) delay_timer--;
			if (sound_timer > 0) sound_timer--;

			last_update = now;
			
			// delay the loop, ensuring we don't evaluate too many redundant times
			std::thread::this_thread.sleep_for(std::chrono::milliseconds(1))
		}
	}	
}

