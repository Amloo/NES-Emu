#include "Bus.hpp"

uint8_t Bus::Read(uint16_t address)
{
    if (address <= 0x1FFF)
    {
        return ram[address & 0x07FF];
    }
    return 0;
}

void Bus::Write(uint16_t address, uint8_t value)
{
    if (address <= 0x1FFF)
    {
        ram[address & 0x07FF] = value;
    }
}