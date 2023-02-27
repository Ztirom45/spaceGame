#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

//statics
static bool game = true;

//libs
#include "config.hpp"

void init(){
	//init
	SDL_Init(SDL_INIT_EVERYTHING);
	//create window
	SDL_Window* win = SDL_CreateWindow("SpaceGame - a game in space",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIN_W,WIN_H, 0);
	//create renderer
	Uint32 render_flags = SDL_RENDERER_ACCELERATED;
	SDL_Renderer* rend = SDL_CreateRenderer(win,-1,render_flags);
}

int main(){
	init();
	
	while(game){
		SDL_Delay(1000/60);//60 fps
	}
	SDL_Quit();
}
