#ifndef Chip8tleC8re
#define Chip8tleC8re

#include <iostream>

class Chip8tleCore
{
	
	private:
		//Registers					Description																	bits
		unsigned char v[16]; 		//Vx x={0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F} register VF register is a Flag 	8bits/ea
		unsigned short I;			//Store Memory Addresses 													16bits
		unsigned short PC			//Program counter 															16bits
		unsigned char SP			//Stack Pointer 															8bits
		unsigned char DT;  			//Delay Timer 																8bits
		unsigned char ST; 			//Sound Timer 																8bits
		unsigned short stack[16];	//Stack for PC																16bits/ea
};

#endif