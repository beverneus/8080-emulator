#pragma once

#include <fstream>
#include <iostream>

#include "state.hpp"

class Cpu {
    uint8_t opcode = 0x0;
    Registers regs;
    public: Memory memory;

    public:
        int loadRom(const char* path);
        void decode();
};