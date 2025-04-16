#include "cpu.hpp"

int Cpu::loadRom(const char* path) {
    std::ifstream rom(path, std::ios::binary);
    if (rom.fail()) {
        std::cout << "Failed to read rom at: " << path << std::endl;
        return 1;
    }

    uint16_t address = 0;
    uint8_t byte = 0;
    while(!rom.eof()) {
        rom.read(reinterpret_cast<char*>(&byte), 1);
        memory.write(address, byte);
        address++;
    }
    rom.close();
    return 0;
}

void Cpu::UnimplementedInstruction() {
    regs.PC--;
    std::cerr << "Unimplemented instruction at: 0x" << std::hex << (int)regs.PC << '\n' << "0x" << std::hex << (int)memory.read(regs.PC) << '\n';
    exit(1);
}

uint16_t Cpu::read16atPC() {
    uint16_t value = memory.read16(regs.PC);
    regs.PC += 2;
    return value;
}

int Cpu::decode() {
    const uint8_t opcode = memory.read(regs.PC);

    std::cout << std::hex << (int)opcode << '\n';

    uint16_t address;
    uint8_t temp8;
    uint16_t temp16;
    uint8_t bit;
    // uint16_t value16;

    regs.PC += 1; // increment PC to avoid repetitive code
    
    switch (opcode) {
        case 0x00: // NOP
            return 4;
        // DATA TRANSFER GROUP
        { // MOV
            // destination B
            case 0x40:
                return 1;
            case 0x41:
                regs.B = regs.C;
                return 1;
            case 0x42:
                regs.B = regs.D;
                return 1;
            case 0x43:
                regs.B = regs.E;
                return 1;
            case 0x44:
                regs.B = regs.H;
                return 1;
            case 0x45:
                regs.B = regs.L;
                return 1;
            case 0x46:
                address = regs.readHL();
                regs.B = memory.read(address);
                return 2;
            case 0x47:
                regs.B = regs.A;
                return 1;
            // destination C
            case 0x48:
                regs.C = regs.B;
                return 1;
            case 0x49:
                return 1;
            case 0x4A:
                regs.C = regs.D;
                return 1;
            case 0x4B:
                regs.C = regs.E;
                return 1;
            case 0x4C:
                regs.C = regs.H;
                return 1;
            case 0x4D:
                regs.C = regs.L;
                return 1;
            case 0x4E:
                address = regs.readHL();
                regs.C = memory.read(address);
                return 2;
            case 0x4F:
                regs.C = regs.A;
                return 1;
            // destination D
            case 0x50:
                regs.D = regs.B;
                return 1;
            case 0x51:
                regs.D = regs.C;
                return 1;
            case 0x52:
                return 1;
            case 0x53:
                regs.D = regs.E;
                return 1;
            case 0x54:
                regs.D = regs.H;
                return 1;
            case 0x55:
                regs.D = regs.L;
                return 1;
            case 0x56:
                address = regs.readHL();
                regs.D = memory.read(address);
                return 2;
            case 0x57:
                regs.D = regs.A;
                return 1;
            // destination E
            case 0x58:
                regs.E = regs.B;
                return 1;
            case 0x59:
                regs.E = regs.C;
                return 1;
            case 0x5A:
                regs.E = regs.D;
                return 1;
            case 0x5B:
                return 1;
            case 0x5C:
                regs.E = regs.H;
                return 1;
            case 0x5D:
                regs.E = regs.L;
                return 1;
            case 0x5E:
                address = regs.readHL();
                regs.E = memory.read(address);
                return 2;
            case 0x5F:
                regs.E = regs.A;
                return 1;
            // destination H
            case 0x60:
                regs.H = regs.B;
                return 1;
            case 0x61:
                regs.H = regs.C;
                return 1;
            case 0x62:
                regs.H = regs.D;
                return 1;
            case 0x63:
                regs.H = regs.E;
                return 1;
            case 0x64:
                return 1;
            case 0x65:
                regs.H = regs.L;
                return 1;
            case 0x66:
                address = regs.readHL();
                regs.H = memory.read(address);
                return 2;
            case 0x67:
                regs.H = regs.A;
                return 1;
            // destination L
            case 0x68:
                regs.L = regs.B;
                return 1;
            case 0x69:
                regs.L = regs.C;
                return 1;
            case 0x6A:
                regs.L = regs.D;
                return 1;
            case 0x6B:
                regs.L = regs.E;
                return 1;
            case 0x6C:
                regs.L = regs.H;
                return 1;
            case 0x6D:
                return 1;
            case 0x6E:
                address = regs.readHL();
                regs.L = memory.read(address);
                return 2;
            case 0x6F:
                regs.L = regs.A;
                return 1;
            // destination memory address in HL
            case 0x70:
                address = regs.readHL();
                memory.write(address, regs.B);
                return 2;
            case 0x71:
                address = regs.readHL();
                memory.write(address, regs.C);
                return 2;        
            case 0x72:
                address = regs.readHL();
                memory.write(address, regs.D);
                return 2;
            case 0x73:
                address = regs.readHL();
                memory.write(address, regs.E);
                return 2;
            case 0x74:
                address = regs.readHL();
                memory.write(address, regs.H);
                return 2;
            case 0x75:
                address = regs.readHL();
                memory.write(address, regs.L);
                return 2;
            case 0x77:
                address = regs.readHL();
                memory.write(address, regs.A);
                return 2;
            // destination A
            case 0x78:
                regs.A = regs.B;
                return 1;
            case 0x79:
                regs.A = regs.C;
                return 1;
            case 0x7A:
                regs.A = regs.D;
                return 1;
            case 0x7B:
                regs.A = regs.E;
                return 1;
            case 0x7C:
                regs.A = regs.H;
                return 1;
            case 0x7D:
                regs.A = regs.L;
                return 1;
            case 0x7E:
                address = regs.readHL();
                regs.A = memory.read(address);
                return 2;
            case 0x7F:
                return 1;
        };        
        { // MVI
            case 0x06:
                regs.B = memory.read(regs.PC++);
                return 2;
            case 0x0E:
                regs.C = memory.read(regs.PC++);
                return 2;
            case 0x16:
                regs.D = memory.read(regs.PC++);
                return 2;
            case 0x1E:
                regs.E = memory.read(regs.PC++);
                return 2;
            case 0x26:
                regs.H = memory.read(regs.PC++);
                return 2;
            case 0x2E:
                regs.L = memory.read(regs.PC++);
                return 2;
            case 0x36:
                temp8 = memory.read(regs.PC++);
                memory.write(regs.readHL(), temp8);
                return 3;
            case 0x3E:
                regs.A = memory.read(regs.PC++);
                return 2;
        };
        { // LXI
            case 0x01:
                regs.setBC(read16atPC());
                return 3;
            case 0x11:
                regs.setDE(read16atPC());
                return 3;
            case 0x21:
                regs.setHL(read16atPC());
                return 3;
            case 0x31:
                regs.SP = read16atPC();
                return 3;
        };
        { // LDA / LDAX
            case 0x0A:
                regs.A = memory.read(regs.readBC());
                return 2;
            case 0x1A:
                regs.A = memory.read(regs.readDE());
                return 2;
            case 0x3A: // LDA
                regs.A = memory.read(read16atPC());
                return 4;
        };
        { // STA / STAX
            case 0x02:
                memory.write(regs.readBC(), regs.A);
                return 2;
            case 0x12:
                memory.write(regs.readDE(), regs.A);
                return 2;
            case 0x32:
                memory.write(read16atPC(), regs.A);
                return 4;
        };
        { // HL stuff
        case 0x2A: // LHLD
            address = read16atPC();
            regs.L = memory.read(address);
            regs.H = memory.read(address+1);
            return 5;
        case 0x22: // SHLD
            address = read16atPC();
            memory.write(address, regs.L);
            memory.write(address+1, regs.H);
            return 5;
        case 0xEB: // XCHG
            temp16 = regs.readHL();
            regs.setHL(regs.readDE());
            regs.setDE(temp16);
            return 1;
        };
        // ARITHMETIC GROUP
        { // ADD
            case 0x80:
                temp16 = regs.A + regs.B;
                regs.setFlagsADD(temp16, regs.A, regs.B);
                regs.A = temp16;
                return 1;
            case 0x81:
                temp16 = regs.A + regs.C;
                regs.setFlagsADD(temp16, regs.A, regs.C);
                regs.A = temp16;
                return 1;
            case 0x82:
                temp16 = regs.A + regs.D;
                regs.setFlagsADD(temp16, regs.A, regs.D);
                regs.A = temp16;
                return 1;
            case 0x83:
                temp16 = regs.A + regs.E;
                regs.setFlagsADD(temp16, regs.A, regs.E);
                regs.A = temp16;
                return 1;
            case 0x84:
                temp16 = regs.A + regs.H;
                regs.setFlagsADD(temp16, regs.A, regs.H);
                regs.A = temp16;
                return 1;
            case 0x85:
                temp16 = regs.A + regs.L;
                regs.setFlagsADD(temp16, regs.A, regs.L);
                regs.A = temp16;
                return 1;
            case 0x86:
                temp16 = regs.A + memory.read(regs.readHL());
                regs.setFlagsADD(temp16, regs.A, memory.read(regs.readHL()));
                regs.A = temp16;
                return 1;
            case 0x87:
                temp16 = regs.A + regs.A;
                regs.setFlagsADD(temp16, regs.A, regs.A);
                regs.A = temp16;
                return 1;
            case 0xC6: // ADI
                temp8 = memory.read(regs.PC++);
                temp16 = regs.A + temp8;
                regs.setFlagsADD(temp16, regs.A, temp8);
                regs.A = temp16;
                return 2;
        };
        { // ADC
            case 0x88:
                temp16 = regs.A + regs.B + regs.getCarry();
                regs.setFlagsADD(temp16, regs.A, regs.B, true);
                regs.A = temp16;
                return 1;
            case 0x89:
                temp16 = regs.A + regs.C + regs.getCarry();
                regs.setFlagsADD(temp16, regs.A, regs.C, true);
                regs.A = temp16;
                return 1;
            case 0x8A:
                temp16 = regs.A + regs.D + regs.getCarry();
                regs.setFlagsADD(temp16, regs.A, regs.D, true);
                regs.A = temp16;
                return 1;
            case 0x8B:
                temp16 = regs.A + regs.E + regs.getCarry();
                regs.setFlagsADD(temp16, regs.A, regs.E, true);
                regs.A = temp16;
                return 1;
            case 0x8C:
                temp16 = regs.A + regs.H + regs.getCarry();
                regs.setFlagsADD(temp16, regs.A, regs.H, true);
                regs.A = temp16;
                return 1;
            case 0x8D:
                temp16 = regs.A + regs.L + regs.getCarry();
                regs.setFlagsADD(temp16, regs.A, regs.L, true);
                regs.A = temp16;
                return 1;
            case 0x8E:
                temp16 = regs.A + memory.read(regs.readHL()) + regs.getCarry();
                regs.setFlagsADD(temp16, regs.A, memory.read(regs.readHL()), true);
                regs.A = temp16;
                return 1;
            case 0x8F:
                temp16 = regs.A + regs.A + regs.getCarry();
                regs.setFlagsADD(temp16, regs.A, regs.A, true);
                regs.A = temp16;
                return 1;
            case 0xCE: // ADI
                temp8 = memory.read(regs.PC++);
                temp16 = regs.A + temp8 + regs.getCarry();
                regs.setFlagsADD(temp16, regs.A, temp8, true);
                regs.A = temp16;
                return 2;
        };
        { // SUB
            case 0x90:
                temp16 = regs.A - regs.B;
                regs.setFlagsSUB(temp16, regs.A, regs.B);
                regs.A = temp16;
                return 1;
            case 0x91:
                temp16 = regs.A - regs.C;
                regs.setFlagsSUB(temp16, regs.A, regs.C);
                regs.A = temp16;
                return 1;
            case 0x92:
                temp16 = regs.A - regs.D;
                regs.setFlagsSUB(temp16, regs.A, regs.D);
                regs.A = temp16;
                return 1;
            case 0x93:
                temp16 = regs.A - regs.E;
                regs.setFlagsSUB(temp16, regs.A, regs.E);
                regs.A = temp16;
                return 1;
            case 0x94:
                temp16 = regs.A - regs.H;
                regs.setFlagsSUB(temp16, regs.A, regs.H);
                regs.A = temp16;
                return 1;
            case 0x95:
                temp16 = regs.A - regs.L;
                regs.setFlagsSUB(temp16, regs.A, regs.L);
                regs.A = temp16;
                return 1;
            case 0x96:
                temp16 = regs.A - memory.read(regs.readHL());
                regs.setFlagsSUB(temp16, regs.A, memory.read(regs.readHL()));
                regs.A = temp16;
                return 1;
            case 0x97:
                temp16 = regs.A - regs.A;
                regs.setFlagsSUB(temp16, regs.A, regs.A);
                regs.A = temp16;
                return 1;
            case 0xD6: // SUI
                temp8 = memory.read(regs.PC++);
                temp16 = regs.A - temp8;
                regs.setFlagsSUB(temp16, regs.A, temp8);
                regs.A = temp16;
                return 2;
        };
        { // SBB
            case 0x98:
                temp16 = regs.A - regs.B - regs.getCarry();
                regs.setFlagsSUB(temp16, regs.A, regs.B, true);
                regs.A = temp16;
                return 1;
            case 0x99:
                temp16 = regs.A - regs.C - regs.getCarry();
                regs.setFlagsSUB(temp16, regs.A, regs.C, true);
                regs.A = temp16;
                return 1;
            case 0x9A:
                temp16 = regs.A - regs.D - regs.getCarry();
                regs.setFlagsSUB(temp16, regs.A, regs.D, true);
                regs.A = temp16;
                return 1;
            case 0x9B:
                temp16 = regs.A - regs.E - regs.getCarry();
                regs.setFlagsSUB(temp16, regs.A, regs.E, true);
                regs.A = temp16;
                return 1;
            case 0x9C:
                temp16 = regs.A - regs.H - regs.getCarry();
                regs.setFlagsSUB(temp16, regs.A, regs.H, true);
                regs.A = temp16;
                return 1;
            case 0x9D:
                temp16 = regs.A - regs.L - regs.getCarry();
                regs.setFlagsSUB(temp16, regs.A, regs.L, true);
                regs.A = temp16;
                return 1;
            case 0x9E:
                temp16 = regs.A - memory.read(regs.readHL()) - regs.getCarry();
                regs.setFlagsSUB(temp16, regs.A, memory.read(regs.readHL()), true);
                regs.A = temp16;
                return 1;
            case 0x9F:
                temp16 = regs.A - regs.A - regs.getCarry();
                regs.setFlagsSUB(temp16, regs.A, regs.A, true);
                regs.A = temp16;
                return 1;
            case 0xDE: // SBI
                temp8 = memory.read(regs.PC++);
                temp16 = regs.A - temp8 - regs.getCarry();
                regs.setFlagsSUB(temp16, regs.A, temp8, true);
                regs.A = temp16;
                return 2;
        }
        { // INR
            case 0x04:
                temp16 = regs.B + 1;
                regs.setFlagsADD(temp16, regs.B, 1, 0, 1, 1, 1, 0, 1);
                regs.B = temp16;
                return 1;
            case 0x0C:
                temp16 = regs.C + 1;
                regs.setFlagsADD(temp16, regs.C, 1, 0, 1, 1, 1, 0, 1);
                regs.C = temp16;
                return 1;
            case 0x14:
                temp16 = regs.D + 1;
                regs.setFlagsADD(temp16, regs.D, 1, 0, 1, 1, 1, 0, 1);
                regs.D = temp16;
                return 1;
            case 0x1C:
                temp16 = regs.E + 1;
                regs.setFlagsADD(temp16, regs.E, 1, 0, 1, 1, 1, 0, 1);
                regs.E = temp16;
                return 1;
            case 0x24:
                temp16 = regs.H + 1;
                regs.setFlagsADD(temp16, regs.H, 1, 0, 1, 1, 1, 0, 1);
                regs.H = temp16;
                return 1;
            case 0x2C:
                temp16 = regs.L + 1;
                regs.setFlagsADD(temp16, regs.L, 1, 0, 1, 1, 1, 0, 1);
                regs.L = temp16;
                return 1;
            case 0x34: // increment memory
                temp16 = memory.read(regs.readHL()) + 1;
                regs.setFlagsADD(temp16, memory.read(regs.readHL()), 1, 0, 1, 1, 1, 0, 1);
                memory.write(regs.readHL(), temp16);
                return 3;
            case 0x3C:
                temp16 = regs.A + 1;
                regs.setFlagsADD(temp16, regs.A, 1, 0, 1, 1, 1, 0, 1);
                regs.A = temp16;
                return 1;
        };
        { // INX, increment 16bit register pair
            case 0x03:
                regs.setBC(regs.readBC() + 1);
                return 1;
            case 0x13:
                regs.setDE(regs.readDE() + 1);
                return 1;
            case 0x23:
                regs.setHL(regs.readHL() + 1);
                return 1;
            case 0x33:
                regs.SP += 1;
                return 1;
        };
        { // DCR
            case 0x05:
                temp16 = regs.B - 1;
                regs.setFlagsSUB(temp16, regs.B, 1, 0, 1, 1, 1, 0, 1);
                regs.B = temp16;
                return 1;
            case 0x0D:
                temp16 = regs.C - 1;
                regs.setFlagsSUB(temp16, regs.C, 1, 0, 1, 1, 1, 0, 1);
                regs.C = temp16;
                return 1;
            case 0x15:
                temp16 = regs.D - 1;
                regs.setFlagsSUB(temp16, regs.D, 1, 0, 1, 1, 1, 0, 1);
                regs.D = temp16;
                return 1;
            case 0x1D:
                temp16 = regs.E - 1;
                regs.setFlagsSUB(temp16, regs.E, 1, 0, 1, 1, 1, 0, 1);
                regs.E = temp16;
                return 1;
            case 0x25:
                temp16 = regs.H - 1;
                regs.setFlagsSUB(temp16, regs.H, 1, 0, 1, 1, 1, 0, 1);
                regs.H = temp16;
                return 1;
            case 0x2D:
                temp16 = regs.L - 1;
                regs.setFlagsSUB(temp16, regs.L, 1, 0, 1, 1, 1, 0, 1);
                regs.L = temp16;
                return 1;
            case 0x35: // decrease memory
                temp16 = memory.read(regs.readHL()) - 1;
                regs.setFlagsSUB(temp16, memory.read(regs.readHL()), 1, 0, 1, 1, 1, 0, 1);
                memory.write(regs.readHL(), temp16);
                return 3;
            case 0x3D:
                temp16 = regs.A - 1;
                regs.setFlagsSUB(temp16, regs.A, 1, 0, 1, 1, 1, 0, 1);
                regs.A = temp16;
                return 1;
        };
        { // DCX, decrement 16bit register pair
            case 0x0B:
                regs.setBC(regs.readBC() - 1);
                return 1;
            case 0x1B:
                regs.setDE(regs.readDE() - 1);
                return 1;
            case 0x2B:
                regs.setHL(regs.readHL() - 1);
                return 1;
            case 0x3B:
                regs.SP -= 1;
                return 1;
        };
        { // DAD, add register RP to HL, only sets carry flag based on double precision overflow
            case 0x09:
                if (UINT16_MAX - regs.readHL() < regs.readBC()) { // set carry if overflow
                    regs.setCarry();;
                } else {
                    regs.clearCarry();
                }
                regs.setHL(regs.readHL() + regs.readBC());
                return 3;
            case 0x19:
                if (UINT16_MAX - regs.readHL() < regs.readDE()) {
                    regs.setCarry();;
                } else {
                    regs.clearCarry();
                }
                regs.setHL(regs.readHL() + regs.readDE());
                return 3;
            case 0x29:
                if (UINT16_MAX - regs.readHL() < regs.readHL()) { 
                    regs.setCarry();;
                } else {
                    regs.clearCarry();
                }
                regs.setHL(regs.readHL() + regs.readHL());
                return 3;
            case 0x39:
                if (UINT16_MAX - regs.readHL() < regs.SP) { 
                    regs.setCarry();;
                } else {
                    regs.clearCarry();
                }
                regs.setHL(regs.readHL() + regs.SP);
                return 3;
        };
        { // DAA
            case 0x27: 
                temp8 = 0;
                if ((regs.A & 0x0F) > 9 || regs.getAuxCarry() == 1) {
                    temp8 += 6;
                }
                if ((regs.A + temp8) >> 4 > 9 || regs.getCarry() == 1) {
                    temp8 += 6 << 4;
                }
                temp16 = regs.A + temp8;
                regs.setFlagsADD(temp16, regs.A, temp8);
                regs.A = temp8;
                return 1;
        };
        // LOGICAL GROUP
        { // ANA
            case 0xA0:
                temp8 = regs.A & regs.B;
                regs.setFlags(temp8, 1, 1, 1, 0);
                if (((regs.A | regs.B) && 0b100 ) >> 2) {
                    regs.F |= 0b00010000;
                } else {
                    regs.F &= ~0b00010000;
                }
                regs.clearCarry(); // unset CY
                regs.A = temp8;
                return 1;
            case 0xA1:
                temp8 = regs.A & regs.C;
                regs.setFlags(temp8, 1, 1, 1, 0);
                if (((regs.A | regs.C) && 0b100 ) >> 2) {
                    regs.F |= 0b00010000;
                } else {
                    regs.F &= ~0b00010000;
                }
                regs.clearCarry(); // unset CY
                regs.A = temp8;
                return 1;
            case 0xA2:
                temp8 = regs.A & regs.D;
                regs.setFlags(temp8, 1, 1, 1, 0);
                if (((regs.A | regs.D) && 0b100 ) >> 2) {
                    regs.F |= 0b00010000;
                } else {
                    regs.F &= ~0b00010000;
                }
                regs.clearCarry(); // unset CY
                regs.A = temp8;
                return 1;
            case 0xA3:
                temp8 = regs.A & regs.E;
                regs.setFlags(temp8, 1, 1, 1, 0);
                if (((regs.A | regs.E) && 0b100 ) >> 2) {
                    regs.F |= 0b00010000;
                } else {
                    regs.F &= ~0b00010000;
                }
                regs.A = temp8;
                return 1;
            case 0xA4:
                temp8 = regs.A & regs.H;
                regs.setFlags(temp8, 1, 1, 1, 0);
                if (((regs.A | regs.H) && 0b100 ) >> 2) {
                    regs.F |= 0b00010000;
                } else {
                    regs.F &= ~0b00010000;
                }
                regs.clearCarry(); // unset CY
                regs.A = temp8;
                return 1;
            case 0xA5:
                temp8 = regs.A & regs.L;
                regs.setFlags(temp8, 1, 1, 1, 0);
                if (((regs.A | regs.L) && 0b100 ) >> 2) {
                    regs.F |= 0b00010000;
                } else {
                    regs.F &= ~0b00010000;
                }
                regs.clearCarry(); // unset CY
                regs.A = temp8;
                return 1;
            case 0xA6:
                temp8 = regs.A & memory.read(regs.readHL());
                regs.setFlags(temp8, 1, 1, 1, 0);
                if (((regs.A | memory.read(regs.readHL())) && 0b100 ) >> 2) {
                    regs.F |= 0b00010000;
                } else {
                    regs.F &= ~0b00010000;
                }
                regs.clearCarry(); // unset CY
                regs.A = temp8;
                return 2;
            case 0xA7:
                temp8 = regs.A & regs.A;
                regs.setFlags(temp8, 1, 1, 1, 0);
                if (((regs.A | regs.A) && 0b100 ) >> 2) {
                    regs.F |= 0b00010000;
                } else {
                    regs.F &= ~0b00010000;
                }
                regs.clearCarry(); // unset CY
                regs.A = temp8;
                return 1;
        };
        { // ANI
            case 0xE5:
                uint8_t value = memory.read(regs.PC++);
                temp8 = regs.A & value;
                regs.setFlags(temp8, 1, 1, 1, 0);
                regs.F &= ~0b00010001; // unset CY and AC
                regs.A = temp8;
                return 2;
        };
        { // XRA
            case 0xA8:
                regs.A ^= regs.B;
                regs.setFlags(regs.A, 1, 1, 1, 0);
                regs.F &= ~0b00010001; // unset CY and AC
                return 1;
            case 0xA9:
                regs.A ^= regs.C;
                regs.setFlags(regs.A, 1, 1, 1, 0);
                regs.F &= ~0b00010001; // unset CY and AC
                return 1;
            case 0xAA:
                regs.A ^= regs.D;
                regs.setFlags(regs.A, 1, 1, 1, 0);
                regs.F &= ~0b00010001; // unset CY and AC
                return 1;
            case 0xAB:
                regs.A ^= regs.E;
                regs.setFlags(regs.A, 1, 1, 1, 0);
                regs.F &= ~0b00010001; // unset CY and AC
                return 1;
            case 0xAC:
                regs.A ^= regs.H;
                regs.setFlags(regs.A, 1, 1, 1, 0);
                regs.F &= ~0b00010001; // unset CY and AC
                return 1;
            case 0xAD:
                regs.A ^= regs.L;
                regs.setFlags(regs.A, 1, 1, 1, 0);
                regs.F &= ~0b00010001; // unset CY and AC
                return 1;
            case 0xAE:
                regs.A ^= memory.read(regs.readHL());
                regs.setFlags(regs.A, 1, 1, 1, 0);
                regs.F &= ~0b00010001; // unset CY and AC
                return 2;
            case 0xAF:
                regs.A ^= regs.A;
                regs.setFlags(regs.A, 1, 1, 1, 0);
                regs.F &= ~0b00010001; // unset CY and AC
                return 1;
        };
        { // XRI
            case 0xED:
                regs.A ^= memory.read(regs.PC++);
                regs.setFlags(regs.A, 1, 1, 1, 0);
                regs.F &= ~0b00010001; // unset CY and AC
                return 2;
        };
        { // ORA
            case 0xB0:
                regs.A |= regs.B;
                regs.setFlags(regs.A, 1, 1, 1, 0);
                regs.F &= ~0b00010001; // unset CY and AC
                return 1;
            case 0xB1:
                regs.A |= regs.C;
                regs.setFlags(regs.A, 1, 1, 1, 0);
                regs.F &= ~0b00010001; // unset CY and AC
                return 1;
            case 0xB2:
                regs.A |= regs.D;
                regs.setFlags(regs.A, 1, 1, 1, 0);
                regs.F &= ~0b00010001; // unset CY and AC
                return 1;
            case 0xB3:
                regs.A |= regs.E;
                regs.setFlags(regs.A, 1, 1, 1, 0);
                regs.F &= ~0b00010001; // unset CY and AC
                return 1;
            case 0xB4:
                regs.A |= regs.H;
                regs.setFlags(regs.A, 1, 1, 1, 0);
                regs.F &= ~0b00010001; // unset CY and AC
                return 1;
            case 0xB5:
                regs.A |= regs.L;
                regs.setFlags(regs.A, 1, 1, 1, 0);
                regs.F &= ~0b00010001; // unset CY and AC
                return 1;
            case 0xB6:
                regs.A |= memory.read(regs.readHL());
                regs.setFlags(regs.A, 1, 1, 1, 0);
                regs.F &= ~0b00010001; // unset CY and AC
                return 2;
            case 0xB7:
                regs.A |= regs.A;
                regs.setFlags(regs.A, 1, 1, 1, 0);
                regs.F &= ~0b00010001; // unset CY and AC
                return 1;
        };
        { // ORI
            case 0xF6:
                regs.A ^= memory.read(regs.PC++);
                regs.setFlags(regs.A, 1, 1, 1, 0);
                regs.F &= ~0b00010001; // unset CY and AC
                return 2;
        };
        { // CMP
            case 0xB8:
                temp16 = regs.A - regs.B;
                regs.setFlagsSUB(temp16, regs.A, regs.B);
                return 1;
            case 0xB9:
                temp16 = regs.A - regs.C;
                regs.setFlagsSUB(temp16, regs.A, regs.B);
                return 1;
            case 0xBA:
                temp16 = regs.A - regs.D;
                regs.setFlagsSUB(temp16, regs.A, regs.B);
                return 1;
            case 0xBB:
                temp16 = regs.A - regs.E;
                regs.setFlagsSUB(temp16, regs.A, regs.B);
                return 1;
            case 0xBC:
                temp16 = regs.A - regs.H;
                regs.setFlagsSUB(temp16, regs.A, regs.B);
                return 1;
            case 0xBD:
                temp16 = regs.A - regs.L;
                regs.setFlagsSUB(temp16, regs.A, regs.B);
                return 1;
            case 0xBE:
                temp16 = regs.A - memory.read(regs.readHL());
                regs.setFlagsSUB(temp16, regs.A, regs.B);
                return 2;
            case 0xBF:
                temp16 = regs.A - regs.A;
                regs.setFlagsSUB(temp16, regs.A, regs.B);
                return 1;
        };
        { // CPI
            case 0xFE:
                temp16 = regs.A - memory.read(regs.PC++);
                regs.setFlagsSUB(temp16, regs.A, regs.B);
                return 2;
        };
        { // ROTATE
            case 0x07: // RLC, rotate left
                bit = (regs.A & 0b10000000) >> 7;
                if (bit == 1) {
                    regs.setCarry();
                } else {
                    regs.clearCarry();
                }
                temp8 = regs.A << 1;
                regs.A = temp8 + bit;
                return 1;
            case 0x0F: // RRC, rotate right
                bit = regs.A & 0b1;
                if (bit == 1) {
                    regs.setCarry();
                } else {
                    regs.clearCarry();
                }
                temp8 = (regs.A >> 1) | (bit << 7);
                regs.A = temp8;
                return 1;
            case 0x17: // RAL, rotate left through carry
                bit = (regs.A & 0b10000000) >> 7;
                temp8 = (regs.A << 1) + regs.getCarry();
                regs.A = temp8;
                if (bit == 1) {
                    regs.setCarry();
                } else {
                    regs.clearCarry();
                }
                return 1;
            case 0x1F: // RAR, rotate right through carry
                bit = regs.A & 0b1;
                temp8 = (regs.A >> 1) + (regs.getCarry() << 7);
                regs.A = temp8;
                if (bit == 1) {
                    regs.setCarry();
                }
                else {
                    regs.clearCarry();
                }
                return 1;
        };
        { // COMPLEMENT
            case 0x2F: // CMA, complement accumulator
                regs.A = ~regs.A;
                return 1;
            case 0x3F: // CMC, complement carry
                regs.toggleCarry();
                return 1;
        };
        { // STC
            case 0x37:
                regs.setCarry();
                return 1;
        };
        // BRANCH GROUP
        { // JMP
            case 0xC3: // conditional
                regs.PC = read16atPC();
                return 3;
            case 0xC2: // JNZ, jump if not zero
                if (!regs.getZero()) {
                    regs.PC = read16atPC();
                }
                return 3;
            case 0xCA: // JZ, jump if zero
                if (regs.getZero()) {
                    regs.PC = read16atPC();
                }
                return 3;
            case 0xD2: // JNC, jump if carry not set
                if (!regs.getCarry()) {
                    regs.PC = read16atPC();
                }
                return 3;
            case 0xDA: // JC, jump if carry set
                if (regs.getCarry()) {
                    regs.PC = read16atPC();
                }
                return 3;
            case 0xE2: // JPO, jump if parity not set, odd parity
                if (!regs.getParity()) {
                    regs.PC = read16atPC();
                }
                return 3;
            case 0xEA: // JPE, jump if parity set, even parity
                if (regs.getParity()) {
                    regs.PC = read16atPC();
                }
                return 3;
            case 0xF2: // JP, jump if sign plus, not set
                if (!regs.getSign()) {
                    regs.PC = read16atPC();
                }
                return 3;
            case 0xFA: // JM, jump if sign minus, set
                if (regs.getSign()) {
                    regs.PC = read16atPC();
                }
                return 3;
        };
        { // CALL
            case 0xCD: // CALL unconditional
                memory.write(regs.SP-1, (regs.PC & 0xF0) >> 8);
                memory.write(regs.SP-2, regs.PC & 0x0F);
                regs.SP -= 2;
                regs.PC = read16atPC();
                return 5;
            case 0xC9: // RET, return from call
                temp16 = 0;
                temp16 += memory.read(regs.SP);
                temp16 += memory.read(regs.SP+1) << 8;
                regs.SP += 2;
                regs.PC = temp16;
                return 3;
        }
        default:
            UnimplementedInstruction();
            return 0;
    }   
}