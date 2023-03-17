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
static bool quit = false;
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
#include "Buttons.hpp"



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
				quit = true;
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

void Menu(){
	bool play = false;
	bool skip = false;
	bool back = false;

	button button1;
	button button2;
	button button3;

	button1.init(1,{360,760});
	button2.init(2,{460,760});//middle of screen
	button3.init(0,{560,760});
	
	while(loop){
		events();
		
		if(keys[KEY_SPACE]){
			play = true;
			loop = false;
		}
		if(keys[KEY_A]){
			back = true;
		}
		if(keys[KEY_D]){
			skip = true;
		}
		
		
		//draw
		SDL_RenderClear(rend);
		SDL_SetRenderDrawColor(rend, 38, 38, 38, 255);
		
		
		draw_image("img/Background.png",{244,194},2);
		draw_image("img/Background.png",{244-600,194},2);
		draw_image("img/Background.png",{244+600,194},2);
		
		draw_image("img/NormalMode.png",{250,200});
		draw_image("img/NormalMode.png",{250-600,200});
		draw_image("img/NormalMode.png",{250+600,200});
		
		button1.draw(back);
		button2.draw(play);
		button3.draw(skip);
		
		SDL_RenderPresent(rend);
		SDL_Delay(1000/60);
		
		if(play||back||skip){
			SDL_Delay(250);
			play = false;
			back = false;
			skip = false;
			}
	}
	if(!quit){loop = true;}
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
	
	Menu();
	
	while(loop){
		//update
		events();
		if(my_game.update(&my_player.my_shot)){
			my_player.update(&my_game.my_levels[my_game.level_now].my_shots);
			my_sky.update();
			live_bar.update(my_player.lives);
		}
		
		//clear
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
		SDL_RenderClear(rend);
		
		
		//render screen
		my_sky.draw();
		my_player.draw();
		if(my_game.tick_delay<=0){my_game.draw();}
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
