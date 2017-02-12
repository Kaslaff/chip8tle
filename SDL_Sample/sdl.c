#include <stdio.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 1280 	//x20
#define SCREEN_HEIGHT 704 	//x22

//Starts up SDL and creates window
void init();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

int main()
{
	SDL_Event e;
	SDL_Rect *rect = NULL;
	int quit = 0;
	int directionx,directiony;

	rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));

	rect->x=0;
	rect->y=0;
	rect->w=20;
	rect->h=20;

	init();

	//While application is running
	while( !quit )
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = 1;
			}
		}

		//Clear screen
		SDL_RenderClear( gRenderer );
		SDL_SetRenderDrawColor( gRenderer, 0x0, 0x0, 0x0, 0xff);
		SDL_RenderFillRect(gRenderer,rect);
		SDL_SetRenderDrawColor( gRenderer, 0xff, 0xff, 0xff, 0xff);

		if(rect->x == 0)
		{
			directionx = 1;
		}
		else if(rect->x == SCREEN_WIDTH-20)
		{
			directionx= 0;
		}

		if(rect->y == 0)
		{
			directiony = 1;
		}
		else if(rect->y == SCREEN_HEIGHT-20)
		{
			directiony= 0;
		}

		if(directionx)
			(rect->x)++;
		else
			(rect->x)--;

		if(directiony)
			(rect->y)++;
		else
			(rect->y)--;

		//Update screen
		SDL_RenderPresent( gRenderer );
		SDL_Delay(10);
	}
	free(rect);
	close();
	return 0;
}

void init()
{
	//Initialize SDL
	SDL_Init( SDL_INIT_VIDEO );

	gWindow = SDL_CreateWindow("Chip8tle",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);

	//Create renderer for window
	gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );

	//Initialize renderer color
	SDL_SetRenderDrawColor( gRenderer, 0xff, 0xff, 0xff, 0xff);
}

void close()
{
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	//Quit SDL subsystems
	SDL_Quit();
}
