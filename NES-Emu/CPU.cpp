#include "CPU.hpp"
#include "Bus.hpp"

CPU::CPU(Bus& bus) : bus(bus) {}

void CPU::execute(uint8_t opcode) {

}

uint16_t CPU::Absolute() {
    uint8_t low = bus.Read(pc++);
    uint8_t high = bus.Read(pc++);

    return (high << 8) | low;
}

uint16_t CPU::ZeroPage() {
    return bus.Read(pc++);
}

uint16_t CPU::Immediate() { 
    return pc++; 
}

void CPU::SetZ(uint8_t value)
{
    if (value == 0)
        p |= (1 << 1);
    else
        p &= ~(1 << 1);
}

void CPU::SetN(uint8_t value)
{
    if (value & 0x80)
        p |= (1 << 7);
    else
        p &= ~(1 << 7);
}

void CPU::LDA(uint16_t address)
{
    a = bus.Read(address);
    SetZ(a);
    SetN(a);
}