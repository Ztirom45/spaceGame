#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include <string>
#include <map>
#include <dirent.h>
#include <iostream>

static std::map<std::string, SDL_Texture*> textures;



void load_images(){
	
	if (auto dir = opendir("img")) {
		while (auto f = readdir(dir)) {
			if (!f->d_name || f->d_name[0] == '.')
				continue; // skip hidden files
			std::string str(f->d_name);
			str = "img/"+str;
			SDL_Surface* surface 	= IMG_Load(str.c_str());
			textures[str] = SDL_CreateTextureFromSurface(rend, surface);
			std::cout<<"Includet image: " << str << ":\t" << &textures[str] <<"\n";
			SDL_FreeSurface(surface);
		}
		closedir(dir);
	}
	
}

void distroy_images(){
	std::map<std::string, SDL_Texture*>::reverse_iterator i;
	for(i=textures.rbegin(); i!=textures.rend(); ++i){  
		std::cout<<"distroyed: " << (*i).first <<"\n";
		SDL_DestroyTexture((*i).second);
	}  
}

void draw_image(std::string image,vec2i pos){
	SDL_Rect rect_dsp;
	SDL_Rect rect_img;
	
	SDL_QueryTexture(textures[image], NULL, NULL, &rect_dsp.w, &rect_dsp.h);
	SDL_QueryTexture(textures[image], NULL, NULL, &rect_img.w, &rect_img.h);
	
	
	rect_dsp.x = pos.x;
	rect_dsp.y = pos.y;
	rect_img.x = 0;
	rect_img.y = 0;
	
	SDL_RenderCopy(rend,textures[image],&rect_img, &rect_dsp);
}

void draw_image(std::string image,vec2i pos,int scale){
	SDL_Rect rect_dsp;
	SDL_Rect rect_img;
	
	SDL_QueryTexture(textures[image], NULL, NULL, &rect_dsp.w, &rect_dsp.h);
	SDL_QueryTexture(textures[image], NULL, NULL, &rect_img.w, &rect_img.h);
	
	
	rect_dsp.x = pos.x;
	rect_dsp.y = pos.y;
	rect_dsp.w *= scale;
	rect_dsp.h *= scale;
	
	rect_img.x = 0;
	rect_img.y = 0;
	
	SDL_RenderCopy(rend,textures[image],&rect_img, &rect_dsp);
}

void fill_screen(std::string image){
	SDL_Rect rect_dsp;
	rect_dsp.x = 0;
	rect_dsp.y = 0;
	rect_dsp.w = WIN_W;
	rect_dsp.h = WIN_H;
	
	SDL_Rect rect_img;
	rect_img.x = 0;
	rect_img.y = 0;
	rect_img.w = 500;
	rect_img.h = 500;
	
	SDL_RenderCopy(rend,textures[image],&rect_img, &rect_dsp);
}
