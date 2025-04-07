#pragma once

#include <fstream>
#include <iostream>
#include <cassert>

#include "state.hpp"

class Cpu {
    Registers regs;
    Memory memory;

    void UnimplementedInstruction();

    public:
        int loadRom(const char* path);
        int decode();
};