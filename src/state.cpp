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

uint16_t Memory::read16(uint16_t address) const {
    uint8_t low = read(address);
    uint8_t high = read(address + 1);
    return (high << 8) | low;
}

// REGISTERS

Registers::Registers() : B(0), C(0), D(0), E(0), H(0), L(0), A(0), F(0) {}

void Registers::setFlags(uint16_t result) {
    if ((uint8_t)result == 0x0) { // Zero flag
        F |= 0b10000;
    } else {
        F &= ~0b10000;
    }
    if (((uint8_t)result & 0b10000000) >> 7 ==  0b1) { // Sign flag, most significant bit set
        F |= 0b01000;
    } else {
        F &= ~0b01000;
    }
    if (std::popcount((uint8_t)result) % 2 == 0) { // Parity flag, modulo 2 sum of bits is zero 
        F |= 0b00100; 
    } else {
        F &= ~0b00100; 
    }
    if (result > UINT8_MAX) { // Carry flag
        F |= 0b00010;
    } else {
        F &= ~0b00010;
    }
}

void Registers::setFlagsADD(uint16_t result, uint8_t a, uint8_t b, bool carry) {
    setFlags(result); // Zero, Sign, and Parity flags
    if (((a & 0x0F) + (b & 0x0F) + 0b1*carry) > 0xF) { // AuxCarry flag
        F |= 0b00001;
    } else {
        F &= ~0b00001;
    }
}

void Registers::setFlagsSUB(uint16_t result, uint8_t a, uint8_t b, bool borrow) {
    setFlags(result); // Zero, Sign, and Parity flags
    if ((a & 0x0F) < ((b & 0x0F) + 0b1 * borrow)) { // AuxCarry flag
        F |= 0b00001;
    } else {
        F &= ~0b00001;
    }
}


uint8_t Registers::getZero() {return (F & 0b10000) >> 4;}
uint8_t Registers::getCarry() {return (F & 0b1000) >> 3;}
uint8_t Registers::getSign() {return (F & 0b100) >> 2;}
uint8_t Registers::getParity() {return (F & 0b10) >> 1;}
uint8_t Registers::getAuxCarry() {return F & 0b1;}

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