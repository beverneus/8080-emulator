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

    uint16_t address;
    uint8_t value8;
    uint16_t temp16;
    // uint16_t value16;

    regs.PC += 1; // increment PC to avoid repetitive code
    
    switch (opcode) {
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
                value8 = memory.read(regs.PC++);
                memory.write(regs.readHL(), value8);
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
                regs.A += regs.B;
                regs.setFlags(regs.A);
                return 1;
            case 0x81:
                regs.A += regs.C;
                regs.setFlags(regs.A);
                return 1;
            case 0x82:
                regs.A += regs.D;
                regs.setFlags(regs.A);
                return 1;
            case 0x83:
                regs.A += regs.E;
                regs.setFlags(regs.A);
                return 1;
            case 0x84:
                regs.A += regs.H;
                regs.setFlags(regs.A);
                return 1;
            case 0x85:
                regs.A += regs.L;
                regs.setFlags(regs.A);
                return 1;
            case 0x86:
                regs.A += memory.read(regs.readHL());
                regs.setFlags(regs.A);
                return 1;
            case 0x87:
                regs.A += regs.A;
                regs.setFlags(regs.A);
                return 1;
            case 0xC6: // ADI
                regs.A += memory.read(regs.PC++);
                regs.setFlags(regs.A);
                return 2;
        };
        { // ADC
            case 0x88:
                regs.A += regs.B + regs.getCarry();
                regs.setFlags(regs.A);
                return 1;
            case 0x89:
                regs.A += regs.C + regs.getCarry();
                regs.setFlags(regs.A);
                return 1;
            case 0x8A:
                regs.A += regs.D + regs.getCarry();
                regs.setFlags(regs.A);
                return 1;
            case 0x8B:
                regs.A += regs.E + regs.getCarry();
                regs.setFlags(regs.A);
                return 1;
            case 0x8C:
                regs.A += regs.H + regs.getCarry();
                regs.setFlags(regs.A);
                return 1;
            case 0x8D:
                regs.A += regs.L + regs.getCarry();
                regs.setFlags(regs.A);
                return 1;
            case 0x8E:
                regs.A += memory.read(regs.readHL()) + regs.getCarry();
                regs.setFlags(regs.A);
                return 1;
            case 0x8F:
                regs.A += regs.A + regs.getCarry();
                regs.setFlags(regs.A);
                return 1;
            case 0xCE: // ADI
                regs.A += memory.read(regs.PC++) + regs.getCarry();
                regs.setFlags(regs.A);
                return 2;
        };
        { // SUB
            case 0x90:
                regs.A -= regs.B;
                regs.setFlags(regs.A);
                return 1;
            case 0x91:
                regs.A -= regs.C;
                regs.setFlags(regs.A);
                return 1;
            case 0x92:
                regs.A -= regs.D;
                regs.setFlags(regs.A);
                return 1;
            case 0x93:
                regs.A -= regs.E;
                regs.setFlags(regs.A);
                return 1;
            case 0x94:
                regs.A -= regs.H;
                regs.setFlags(regs.A);
                return 1;
            case 0x95:
                regs.A -= regs.L;
                regs.setFlags(regs.A);
                return 1;
            case 0x96:
                regs.A -= memory.read(regs.readHL());
                regs.setFlags(regs.A);
                return 1;
            case 0x97:
                regs.A -= regs.A;
                regs.setFlags(regs.A);
                return 1;
            case 0xD6: // SUI
                regs.A -= memory.read(regs.PC++);
                regs.setFlags(regs.A);
                return 2;
        };
        { // SBB
            case 0x98:
                regs.A -= regs.B + regs.getCarry();
                regs.setFlags(regs.A);
                return 1;
            case 0x99:
                regs.A -= regs.C + regs.getCarry();
                regs.setFlags(regs.A);
                return 1;
            case 0x9A:
                regs.A -= regs.D + regs.getCarry();
                regs.setFlags(regs.A);
                return 1;
            case 0x9B:
                regs.A -= regs.E + regs.getCarry();
                regs.setFlags(regs.A);
                return 1;
            case 0x9C:
                regs.A -= regs.H + regs.getCarry();
                regs.setFlags(regs.A);
                return 1;
            case 0x9D:
                regs.A -= regs.L + regs.getCarry();
                regs.setFlags(regs.A);
                return 1;
            case 0x9E:
                regs.A -= memory.read(regs.readHL()) + regs.getCarry();
                regs.setFlags(regs.A);
                return 1;
            case 0x9F:
                regs.A -= regs.A + regs.getCarry();
                regs.setFlags(regs.A);
                return 1;
            case 0xDE: // SBI
                regs.A -= memory.read(regs.PC++) + regs.getCarry();
                regs.setFlags(regs.A);
                return 2;
        };
        default:
            UnimplementedInstruction();
            return 0;
    }   
}