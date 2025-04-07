#include <stdio.h>
#include <iostream>
#include <fstream>

#include "cpu.hpp"

int main() {
    Cpu cpu;

    //LOAD ROM
    const char* path = "../assets/invaders";
    cpu.loadRom(path);
    
    int cycles = 0;

    while (true) {
        if (cycles > 0) {
            cycles--;
            continue;
        }
        cycles = cpu.decode();
        cycles--;
    }
    return 0;
}