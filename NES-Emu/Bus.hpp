#pragma once
#include <cstdint>

class Bus
{
private:
    uint8_t ram[2048];

public:
    uint8_t Read(uint16_t address);
    void Write(uint16_t address, uint8_t value);
};