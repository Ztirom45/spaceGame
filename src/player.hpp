#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include <string>
#include <map>
#include <dirent.h>
#include <iostream>

class player{
	public:
		SDL_Rect rect_dsp;;	//size and pos on display
		SDL_Rect rect_img;	//pixel positions in images
		std::string image;
	
	void init(std::string new_image){
		std::string image = new_image;
		SDL_QueryTexture(textures[image], NULL, NULL, &rect_dsp.w, &rect_dsp.h);
		SDL_QueryTexture(textures[image], NULL, NULL, &rect_img.w, &rect_img.h);
		
	};
	
	void draw(){
		SDL_RenderCopy(rend,textures[image],&rect_img, &rect_dsp);
	};
};
