//SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include <string>
#include <map>
#include <dirent.h>
#include <iostream>
#include <vector>

//mocros
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_SPACE 32

//static vars
static bool loop = true;
static SDL_Renderer* rend;
static bool keys[256];//sizeof Uint8 cant't use non letter keys


//libs
#include "config.hpp"
#include "cvec.hpp"
#include "hitbox.hpp"
#include "images.hpp"
#include "entity.hpp"
#include "player.hpp"



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
				keys[event.key.keysym.sym] = true;
				break;
			case SDL_KEYUP:
				keys[event.key.keysym.sym] = false;
				break;
			default:
				break;
			}
		}
}
int main(){
	init();
	//create sky
	sky my_sky;
	my_sky.init();

	//craete player
	player my_player;
	my_player.init({"img/SpaceShipL.png","img/SpaceShipR.png","img/SpaceShipM.png"});
	
	my_player.rect_dsp.x = 500;
	my_player.rect_dsp.y = 500;
	
	//create enime
	level my_level;
	my_level.init("img/Enemy.png");
	my_level.set_enemys({{100,100},{200,100},{300,100},{400,100},{500,100},{600,100},{700,100},{800,100}});
	

	while(loop){
		//update
		events();
		my_player.update(&my_level.my_shots);
		my_sky.update();
		my_level.update(&my_player.my_shot);
		
		//clear
		SDL_RenderClear(rend);
		
		
		//render screen
		my_sky.draw();
		my_player.draw();
		my_level.draw();
		
		SDL_RenderPresent(rend);
		SDL_Delay(1000/60);//60 fps
	}
	distroy_images();
	SDL_Quit();
}
