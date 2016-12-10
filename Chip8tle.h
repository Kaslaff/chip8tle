#ifndef Chip8tle
#define Chip8tle

#include <iostream>
#include "Chip8tleC8re.h"

#define SCREEN_H 32
#define SCREEN_W 64

class Chip8tleCore; /* Creo que era asi */

/* Esta es la clase VM separa la decodificacion
 del core */

class Chip8tleVM {

public:
	 Chip8tleVM();
	~Chip8tleVM();

	// Super Core
	Chip8tleCore core;

	unsigned char rem[4096];					// Memory Ram 
	unsigned char screen[SCREEN_H][SCREEN_W];	// Screen Pixels 

	// Por aqui deberia ir opcoder[35]
}

Chip8tleVM::Chip8tleVM() {
	this->core = Chip8tleCore();
	// Y lo demas
}

// Por aqui los metodos de cada opcode

#endif