#ifndef Chip8tle
#define Chip8tle

#include <iostream>
#include "res.h"

#define SCREEN_H 32
#define SCREEN_W 64

/* Virtual Machine class */
/* Should be PC += 2 OR PC += 4 when skip ? */

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
};

Chip8tleVM::Chip8tleVM() {
	this->opcode  = 0;
	this->opcoder = {	// 5 x 7 !!!!
		sys  , ret, call , sne_kk, ld_kk, 
		ld_y0, And, addy4, shr   , shl  , 
		ldnn
	};
	this->core = Chip8tleCore();
	this->ext  = Chip8tleExt();
	// Y lo demas (Creo que mas nada)
}

// Por aqui los metodos de cada opcode
void Chip8tleVM::sys()
{
	PC = (opcode & 0x0fff);
}

void Chip8tleVM::CLS() {

	int i, j;
	for(i=0; i < SCREEN_W; i++) {
		for(j=0; j < SCREEN_H; j++) {
			ext.screen[i][j] = 0
		}
	}
}

void Chip8tleVM::ret()
{
	SP--;
	PC = stack[SP];
}

void Chip8tleVM::JP() {
	core.PC = opcode & 0x0FFF;
}

void Chip8tleVM::call()
{
	stack[SP] = PC;
	PC = (opcode & 0x0FFF);
	SP++;
}

void Chip8tleVM::SE_3xkk() {
	unsigned short t1 = core.V[(opcode & 0x0F00) >> 8];
	unsigned short t2 = opcode & 0x00FF;
	if(t1 == t2) PC += 2;
}

void Chip8tleVM::sne_kk()
{
	if(V[(opcode & 0x0f00) >> 8] != (opcode & 0x00ff))
	{
		PC = PC+2;
	}
}

void Chip8tleVM::SE_5xy0() {
	unsigned short X = (opcode & 0x0F00) >> 8;
	unsigned short Y = (opcode & 0x00F0) >> 4;
	if(core.V[X] == core.V[Y]) core.PC += 2;
}

void Chip8tleVM::ld_kk()
{
	V[(opcode & 0x0f00) >> 8] = (opcode & 0x00ff); 
}

void Chip8tleVM::ADD_7xkk() {
	unsigned short X  = (opcode & 0x0F00) >> 8;
	unsigned short KK = (opcode & 0x00FF);
	core.V[X] += core.KK;
}

void Chip8tleVM::ld_y0()
{
	V[(opcode & 0x0f00) >> 8] = V[(opcode & 0x00f0) >> 4]; 
}

void Chip8tleVM::OR_8xy1() {
	unsigned short X = (opcode & 0x0F00) >> 8;
	unsigned short Y = (opcode & 0x00F0) >> 4;
	core.V[X] |= core.V[Y];
}

void Chip8tleVM::And()
{
	V[(opcode & 0x0f00) >> 8] = V[(opcode & 0x0f00) >> 8] & V[(opcode & 0x00f0) >> 4]; 
}

void Chip8tleVM::XOR_8xy3() {
	unsigned short X = (opcode & 0x0F00) >> 8;
	unsigned short Y = (opcode & 0x00F0) >> 4;
	core.V[X] ^= core.V[Y];
}

void Chip8tleVM::addy4()
{
	V[(opcode & 0x0f00) >> 8] = (V[(opcode & 0x0f00) >> 8] + V[(opcode & 0x00f0) >> 4]) & 0x00ff;
	if((V[(opcode & 0x0f00) >> 8] + V[(opcode & 0x00f0) >> 4]) > 0xff) 
		V[0xf] = 0x01;
}

void Chip8tleVM::SUB_8xy5() {
	unsigned short X = (opcode & 0x0F00) >> 8;
	unsigned short Y = (opcode & 0x00F0) >> 4;
	core.V[X] -= core.V[Y];
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

void Chip8tleVM::SUBN_8xy7() {
	unsigned short X = (opcode & 0x0F00) >> 8;
	unsigned short Y = (opcode & 0x00F0) >> 4;
	core.V[0xF] = (core.V[X] > core.V[Y]) ? 1 : 0;
	core.V[X] -= core.V[Y];
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

void Chip8tleVM::SNE_9xy0() {
	unsigned short X = (opcode & 0x0F00) >> 8;
	unsigned short Y = (opcode & 0x00F0) >> 4;
	if(core.V[X] != core.V[Y]) core.PC += 2
}

void Chip8tleVM::ldnn()
{
	I = opcode & 0x0fff
}

void Chip8tleVM::JP_Bnnn() {
	unsigned short N = (opcode & 0x0FFF);
	core.PC = core.V[0] + N;
}

/* Helper function */
/* Maybe datatypes are wrong */
void Chip8tleVM::Draw_Byte(unsigned char byte, int X, int Y) {
	int i, px;
	for(i=0; i < 8; i++) {
		if ((byte & (0x80 >> i)) != 0) {
			px = (X + j) % SCREEN_W;
			if (ext.screen[Y][px] == 1) 
				V[0xF] = 1;
			ext.screen[Y][px] ^= 1;
		}
	}
}

void Chip8tleVM::DRW_Dxyn() {
	unsigned char byte;
	unsigned short X = (opcode & 0x0F00) >> 8;
	unsigned short Y = (opcode & 0x00F0) >> 4;
	unsigned short N = (opcode & 0x000F);

	for (int i=0; i < N; i++) {
		byte = ext.rem[core.I+i];
		this->Draw_Byte(byte, X, (Y + i) % SCREEN_H);
	}
}

void Chip8tleVM::SKNP_ExA1() {
	unsigned short X = (opcode & 0x0F00) >> 8;
	if (!key(V[X])) PC += 2; // Esto no existe (Should be +4) ?
	
	/* Skip next instruction if key with the value of Vx is not pressed.
	Checks the keyboard, and if the key corresponding to the value of Vx is currently in the up position, 
	PC is increased by 2.
	*/
}

void Chip8tleVM::LD_Fx0A() {
	wait_key(V[X]);	// Esto no existe

	/* Wait for a key press, store the value of the key in Vx.
	All execution stops until a key is pressed, then the value of that key is stored in Vx.
	*/
}

void Chip8tleVM::LD_Fx18() {
	unsigned short X = (opcode & 0x0F00) >> 8;
	core.ST = (char) V[X];	// Should i cast or something?
	
	/* Set sound timer = Vx.
	ST is set equal to the value of Vx.
	*/
}

void Chip8tleVM::LD_Fx29() {
	unsigned short X = (opcode & 0x0F00) >> 8;
	core.I = font_addr(V[X]);	// Esto no existe
	/* Set I = location of sprite for digit Vx.
	The value of I is set to the location for the hexadecimal sprite corresponding to the value of Vx. 
	See section 2.4, Display, for more information on the Chip-8 hexadecimal font.
	*/
}

void Chip8tleVM::LD_Fx55() {
	unsigned short X = (opcode & 0x0F00) >> 8;
	for (int i=0; i < X; i++) {
		ext.rem[core.I+i] = V[i];
	}
	/* Store registers V0 through Vx in memory starting at location I.
	The interpreter copies the values of registers V0 through Vx into memory, 
	starting at the address in I.
	*/
}

#endif