#include "cpu.hpp"

int Cpu::loadRom(const char* path) {
    std::ifstream rom(path, std::ios::binary);
    if (rom.fail()) {
        std::cout << "Failed to read rom at: " << path << std::endl;
        return 1;
    }

    uint16_t address = 0;
    uint8_t byte = 0;
    while(!rom.eof()) {
        rom.read(reinterpret_cast<char*>(&byte), 1);
        memory.write(address, byte);
        address++;
    }
    rom.close();
    return 0;
}

void Cpu::decode() {
}