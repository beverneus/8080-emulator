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

int Cpu::decode() {
    const uint8_t opcode = memory.read(regs.PC);
    const uint8_t group = (opcode & 0b11000000) >> 6;

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
            }
        }
        default: break;
    }

    switch (opcode) {
        case 0x00: //NOP
            break;
        default:
            UnimplementedInstruction();
    }
    return 1; // most instructions are 1 cycle long

}