cmake_minimum_required(VERSION 3.15)

project(CHIP-8-Emulator)

set(SOURCES src/main.cpp src/chip8.cpp)

find_package(SDL2 REQUIRED)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(CHIP-8-Emulator PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(CHIP-8-Emulator PRIVATE ${SDL2_LIBRARIES})





