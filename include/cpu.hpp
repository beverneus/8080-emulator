#pragma once

#include <fstream>
#include <iostream>
#include <cassert>

#include "state.hpp"

class Cpu {
    Registers regs;
    Memory memory;

    void UnimplementedInstruction();

    uint16_t read16atPC(); // read next two bytes and increment PC twice

    public:
        int loadRom(const char* path);
        int decode();
};