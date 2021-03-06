#ifndef Chip8tleC8re
#define Chip8tleC8re

#include <stdio.h>

typedef struct
{
		//Registers					Description																	bits
		unsigned char V[16]; 		//Vx x={0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F} register VF register is a Flag 	8bits/ea
		unsigned short I;			//Store Memory Addresses 													16bits
		unsigned short PC			//Program counter 															16bits
		unsigned char SP			//Stack Pointer 															8bits
		unsigned char DT;  			//Delay Timer 																8bits
		unsigned char ST; 			//Sound Timer 																8bits
		unsigned short stack[16];	//Stack for PC																16bits/ea

		//methods
		 Chip8tleCoreConstructor();
}Chip8tleCore;

Chip8tleCoreConstructor()
{
	PC = 0x200;
	I  = 0;
	SP = 0;
}


typedef struct {
	unsigned char rem[4096];					// Memory Ram
	unsigned char screen[SCREEN_H][SCREEN_W];	// Screen Pixels
	unsigned char key[16];						//key pressed
}Chip8tleExt;

#endif
