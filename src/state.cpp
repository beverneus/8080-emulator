#include "state.hpp"

// MEMORY

uint8_t Memory::read(uint16_t address) const {
    if (address >= 0x4000) {
        address = address % 0x4000 + 0x2000;
    }
    return data[address];
}

void Memory::write(uint16_t address, uint8_t value) {
    if (address >= 0x4000) {
        address = address % 0x4000 + 0x2000;
    }
    data[address] = value;
}

// REGISTERS

Registers::Registers() : B(0), C(0), D(0), E(0), H(0), L(0), A(0), F(0) {}

uint8_t* Registers::getSingleRegister(uint8_t code) { // code is a two/three bit code
    switch (code) {
    case 0b111:
        return &A;
    case 0b000:
        return &B;
    case 0b001:
        return &C;
    case 0b010:
        return &D;
    case 0b011:
        return &E;
    case 0b100:
        return &H;
    case 0b101:
        return &L;
    default:
        return nullptr;
    }
}

uint16_t Registers::readPair(uint8_t high, uint8_t low)
{
    uint16_t value = (high << 8) | low;
    return value;
}

void Registers::setPair(uint8_t *high, uint8_t *low, uint16_t value)
{
    *high = value >> 8;
    *low = value & 0x00FF;
}