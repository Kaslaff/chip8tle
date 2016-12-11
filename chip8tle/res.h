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
		void addy4();
		void shr();
		void shl();
		void ldnn();
};

Chip8tleCore::Chip8tleCore()
{
	PC = 0x200;
	I = 0;
	SP = 0;
	opcode = 0;

	opcoder =
	{
		sys, ret, call, sne_kk, ld_kk, ld_y0, And, addy4, shr, shl, ldnn
	};
}


class Chip8tleExt {

public:
	unsigned char rem[4096];					// Memory Ram 
	unsigned char screen[SCREEN_H][SCREEN_W];	// Screen Pixels 
};

#endif