#ifndef Chip8tle
#define Chip8tle

#include <iostream>
#include "res.h"
#include <cstdlib>
#include <ctime>

#define SCREEN_H 32
#define SCREEN_W 64

/* Virtual Machine class */

class Chip8tleVM {

public:
	 Chip8tleVM();
	~Chip8tleVM();

	Chip8tleCore core;	// Super Core
	Chip8tleExt ext;	// External

	// Opcoder
	unsigned short opcode 	//Opcode 	16bits
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
	void rnd();
	void ld07();
	void ld15();
	void add1d();
	void ld33();
	void ld65();
};

Chip8tleVM::Chip8tleVM() {
	srand (time(NULL));
	this->opcode  = 0;
	this->opcoder = {	// 5 x 7 !!!!
		sys  , ret, call , sne_kk, ld_kk, 
		ld_y0, And, addy4, shr   , shl  , 
		ldnn, rnd, ld07, ld15, ld33
	};
	this->core = Chip8tleCore();
	this->ext  = Chip8tleExt();
	// Y lo demas (Creo que mas nada)
}

// Por aqui los metodos de cada opcode
void Chip8tleVM::ld65()
{
	for(int i = 0;i<=((opcode & 0x0f00) >> 8);i++)
	{
		core.V[i] = ext.rem[core.I+i];
	}
}

void Chip8tleVM::ld33()
{
	ext.rem[core.I] = core.V[(opcode & 0x0f00) >> 8] % 100;
	ext.rem[core.I+1] = (core.V[(opcode & 0x0f00) >> 8] /10)%10;
	ext.rem[core.I+2] = core.V[(opcode & 0x0f00) >> 8] % 10;
}

void Chip8tleVM::add1d()
{
	core.I = core.V[(opcode & 0x0f00) >> 8] + core.I;
}

void Chip8tleVM::ld15()
{
	core.DT = core.V[(opcode & 0x0f00) >> 8];
}


void Chip8tleVM::ld07()
{
	core.V[(opcode & 0x0f00) >> 8] = core.DT;
}

void Chip8tleVM::rnd()
{
	core.V[(opcode & 0x0f00) >> 8] = rand()%256 & (opcode & 0x00ff);
}

void Chip8tleVM::sys()
{
	core.PC = (opcode & 0x0fff);
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
	core.SP--;
	core.PC = core.stack[core.SP];
}

void Chip8tleVM::call()
{
	core.stack[core.SP] = core.PC;
	core.PC = (opcode & 0x0fff);
	core.SP++;
}

void Chip8tleVM::sne_kk()
{
	if(core.V[(opcode & 0x0f00) >> 8] != (opcode & 0x00ff))
	{
		core.PC = core.PC+2;
	}
}

void Chip8tleVM::ld_kk()
{
	core.V[(opcode & 0x0f00) >> 8] = (opcode & 0x00ff); 
}

void Chip8tleVM::ld_y0()
{
	core.V[(opcode & 0x0f00) >> 8] = core.V[(opcode & 0x00f0) >> 4]; 
}

void Chip8tleVM::And()
{
	core.V[(opcode & 0x0f00) >> 8] = core.V[(opcode & 0x0f00) >> 8] & core.V[(opcode & 0x00f0) >> 4]; 
}

void Chip8tleVM::addy4()
{
	core.V[(opcode & 0x0f00) >> 8] = (core.V[(opcode & 0x0f00) >> 8] + core.V[(opcode & 0x00f0) >> 4]) & 0x00ff;
	if((core.V[(opcode & 0x0f00) >> 8] + core.V[(opcode & 0x00f0) >> 4]) > 0xff) 
		core.V[0xf] = 0x01;
}

void Chip8tleVM::shr()
{
	if(core.V[opcode & 0x0f00] %2 != 0)
	{
		core.V[0xf] = 0x01;
	}
	else
	{
		core.V[0xf] = 0x0;
	}

	core.V[opcode & 0x0f00] >> 1;
}

void Chip8tleVM::shl()
{
	if(core.V[opcode & 0x0f00] & 0x80 == 0x80)
	{
		core.V[0xf] = 0x01;
	}
	else
	{
		core.V[0xf] = 0x0;
	}

	core.V[opcode & 0x0f00] << 1;
}

void Chip8tleVM::ldnn()
{
	core.I = opcode & 0x0fff
}

#endif