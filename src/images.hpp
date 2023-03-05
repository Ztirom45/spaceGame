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
