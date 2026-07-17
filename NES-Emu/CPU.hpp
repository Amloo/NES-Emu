#pragma once
#include <cstdint>

class Bus;

class CPU {
public:
	CPU(Bus& bus);

private:
	Bus& bus;

	uint8_t a;
	uint8_t x;
	uint8_t y;
	uint16_t pc;
	uint8_t s;
	uint8_t p;

	void execute(uint8_t opcode);

	uint16_t Absolute();
	uint16_t ZeroPage();
	uint16_t Immediate();

	void SetZ(uint8_t value);
	void SetN(uint8_t value);

	void LDA(uint16_t address);
	void STA(uint16_t address);
	void LDX(uint16_t address);
	void STX(uint16_t address);
	void LDY(uint16_t address);
	void STY(uint16_t address);
	void TAX();
	void TXA();
	void TAY();
	void TYA();
	void ADC(uint16_t address);
	void SBC(uint16_t address);
	void INC(uint16_t address);
	void DEC(uint16_t address);
	void INX();
	void DEX();
	void INY();
	void DEY();
	void ASL(uint16_t address);
	void LSR(uint16_t address);
	void ROL(uint16_t address);
	void ROR(uint16_t address);
	void AND(uint16_t address);
	void ORA(uint16_t address);
	void EOR(uint16_t address);
	void BIT(uint16_t address);
	void CMP(uint16_t address);
	void CPX(uint16_t address);
	void CPY(uint16_t address);
	void BCC(uint16_t address);
	void BCS(uint16_t address);
	void BEQ(uint16_t address);
	void BNE(uint16_t address);
	void BPL(uint16_t address);
	void BMI(uint16_t address);
	void BVC(uint16_t address);
	void BVS(uint16_t address);
	void JMP(uint16_t address);
	void JSR(uint16_t address);
	void RTS();
	void BRK();
	void RTI();
	void PHA();
	void PLA();
	void PHP();
	void PLP();
	void TXS();
	void TSX();
	void CLC();
	void SEC();
	void CLI();
	void SEI();
	void CLD();
	void SED();
	void CLV();
	void NOP();
};