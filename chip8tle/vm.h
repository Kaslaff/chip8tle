#ifndef Chip8tle
#define Chip8tle

#include <stdio.h>
#include "res.h"
#include <stdlib.h>
#include <time.h>

#define SCREEN_H 32
#define SCREEN_W 64

/* Virtual Machine class */
/* Should be PC += 2 OR PC += 4 when skip ? */

typedef struct{


	Chip8tleVMConstructor();

	Chip8tleCore core;	// Super Core
	Chip8tleExt ext;	// External

	// Opcoder
	unsigned short opcode 	//	Opcode 	16 bits
	void (*opcoder[35])();	//	Opcode table

private:
	void CLS_00E0();
	void RET_00EE();
	void SYS_0nnn();
	void JP_1nnn();
	void CALL_2nnn();
	void SE_3xkk();
	void SNE_4xkk();
	void SE_5xy0();
	void LD_6xkk();
	void ADD_7xkk();
	void LD_8xy0();
	void OR_8xy1();
	void AND_8xy2();
	void XOR_8xy3();
	void ADD_8xy4();
	void SUB_8xy5();
	void SHR_8xy6();
	void SUBN_8xy7();
	void SHL_8xyE();
	void SNE_9xy0();
	void LD_Annn();
	void JP_Bnnn();
	void RND_Cxkk();
	void DRW_Dxyn();
	void SKP_Ex9E();
	void SKNP_ExA1();
	void LD_Fx07();
	void LD_Fx0A();
	void LD_Fx15();
	void LD_Fx18();
	void ADD_Fx1E();
	void LD_Fx29();
	void LD_Fx33();
	void LD_Fx55();
	void LD_Fx65();

	// Maybe not the datatypes
	void Draw_Byte(unsigned char, int, int);
}Chip8tleVM;

Chip8tleVMConstructor() {
	srand (time(NULL));
	this->opcode  = 0;
	this->opcoder = {	// 5 x 7 !!!!
		CLS_00E0 , RET_00EE, SYS_0nnn , JP_1nnn , CALL_2nnn,
		SE_3xkk  , SNE_4xkk, SE_5xy0  , LD_6xkk , ADD_7xkk ,
		LD_8xy0  , OR_8xy1 , AND_8xy2 , XOR_8xy3, ADD_8xy4 ,
		SUB_8xy5 , SHR_8xy6, SUBN_8xy7, SHL_8xyE, SNE_9xy0 ,
		LD_Annn  , JP_Bnnn , RND_Cxkk , DRW_Dxyn, SKP_Ex9E ,
		SKNP_ExA1, LD_Fx07 , LD_Fx0A  , LD_Fx15 , LD_Fx18  ,
		ADD_Fx1E , LD_Fx29 , LD_Fx33  , LD_Fx55 , LD_Fx65
	};
	this->core = Chip8tleCore();
	this->ext  = Chip8tleExt();
	// Y lo demas (Creo que mas nada)
}

// Por aqui los metodos de cada opcode
void SKP_Ex9E()
{
	if(ext.key[core.V[(opcode & 0x0f00)>>8]] == 1)
	{
		core.PC + 2;
	}
}

void LD_Fx65()
{
	for(int i = 0;i<=((opcode & 0x0f00) >> 8);i++)
	{
		core.V[i] = ext.rem[core.I+i];
	}
}

void LD_Fx33()
{
	ext.rem[core.I] = core.V[(opcode & 0x0f00) >> 8] % 100;
	ext.rem[core.I+1] = (core.V[(opcode & 0x0f00) >> 8] /10)%10;
	ext.rem[core.I+2] = core.V[(opcode & 0x0f00) >> 8] % 10;
}

void ADD_Fx1E()
{
	core.I = core.V[(opcode & 0x0f00) >> 8] + core.I;
}

void LD_Fx15()
{
	core.DT = core.V[(opcode & 0x0f00) >> 8];
}


void LD_Fx07()
{
	core.V[(opcode & 0x0f00) >> 8] = core.DT;
}

void RND_Cxkk()
{
	core.V[(opcode & 0x0f00) >> 8] = rand()%256 & (opcode & 0x00ff);
}

void SYS_0nnn()
{
	core.PC = (opcode & 0x0fff);
}

void CLS_00E0() {

	int i, j;
	for(i=0; i < SCREEN_W; i++) {
		for(j=0; j < SCREEN_H; j++) {
			ext.screen[i][j] = 0
		}
	}
}

void RET_00EE()
{
	core.SP--;
	core.PC = core.stack[core.SP];
}

void JP_1nnn() {
	core.PC = opcode & 0x0FFF;
}

void CALL_2nnn()
{
	core.stack[core.SP] = core.PC;
	core.PC = (opcode & 0x0fff);
	core.SP++;
}

void SE_3xkk() {
	unsigned short t1 = core.V[(opcode & 0x0F00) >> 8];
	unsigned short t2 = opcode & 0x00FF;
	if(t1 == t2) PC += 2;
}

