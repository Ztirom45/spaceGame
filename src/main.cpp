
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>



//statics
static bool loop = true;
static SDL_Renderer* rend;
//static bool keys[4294967296];//sizeof Uint32

//libs
#include "images.hpp"
#include "player.hpp"
#include "config.hpp"

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

void events(){
		//events
		SDL_Event event;
		const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);
		while (SDL_PollEvent(&event)) {
			switch (event.type) {

			case SDL_QUIT:
				loop = false;
				break;
			case SDL_KEYDOWN:
				//keys[event.key.keysym.sym] = true;
				break;
			case SDL_KEYUP:
				//keys[event.key.keysym.sym] = false;
				break;
			default:
				break;
			}
		}
}
int main(){
	init();
	player my_player;
	my_player.init("Herz_des_Dschungels.png");
	my_player.rect_dsp.x = 100;
	my_player.rect_dsp.y = 100;
	while(loop){
		//clear
		SDL_RenderClear(rend);
		
		
		//render screen
		my_player.draw();
		SDL_RenderPresent(rend);
		SDL_Delay(1000/60);//60 fps
	}
	distroy_images();
	SDL_Quit();
}
