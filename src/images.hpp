#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include <string>
#include <map>
#include <dirent.h>
#include <iostream>

std::map<std::string, SDL_Texture*> textures;



void load_images(){
	if (auto dir = opendir("img")) {
		while (auto f = readdir(dir)) {
			if (!f->d_name || f->d_name[0] == '.')
				continue; // skip hidden files
			
			SDL_Surface* surface 	= IMG_Load(f->d_name);
			textures[f->d_name] = SDL_CreateTextureFromSurface(rend, surface);
			printf("Includet image: %s\n", f->d_name);
			SDL_FreeSurface(surface);
		}
		closedir(dir);
	}
	
}

void distroy_images(){
	std::map<std::string, SDL_Texture*>::reverse_iterator i;
	for(i=textures.rbegin(); i!=textures.rend(); ++i){  
		SDL_DestroyTexture((*i).second);
	}  
}
