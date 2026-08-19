#include "CPU.hpp"
#include "Bus.hpp"

CPU::CPU(Bus& bus) : bus(bus) {}

void CPU::Execute(uint8_t opcode) {

}

uint16_t CPU::Absolute() {
    uint8_t low = bus.Read(pc++);
    uint8_t high = bus.Read(pc++);
    return (high << 8) | low;
}

uint16_t CPU::ZeroPage() {
    return (uint16_t)bus.Read(pc++);
}

uint16_t CPU::Immediate() { 
    return pc++; 
}

void CPU::Push(uint8_t value)
{
    bus.Write(0x0100 + sp, value);
    sp--;
}

uint8_t CPU::Pop()
{
    sp++;
    return bus.Read(0x0100 + sp);
}

void CPU::SetC(bool carry) {
    if (carry)
        p |= (1 << 0);
    else
        p &= ~(1 << 0);
}

void CPU::SetZ(uint8_t value) {
    if (value == 0)
        p |= (1 << 1);
    else
        p &= ~(1 << 1);
}

void CPU::SetI(bool interrupt) {
    if (interrupt)
        p |= (1 << 2);
    else
        p &= ~(1 << 2);
}

void CPU::SetD(bool decimal) {
    if (decimal)
        p |= (1 << 3);
    else
        p &= ~(1 << 3);
}

void CPU::SetB(bool flag) {
    if (flag)
        p |= (1 << 4);
    else
        p &= ~(1 << 4);
}

void CPU::SetV(bool overflow) {
    if (overflow)
        p |= (1 << 6);
    else
        p &= ~(1 << 6);
}

void CPU::SetN(uint8_t value) {
    if (value & 0x80)
        p |= (1 << 7);
    else
        p &= ~(1 << 7);
}

void CPU::LDA(uint16_t address) //Load A
{
    a = bus.Read(address);
    SetZ(a);
    SetN(a);
}

void CPU::STA(uint16_t address) //Store A
{
    bus.Write(address, a);
}

void CPU::LDX(uint16_t address) //Load X
{
    x = bus.Read(address);
    SetZ(x);
    SetN(x);
}

void CPU::STX(uint16_t address) //Store X
{
    bus.Write(address, x);
}

void CPU::LDY(uint16_t address) //Load Y
{
    y = bus.Read(address);
    SetZ(y);
    SetN(y);
}

void CPU::STY(uint16_t address) //Store Y
{
    bus.Write(address, y);
}

void CPU::TAX() //Transfer A to X
{
    x = a;
    SetZ(x);
    SetN(x);
}

void CPU::TXA() //Transfer X to A
{
    a = x;
    SetZ(a);
    SetN(a);
}

void CPU::TAY() //Transfer A to Y
{
    y = a;
    SetZ(y);
    SetN(y);
}

void CPU::TYA() //Transfer Y to A
{
    a = y;
    SetZ(a);
    SetN(a);
}

void CPU::ADC(uint16_t address) //Add with Carry
{
    uint8_t value = bus.Read(address);
    uint16_t sum = (uint16_t)a + value + (p & 0x01);
    SetC(sum > 0xFF);
    SetV((~(a ^ value) & (a ^ (uint8_t)sum) & 0x80) != 0);
    a = (uint8_t)sum;
    SetZ(a);
    SetN(a);
}

void CPU::SBC(uint16_t address) //Subtract with Carry
{
    uint8_t value = bus.Read(address) ^ 0xFF;
    uint16_t sum = (uint16_t)a + value + (p & 0x01);
    SetC(sum > 0xFF);
    SetV((~(a ^ value) & (a ^ (uint8_t)sum) & 0x80) != 0);
    a = (uint8_t)sum;
    SetZ(a);
    SetN(a);
}

void CPU::INC(uint16_t address) //Increment Memory
{
    uint8_t value = bus.Read(address);
    value++;
    bus.Write(address, value);
    SetZ(value);
    SetN(value);
}

void CPU::DEC(uint16_t address) //Decrement Memory
{
    uint8_t value = bus.Read(address);
    value--;
    bus.Write(address, value);
    SetZ(value);
    SetN(value);
}

void CPU::INX() //Increment X
{
    x++;
    SetZ(x);
    SetN(x);
}

void CPU::DEX() //Decrement X
{
    x--;
    SetZ(x);
    SetN(x);
}

void CPU::INY() //Increment Y
{
    y++;
    SetZ(y);
    SetN(y);
}

void CPU::DEY() //Decrement Y
{
    y--;
    SetZ(y);
    SetN(y);
}

void CPU::ASL(uint16_t address) //Arithmetic Shift Left
{
    uint8_t value = bus.Read(address);
    SetC((value >> 7) & 0x01);
    value <<= 1;
    bus.Write(address, value);
    SetZ(value);
    SetN(value);
}

void CPU::LSR(uint16_t address) //Logical Shift Right
{
    uint8_t value = bus.Read(address);
    SetC(value & 0x01);
    value >>= 1;
    bus.Write(address, value);
    SetZ(value);
    SetN(false);
}

void CPU::ROL(uint16_t address) //Rotate Left
{
    uint8_t value = bus.Read(address);
    bool oldCarry = p & 0x01;
    SetC(value & 0x80);
    value <<= 1;
    if (oldCarry)
        value |= 0x01;
    bus.Write(address, value);
    SetZ(value);
    SetN(value);
}

