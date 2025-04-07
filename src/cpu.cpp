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
    const uint8_t group = (opcode & 0b11000000) >> 6;

    uint16_t address;
    uint8_t value8;
    uint16_t temp16;
    // uint16_t value16;

    regs.PC += 1; // increment PC to avoid repetitive code

    switch (group) { // First check some groups of opcodes we can generalize
        case 0b01: // MOV opcodes
        { 
            const uint8_t SSS = opcode & 0b00000111;        // Source 
            const uint8_t DDD = (opcode & 0b00111000) >> 3; // Destination
            uint8_t *dest = regs.getSingleRegister(DDD);
            uint8_t *source = regs.getSingleRegister(SSS);
            if (SSS == 0b110) { // Move from memory, address in register pair HL, value in register DDD
                *dest = memory.read(regs.readHL());
                return 2; // 2 cycles
            } else if (DDD == 0b110) { // Move to memory, address in register pair HL, value in register SSS
                memory.write(regs.readHL(), *source);
                return 2; // 2 cycles
            } else { // Move, register SSS to register DDD
                *dest = *source; 
                return 1; // 1 cycle
            }
        }
        case 0b00: // Data transfer (without MOV and XCHG)
        {   
            // Move Immediate
            if ((opcode & 0b111) == 0b110) {  
                uint8_t value = memory.read(regs.PC++);
                const uint8_t DDD = (opcode & 0b00111000) >> 3; // Destination
                uint8_t *dest = regs.getSingleRegister(DDD);
                if (dest == nullptr) { // Move to memory immediate
                    assert(opcode == 0b00110110); // Assert this is actually the correct opcode 
                    memory.write(regs.readHL(), value);
                    return 3;
                } else { // Move immediate
                    *dest = value;
                    return 2;
                }
            // Load register pair immediate
            } else if ((opcode & 0b1111) == 0b0001) {
                uint8_t RP = (opcode & 0b00110000);
                uint16_t value = read16atPC();
                regs.setRP(RP, value);
                return 3;
            // Load accumulator indirect
            } else if ((opcode & 0b1111) == 0b1010 && (opcode & 0b00100000) >> 5 == 0b0) {
                uint8_t RP = (opcode & 0b00110000);
                uint16_t address = regs.readRP(RP);
                regs.A = memory.read(address);
                return 2;
            } else if ((opcode & 0b1111) == 0b0010 && (opcode & 0b00100000) >> 5 == 0b0) {
                uint8_t RP = (opcode & 0b00110000);
                uint16_t address = regs.readRP(RP);
                memory.write(address, regs.A);
                return 2;
            }
            break;
        }
        default: break;
    }

    switch (opcode) {
        case 0x00: //NOP
            break;
        // Data transfer
        case 0b00111010: // Load Accumulator direct
        {
            uint16_t value = read16atPC();
            regs.A = value;
            return 4;
        }
        case 0b00110010: // Store Accumulator direct
        {
            uint16_t value = read16atPC();
            memory.write(value, regs.A);
            return 4;
        }
        case 0b00101010: // Load H and L direct
        {
            uint16_t address = read16atPC();
            regs.L = memory.read(address);
            regs.H = memory.read(address+1);
            return 5;
        }
        case 0b11101011: // Exchange H and L with D and E
        {
            uint16_t temp = regs.readHL();
            regs.setHL(regs.readDE());
            regs.setDE(temp);
            return 1;
        }
        default:
            UnimplementedInstruction();
    }
    return 1; // most instructions are 1 cycle long

}