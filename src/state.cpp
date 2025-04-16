#include "state.hpp"

// MEMORY

uint8_t Memory::read(uint16_t address) const {
    return data[address];
}

void Memory::write(uint16_t address, uint8_t value) {
    data[address] = value;
}

uint16_t Memory::read16(uint16_t address) const {
    uint8_t low = read(address);
    uint8_t high = read(address + 1);
    return (high << 8) | low;
}

// REGISTERS

Registers::Registers() : B(0), C(0), D(0), E(0), H(0), L(0), A(0), F(0), PC(0), SP(0) {}

void Registers::setFlags(uint16_t result, bool enableZero, bool enableSign, bool enableParity, bool enableCarry) {
    if ((uint8_t)result == 0x0 && enableZero) { // Zero flag
        F |= 0b01000000; // 7th bit
    } else {
        F &= ~0b01000000;
    }
    if (((uint8_t)result & 0b10000000 && enableSign) >> 7 ==  0b1) { // Sign flag, most significant bit set
        F |= 0b10000000; // 8th bit
    } else {
        F &= ~0b1000000;
    }
    if (std::popcount((uint8_t)result) % 2 == 0 && enableParity) { // Parity flag, modulo 2 sum of bits is zero 
        F |= 0b00000100; // 3th bit
    } else {
        F &= ~0b00000100; 
    }
    if (result > UINT8_MAX && enableCarry) { // Carry flag
    /*  This is the same for addition and subtraction.
        This is possible because if the addition overflows the 8 bit value it's higher than the 8bit maximum in an 16bit uint.
        And if the subtraction borrows it will underflow and in a 16 bit int will become higher than the 8 bit maximum,
        even if a=0x00 and b=0xFF the result would be 0xFF01, a lot bigger than 0xFF.*/
        F |= 0b00000001;  // 1st bit
    } else {
        F &= ~0b00000001;
    }
}

void Registers::setFlagsADD(uint16_t result, uint8_t a, uint8_t b, bool carry,
                            bool enableZero, bool enableSign, bool enableParity, bool enableCarry, bool enableAuxCarry) {
    setFlags(result, enableZero, enableSign, enableParity, enableCarry); // Zero, Sign, Parity, and Carry flags
    /* Checks if the sum of the two argument's lower nibbles (and if used the carry) is higher than the 8 bit maximum.
       If this is the case the addition overflowed into the higher nibble. */
    if (((a & 0x0F) + (b & 0x0F) + 0b1*carry) > 0xF && enableAuxCarry) { // AuxCarry flag, set if the lower 4 bit overflowed 
        F |= 0b00010000; // 5th bit
    } else {
        F &= ~0b00010000;
    }
}

void Registers::setFlagsSUB(uint16_t result, uint8_t a, uint8_t b, bool borrow,
                            bool enableZero, bool enableSign, bool enableParity, bool enableCarry, bool enableAuxCarry) {
    setFlags(result, enableZero, enableSign, enableParity, enableCarry); // Zero, Sign, Parity and Carry flags
    /* Check if the lower nibble of the first value is smaller than the lower nibble of the second value (if used with borrow).
       If this is the case a bit would've been borrowed from the higher nibble. */
    if ((a & 0x0F) < ((b & 0x0F) + 0b1 * borrow) && enableAuxCarry) { // AuxCarry flag, set if the lower 4 bits borrowed from the higher bits
        F |= 0b00010000; // 5th bit
    } else {
        F &= ~0b00010000;
    }
}


uint8_t Registers::getZero(){return (F & 0b01000000) >> 6;}
void Registers::setZero(){F |= 0b01000000;}
void Registers::clearZero(){F &= ~0b01000000;}

uint8_t Registers::getCarry(){return (F & 0b00000001) >> 0;}
void Registers::setCarry(){F |= 0b00000001;}
void Registers::clearCarry(){F &= ~0b00000001;}
void Registers::toggleCarry(){F ^= 0b00000001;}

uint8_t Registers::getSign(){return (F & 0b10000000) >> 7;}
void Registers::setSign(){F |= 0b10000000;}
void Registers::clearSign(){F &= ~0b10000000;}

uint8_t Registers::getParity(){return (F & 0b00000100) >> 2;}
void Registers::setParity(){F |= 0b00000100;}
void Registers::clearParity(){F &= ~0b00000100;}

uint8_t Registers::getAuxCarry(){return F & 0b00010000 >> 4;}
void Registers::setAuxCarry(){F |= 0b00010000;}
void Registers::clearAuxCarry(){F &= ~0b00010000;}

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