void CPU::ROR(uint16_t address) //Rotate Right
{
    uint8_t value = bus.Read(address);
    bool oldCarry = p & 0x01;
    SetC(value & 0x01);
    value >>= 1;
    if (oldCarry)
        value |= 0x80;
    bus.Write(address, value);
    SetZ(value);
    SetN(value);
}

void CPU::AND(uint16_t address) //Bitwise AND
{
    a &= bus.Read(address);
    SetZ(a);
    SetN(a);
}

void CPU::ORA(uint16_t address) //Bitwise OR
{
    a |= bus.Read(address);
    SetZ(a);
    SetN(a);
}

void CPU::EOR(uint16_t address) //Bitwise Exclusive OR
{
    a ^= bus.Read(address);
    SetZ(a);
    SetN(a);
}

void CPU::BIT(uint16_t address) //Bit Test
{
    uint8_t value = bus.Read(address);
    SetZ(a & value);
    SetV(value & 0x40);
    SetN(value);
}

void CPU::CMP(uint16_t address) //Compare A
{
    uint8_t value = bus.Read(address);
    uint8_t sum = a - value;
    SetC(a >= value);
    SetZ(sum);
    SetN(sum);
}

void CPU::CPX(uint16_t address) //Compare X
{
    uint8_t value = bus.Read(address);
    uint8_t sum = x - value;
    SetC(x >= value);
    SetZ(sum);
    SetN(sum);
}

void CPU::CPY(uint16_t address) //Compare Y
{
    uint8_t value = bus.Read(address);
    uint8_t sum = y - value;
    SetC(y >= value);
    SetZ(sum);
    SetN(sum);
}

void CPU::BCC(uint16_t address) //Branch if Carry Clear
{
    if (!(p & 0x01))
        pc += 2 + static_cast<int8_t>(bus.Read(address));
}

void CPU::BCS(uint16_t address) //Branch if Carry Set
{
    if (p & 0x01)
        pc += 2 + static_cast<int8_t>(bus.Read(address));
}

void CPU::BEQ(uint16_t address) //Branch if Equal
{
    if ((p >> 1) & 0x01)
        pc += 2 + static_cast<int8_t>(bus.Read(address));
}

void CPU::BNE(uint16_t address) //Branch if Not Equal
{
    if (!((p >> 1) & 0x01))
        pc += 2 + static_cast<int8_t>(bus.Read(address));
}

void CPU::BPL(uint16_t address) //Branch if Plus
{
    if ((p >> 7) & 0x01)
        pc += 2 + static_cast<int8_t>(bus.Read(address));
}

void CPU::BMI(uint16_t address) //Branch if Minus
{
    if (!((p >> 7) & 0x01))
        pc += 2 + static_cast<int8_t>(bus.Read(address));
}

void CPU::BVC(uint16_t address) //Branch if Overflow Clear
{
    if (!((p >> 6) & 0x01))
        pc += 2 + static_cast<int8_t>(bus.Read(address));
}

void CPU::BVS(uint16_t address) //Branch if Overflow Set
{
    if ((p >> 6) & 0x01)
        pc += 2 + static_cast<int8_t>(bus.Read(address));
}

void CPU::JMP(uint16_t address) //Jump
{
    pc = bus.Read(address);
}

void CPU::JSR(uint16_t address) //Jump to Subroutine
{
    uint16_t returnAddress = pc - 1;
    Push((returnAddress >> 8) & 0xFF);
    Push(returnAddress & 0xFF);
    pc = bus.Read(address);
}

void CPU::RTS() //Return from Subroutine
{
    uint8_t low = Pop();
    uint8_t high = Pop();
    pc = ((high << 8) | low) + 1;
}

void CPU::BRK() //Break
{
    uint16_t returnAddress = pc - 1;
    Push((returnAddress >> 8) & 0xFF);
    Push(returnAddress & 0xFF);
    Push(p);
    pc = bus.Read(0xFFFE);
}

void CPU::RTI() //Return from Interrupt
{
    p = Pop();
    uint8_t low = Pop();
    uint8_t high = Pop();
    pc = ((high << 8) | low) + 1;
}

void CPU::PHA() //Push A
{
    Push(a);
    sp--;
}

void CPU::PLA() //Pull A
{
    sp++;
    a = Pop();
    SetZ(a);
    SetN(a);
}

void CPU::PHP() //Push Processor Status
{
    Push(p);
    sp--;
    SetB(true);
}

void CPU::PLP() //Pull Processor Status
{
    sp++;
    p = Pop();
}

void CPU::TXS() //Transfer X to Stack Pointer
{
    sp = x;
}

void CPU::TSX() //Transfer Stack Pointer to X
{
    x = sp;
    SetZ(a);
    SetN(a);
}

void CPU::CLC() //Clear Carry
{
    SetC(false);
}

void CPU::SEC() //Set Carry
{
    SetC(true);
}

void CPU::CLI() //Clear Interrupt Disable
{
    SetI(false);
}

void CPU::SEI() //Set Interrupt Disable
{
    SetI(true);
}

void CPU::CLD() //Clear Decimal
{
    SetD(false);
}

void CPU::SED() //Set Decimal
{
    SetD(true);
}

void CPU::CLV() //Clear Overflow
{
    SetV(false);
}