#include <stdio.h>
#include <iostream>
#include <fstream>


int main() {
    //LOAD ROM
    const char* path = "../assets/invaders";
    std::ifstream rom(path, std::ios::binary);
    if (rom.fail()) {
        std::cout << "Failed to read rom at: " << path << std::endl;
        return 1;
    }
    uint8_t buffer[0x2000];
    uint16_t address = 0;
    uint8_t byte;
    while(!rom.eof()) {
        rom.read(reinterpret_cast<char*>(&byte), 1);
        buffer[address] = byte;
        address++;
    }
    rom.close();

    std::cout << buffer[0] << std::endl;

    return 0;
}