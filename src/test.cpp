#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

static SDL_Renderer* rend;

#include "config.hpp"
#include "images.hpp"

int main(int argc, char *argv[])
{
	bool loop  = true;
	//init
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* win = SDL_CreateWindow("ALIEN_DUNGEONS",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1000, 1000, 0);

	//screen var
	Uint32 render_flags = SDL_RENDERER_ACCELERATED;
	rend = SDL_CreateRenderer(win, -1, render_flags);

	//load image
	SDL_Surface* Alien_Surface	= IMG_Load("img/Ztirom.png");
	SDL_Texture* Alien_Texture	= SDL_CreateTextureFromSurface(rend,Alien_Surface);
	
	SDL_FreeSurface(Alien_Surface);
	

	//pos
	SDL_Rect pos;
	pos.w = 1000;
	pos.h = 1000;
	pos.x = 0;
	pos.y = 0;
	int speed = 5;
	
	//texture array select rect
	SDL_Rect Alien_Pos;
	Alien_Pos.x = 0;
	Alien_Pos.y = 0;
	Alien_Pos.w = 1000;//Alien_Texture_Pos.w/IMG_MAP_W;
	Alien_Pos.h = 1000;//Alien_Texture_Pos.h/IMG_MAP_H;

	
	while (loop) {
		
		//draw player
		
		//SDL_RenderCopy(rend,Alien_Texture,&Alien_Pos, &pos);
		SDL_RenderCopy(rend,textures["Ztirom45.png"],&Alien_Pos, &pos);

		// for multiple rendering
		SDL_RenderPresent(rend);

		// calculates to 60 fps
		SDL_Delay(1000 / 60);
	}

	//posroy
	SDL_DestroyTexture(Alien_Texture);
	SDL_DestroyTexture(textures["Ztirom45.png"]);
	SDL_DestroyWindow(win);
	 
	// close SDL
	SDL_Quit();

	return 0;
}
