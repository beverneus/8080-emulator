#include <stdio.h>
#include <iostream>
#include <fstream>

#include "cpu.hpp"

int main() {
    Cpu cpu;

    //LOAD ROM
    const char* path = "../assets/invaders";
    cpu.loadRom(path);

    return 0;
}