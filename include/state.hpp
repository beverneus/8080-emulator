#pragma once

#include <cstdint>
#include <iostream>

class Memory {
    uint8_t data[0x4000] = {0};
    public:
    void write(uint16_t address, uint8_t value);
    uint8_t read(uint16_t address) const;
    uint16_t read16(uint16_t address) const;
};

class Registers
{
    uint16_t readPair(uint8_t high, uint8_t low);
    void setPair(uint8_t *high, uint8_t *low, uint16_t value);

    public:
        Registers();

        uint8_t B, C, D, E, H, L; // addressable in pairs B,C; D,E; H,L
        uint8_t A; // Accumulator
        uint8_t F; // Flag register, 5 bits: zero, carry, sign, parity and auxiliary carry
        uint16_t PC, SP; // Program counter, stack pointer

        uint8_t* getSingleRegister(uint8_t code);

        uint16_t readRP(uint8_t code);
        void setRP(uint8_t code, uint16_t value);

        uint16_t readBC() { return readPair(B, C); };
        void setBC(uint16_t value) { setPair(&B, &C, value); }

        uint16_t readDE() { return readPair(D, E); };
        void setDE(uint16_t value) { setPair(&D, &E, value); }

        uint16_t readHL() { return readPair(H, L); };
        void setHL(uint16_t value) { setPair(&H, &L, value); }
};
