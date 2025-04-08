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

void Registers::setFlags(uint8_t result) {
    if (result == 0x0) {F |= 0b10000;} // Zero flag
    if ((result & 0b10000000) >> 7 ==  0b1) {F |= 0b01000;} // Sign flag, most significant bit set
    if (std::popcount(result) % 2 == 0) { // Parity flag, modulo 2 sum of bits is zero 
        F |= 0b00100; // set bit
    } else {
        F &= ~0b00100; // reset bit
    }
}

uint8_t Registers::getZero() {return (F & 0b10000) >> 4;}
uint8_t Registers::getCarry() {return (F & 0b1000) >> 3;}
uint8_t Registers::getSign() {return (F & 0b100) >> 2;}
uint8_t Registers::getParity() {return (F & 0b10) >> 1;}
uint8_t Registers::getAuxCarry() {return F & 0b1;}

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

uint16_t Registers::readRP(uint8_t code) {
    switch (code) {
        case 0b00:
            return readBC();
        case 0b01:
            return readDE();
        case 0b10:
            return readHL();
        case 0b11:
            return SP;
        default:
            std::cerr << "Unused RP code: 0x" << std::hex << code << std::endl;
            exit(1);
    }
}

void Registers::setRP(uint8_t code, uint16_t value) {
    switch (code) {
        case 0b00:
            setBC(value);
            break;
        case 0b01:
            setDE(value);
            break;
        case 0b10:
            setHL(value);
            break;
        case 0b11:
            SP = value;
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