void SNE_4xkk()
{
	if(core.V[(opcode & 0x0f00) >> 8] != (opcode & 0x00ff))
	{
		core.PC = core.PC+2;
	}
}

void SE_5xy0() {
	unsigned short X = (opcode & 0x0F00) >> 8;
	unsigned short Y = (opcode & 0x00F0) >> 4;
	if(core.V[X] == core.V[Y]) core.PC += 2;
}

void LD_6xkk()
{
	core.V[(opcode & 0x0f00) >> 8] = (opcode & 0x00ff);
}

void ADD_7xkk() {
	unsigned short X  = (opcode & 0x0F00) >> 8;
	unsigned short KK = (opcode & 0x00FF);
	core.V[X] += core.KK;
}

void LD_8xy0()
{
	core.V[(opcode & 0x0f00) >> 8] = core.V[(opcode & 0x00f0) >> 4];
}

void OR_8xy1() {
	unsigned short X = (opcode & 0x0F00) >> 8;
	unsigned short Y = (opcode & 0x00F0) >> 4;
	core.V[X] |= core.V[Y];
}

void AND_8xy2()
{
	core.V[(opcode & 0x0f00) >> 8] = core.V[(opcode & 0x0f00) >> 8] & core.V[(opcode & 0x00f0) >> 4];
}

void XOR_8xy3() {
	unsigned short X = (opcode & 0x0F00) >> 8;
	unsigned short Y = (opcode & 0x00F0) >> 4;
	core.V[X] ^= core.V[Y];
}

void ADD_8xy4()
{
	core.V[(opcode & 0x0f00) >> 8] = (core.V[(opcode & 0x0f00) >> 8] + core.V[(opcode & 0x00f0) >> 4]) & 0x00ff;
	if((core.V[(opcode & 0x0f00) >> 8] + core.V[(opcode & 0x00f0) >> 4]) > 0xff)
		core.V[0xf] = 0x01;
}

void SUB_8xy5() {
	unsigned short X = (opcode & 0x0F00) >> 8;
	unsigned short Y = (opcode & 0x00F0) >> 4;
	core.V[X] -= core.V[Y];
}

void SHR_8xy6()
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

void SUBN_8xy7() {
	unsigned short X = (opcode & 0x0F00) >> 8;
	unsigned short Y = (opcode & 0x00F0) >> 4;
	core.V[0xF] = (core.V[X] > core.V[Y]) ? 1 : 0;
	core.V[X] -= core.V[Y];
}

void SHL_8xyE()
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

void SNE_9xy0() {
	unsigned short X = (opcode & 0x0F00) >> 8;
	unsigned short Y = (opcode & 0x00F0) >> 4;
	if(core.V[X] != core.V[Y]) core.PC += 2
}

void LD_Annn()
{
	core.I = opcode & 0x0fff
}

void JP_Bnnn() {
	unsigned short N = (opcode & 0x0FFF);
	core.PC = core.V[0] + N;
}

/* Helper function */
/* Maybe datatypes are wrong */
void Draw_Byte(unsigned char byte, int X, int Y) {
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

void DRW_Dxyn() {
	unsigned char byte;
	unsigned short X = (opcode & 0x0F00) >> 8;
	unsigned short Y = (opcode & 0x00F0) >> 4;
	unsigned short N = (opcode & 0x000F);

	for (int i=0; i < N; i++) {
		byte = ext.rem[core.I+i];
		this->Draw_Byte(byte, X, (Y + i) % SCREEN_H);
	}
}

void SKNP_ExA1() {
	unsigned short X = (opcode & 0x0F00) >> 8;
	if (!key(V[X])) PC += 2; // Esto no existe (Should be +4) ?

	/* Skip next instruction if key with the value of Vx is not pressed.
	Checks the keyboard, and if the key corresponding to the value of Vx is currently in the up position,
	PC is increased by 2.
	*/
}

void LD_Fx0A() {
	wait_key(V[X]);	// Esto no existe

	/* Wait for a key press, store the value of the key in Vx.
	All execution stops until a key is pressed, then the value of that key is stored in Vx.
	*/
}

void LD_Fx18() {
	unsigned short X = (opcode & 0x0F00) >> 8;
	core.ST = (char) V[X];	// Should i cast or something?

	/* Set sound timer = Vx.
	ST is set equal to the value of Vx.
	*/
}

void LD_Fx29() {
	unsigned short X = (opcode & 0x0F00) >> 8;
	core.I = font_addr(V[X]);	// Esto no existe
	/* Set I = location of sprite for digit Vx.
	The value of I is set to the location for the hexadecimal sprite corresponding to the value of Vx.
	See section 2.4, Display, for more information on the Chip-8 hexadecimal font.
	*/
}

void LD_Fx55() {
	unsigned short X = (opcode & 0x0F00) >> 8;
	for (int i=0; i < X; i++) {
		ext.rem[core.I+i] = V[i];
	}
	/* Store registers V0 through Vx in memory starting at location I.
	The interpRET_00EEer copies the values of registers V0 through Vx into memory,
	starting at the address in I.
	*/
}

#endif
