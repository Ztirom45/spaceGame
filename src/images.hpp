#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include <string>
#include <map>
#include <dirent.h>


std::map<std::string, SDL_Texture*> texture_dict;

SDL_Surface* texture_list[IMAGE_COUNT] = {};


void load_images(){
	if (auto dir = opendir("img")) {
		while (auto f = readdir(dir)) {
			if (!f->d_name || f->d_name[0] == '.')
				continue; // skip hidden files
			
			SDL_Surface* surface 	= IMG_Load(f->d_name);
			texture_dict[f->d_name] = SDL_CreateTextureFromSurface(rend, surface);
			printf("Includet File: %s\n", f->d_name);
		}
		closedir(dir);
	}
	
}

void distroy_images(){
	
}
