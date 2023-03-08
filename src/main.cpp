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
static int GameEndEvent = 0;


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
				if(event.key.keysym.sym<256){keys[event.key.keysym.sym] = true;}
				break;
			case SDL_KEYUP:
				if(event.key.keysym.sym<256){keys[event.key.keysym.sym] = false;}
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
	game my_game;
	my_game.init();

	icon_bar live_bar;
	live_bar.init(10,"img/LiveOn.png","img/LiveOff.png");
	
	while(loop){
		//update
		events();
		if(my_game.update(&my_player.my_shot)){
			my_player.update(&my_game.my_levels[my_game.level_now].my_shots);
			my_sky.update();
			live_bar.update(my_player.lives);
		}
		
		//clear
		SDL_RenderClear(rend);
		
		
		//render screen
		my_sky.draw();
		my_player.draw();
		my_game.draw();
		live_bar.draw();
		
		SDL_RenderPresent(rend);
		SDL_Delay(1000/60);//60 fps
	}
	switch(GameEndEvent){
		case 1:
			SDL_RenderClear(rend);
			fill_screen("img/Lose.png");
			SDL_RenderPresent(rend);
			SDL_Delay(1000);
			break;
		case 2:
			SDL_RenderClear(rend);
			fill_screen("img/Win.png");
			SDL_RenderPresent(rend);
			SDL_Delay(1000);
			break;
	}
	
	distroy_images();
	SDL_Quit();
}
