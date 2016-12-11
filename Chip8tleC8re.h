#ifndef Chip8tleC8re
#define Chip8tleC8re

#include <iostream>

class Chip8tleCore
{
	
	private:
		//Registers					Description																	bits
		unsigned char V[16]; 		//Vx x={0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F} register VF register is a Flag 	8bits/ea
		unsigned short I;			//Store Memory Addresses 													16bits
		unsigned short PC			//Program counter 															16bits
		unsigned char SP			//Stack Pointer 															8bits
		unsigned char DT;  			//Delay Timer 																8bits
		unsigned char ST; 			//Sound Timer 																8bits
		unsigned short stack[16];	//Stack for PC																16bits/ea
		unsigned short opcode 		//Opcode 																	16bits

	public:
		//methods
		Chip8tleCore();
		~Chip8tleCore();
		//Opcodes
		void (*opcoder[35])();

	private:	
		void sys();
		void ret();
		void call();
		void sne_kk();
		void ld_kk();
		void ld_y0();
		void And();
};

void Chip8tleCore::sys()
{
	PC = (opcode & 0x0fff);
}

void Chip8tleCore::ret()
{
	SP--;
	PC = stack[SP];
}

void Chip8tleCore::call()
{
	stack[SP] = PC;
	PC = (opcode & 0x0fff);
	SP++;
}

void Chip8tleCore::sne_kk()
{
	if(V[(opcode & 0x0f00) >> 8] != (opcode & 0x00ff))
	{
		PC = PC+2;
	}
}

void Chip8tleCore::ld_kk()
{
	V[(opcode & 0x0f00) >> 8] = (opcode & 0x00ff); 
}

void Chip8tleCore::ld_y0()
{
	V[(opcode & 0x0f00) >> 8] = V[(opcode & 0x00f0) >> 4]; 
}

void Chip8tleCore::And()
{
	V[(opcode & 0x0f00) >> 8] = V[(opcode & 0x0f00) >> 8] & V[(opcode & 0x00f0) >> 4]; 
}

Chip8tleCore::Chip8tleCore()
{
	PC = 0x200;
	I = 0;
	SP = 0;
	opcode = 0;

	opcoder =
	{
		sys,ret,call,sne_kk,ld_kk,ld_y0,And
	};
}

#endif