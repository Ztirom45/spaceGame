#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

//statics
static bool game = false;
static SDL_Renderer* rend;

//libs
#include "config.hpp"
#include "images.hpp"

void init(){
	//init
	SDL_Init(SDL_INIT_EVERYTHING);
	//create window
	SDL_Window* win = SDL_CreateWindow("SpaceGame - a game in space",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIN_W,WIN_H, 0);
	//create renderer
	Uint32 render_flags = SDL_RENDERER_ACCELERATED;
	rend = SDL_CreateRenderer(win,-1,render_flags);
	
	load_images();
}

int main(){
	init();
	
	while(game){
		
		//render screen
		SDL_RenderPresent(rend);
		SDL_Delay(1000/60);//60 fps
	}
	distroy_images();
	SDL_Quit();
}
