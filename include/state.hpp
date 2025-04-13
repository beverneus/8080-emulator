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

        void setFlags(uint16_t result, bool enableZero = 1, bool enableSign = 1, bool enableParity = 1, bool enableCarry = 1);
        void setFlagsADD(uint16_t result, uint8_t a, uint8_t b, bool carry = 0,
                         bool enableZero = 1, bool enableSign = 1, bool enableParity = 1, bool enableCarry = 1, bool enableAuxCarry = 1);
        void setFlagsSUB(uint16_t result, uint8_t a, uint8_t b, bool borrow = 0,
                         bool enableZero = 1, bool enableSign = 1, bool enableParity = 1, bool enableCarry = 1, bool enableAuxCarry = 1);

        uint8_t getZero();
        void setZero();
        void clearZero();

        uint8_t getCarry();
        void setCarry();
        void clearCarry();
        void toggleCarry();

        uint8_t getSign();
        void setSign();
        void clearSign();

        uint8_t getParity();
        void setParity();
        void clearParity();

        uint8_t getAuxCarry();
        void setAuxCarry();
        void clearAuxCarry();

        uint16_t PC, SP; // Program counter, stack pointer

        uint16_t readBC() { return readPair(B, C); };
        void setBC(uint16_t value) { setPair(&B, &C, value); }

        uint16_t readDE() { return readPair(D, E); };
        void setDE(uint16_t value) { setPair(&D, &E, value); }

        uint16_t readHL() { return readPair(H, L); };
        void setHL(uint16_t value) { setPair(&H, &L, value); }
};
