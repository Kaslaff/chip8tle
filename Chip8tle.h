#ifndef Chip8tle
#define Chip8tle

#include <iostream>

class Chip8tle
{
	private:
		//Ram and Screen (Metal parts)
		unsigned char rem[4096];			//Ram 
		unsigned char screen[32][64];		//Screen Pixels 
};

#endif