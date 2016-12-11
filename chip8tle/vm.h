#ifndef Chip8tle
#define Chip8tle

#include <iostream>
#include "res.h"

#define SCREEN_H 32
#define SCREEN_W 64

/* Virtual Machine class */

class Chip8tleVM {

public:
	 Chip8tleVM();
	~Chip8tleVM();

	Chip8tleCore core;	// Super Core
	Chip8tleExt ext;	// External

	// Por aqui deberia ir opcoder[35]
	void (*opcoder[35])();

private:	
	void sys();
	void ret();
	void call();
	void sne_kk();
	void ld_kk();
	void ld_y0();
	void And();
	void addy4();
	void shr();
	void shl();
	void ldnn();
};

Chip8tleVM::Chip8tleVM() {
	this->core = Chip8tleCore();
	// Y lo demas
}

// Por aqui los metodos de cada opcode
void Chip8tleVM::sys()
{
	PC = (opcode & 0x0fff);
}

void Chip8tleVM::cls() {

	int i, j;
	for(i=0; i < SCREEN_W; i++) {
		for(j=0; j < SCREEN_H; j++) {
			this->ext.screen[i][j] = 0
		}
	}
}

void Chip8tleVM::jp() {
	
}

void Chip8tleVM::ret()
{
	SP--;
	PC = stack[SP];
}

void Chip8tleVM::call()
{
	stack[SP] = PC;
	PC = (opcode & 0x0fff);
	SP++;
}

void Chip8tleVM::sne_kk()
{
	if(V[(opcode & 0x0f00) >> 8] != (opcode & 0x00ff))
	{
		PC = PC+2;
	}
}

void Chip8tleVM::ld_kk()
{
	V[(opcode & 0x0f00) >> 8] = (opcode & 0x00ff); 
}

void Chip8tleVM::ld_y0()
{
	V[(opcode & 0x0f00) >> 8] = V[(opcode & 0x00f0) >> 4]; 
}

void Chip8tleVM::And()
{
	V[(opcode & 0x0f00) >> 8] = V[(opcode & 0x0f00) >> 8] & V[(opcode & 0x00f0) >> 4]; 
}

void Chip8tleVM::addy4()
{
	V[(opcode & 0x0f00) >> 8] = (V[(opcode & 0x0f00) >> 8] + V[(opcode & 0x00f0) >> 4]) & 0x00ff;
	if((V[(opcode & 0x0f00) >> 8] + V[(opcode & 0x00f0) >> 4]) > 0xff) 
		V[0xf] = 0x01;
}

void Chip8tleVM::shr()
{
	if(v[opcode & 0x0f00] %2 != 0)
	{
		V[0xf] = 0x01;
	}
	else
	{
		V[0xf] = 0x0;
	}

	v[opcode & 0x0f00] >> 1;
}

void Chip8tleVM::shl()
{
	if(v[opcode & 0x0f00] & 0x80 == 0x80)
	{
		V[0xf] = 0x01;
	}
	else
	{
		V[0xf] = 0x0;
	}

	v[opcode & 0x0f00] << 1;
}

void Chip8tleVM::ldnn()
{
	I = opcode & 0x0fff
}

#endif