# CHIP-8-emulator

## Overview
<p>
  This is my implementation of a simple Chip8 Emulator in C++. I used this project to apply my knowledge of C to C++. I've attached the testing ROM I used, as well as some games to try out.
</p>

## Resources
<p>
  The resources I used include:
</p>
<ul>
  <li>
    <a href="https://tobiasvl.github.io/blog/write-a-chip-8-emulator/"> Guide to making a CHIP-8 emulator by Tobias V. Langhoff
  </li>
  <li>
    <a href="https://en.wikipedia.org/wiki/CHIP-8"> Wikipedia Chip-8 Specifications
  </li>
  <li>
   <a href="https://github.com/kripod/chip8-roms"> kripod's chip-8 ROM collection repo
  </li>
</ul>

## Build
<p>
  Dependencies
</p>

```bash
brew install sdl2
brew install cmake
```

In desired project directory:
```bash
git clone https://github.com/matthew-chang04/CHIP-8-emulator
mkdir build && cd build
cmake ..
make
```

## Run

Now enjoy! I've included some public ROMs I used for testing in the roms directory. The above commands will create a ```CHIP-8-Emulator``` executable.
Remember: The Chip 8 Controls are mapped to the left part of the keyboard. 
