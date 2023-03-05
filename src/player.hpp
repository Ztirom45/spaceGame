class player{
	public:
		SDL_Rect rect_dsp;;	//size and pos on display
		SDL_Rect rect_img;	//pixel positions in images
		std::vector<std::string> costumes; //L R M 
		int costume = 0;
		int lives = 10;
		int speed = 10;
		int scale = 2;
		
		basic_shots my_shot;
		int shot_delay = 0;
	
	void update_texture(int new_costume){
		if(costume != new_costume){
			costume = new_costume;
			SDL_QueryTexture(textures[costumes[costume]], NULL, NULL, &rect_dsp.w, &rect_dsp.h);
			SDL_QueryTexture(textures[costumes[costume]], NULL, NULL, &rect_img.w, &rect_img.h);
			rect_dsp.w *= scale;
			rect_dsp.h *= scale;
			rect_img.w *= scale;
			rect_img.h *= scale;
		}
	}
	
	void init(std::vector<std::string> new_costumes){
		costumes = new_costumes;
		rect_dsp.x = 0;
		rect_dsp.y = 0;
		rect_img.x = 0;
		rect_img.y = 0;
		update_texture(2);
		//shots
		my_shot.init("img/Shot.png",1);
	};
	
	void draw(){
		SDL_Rect t1;
		SDL_RenderCopy(rend,textures[costumes[costume]],&rect_img, &rect_dsp);
		//shots
		my_shot.draw();
	};
	
	void update(){
		if(keys[KEY_W]){
			rect_dsp.y -=speed;
		}
		if(keys[KEY_S]){
			rect_dsp.y +=speed;
		}
		if(keys[KEY_A]){
			rect_dsp.x -=speed;
			update_texture(1);
		}else if(keys[KEY_D]){
			rect_dsp.x +=speed;
			update_texture(0);
		}else{
			update_texture(2);
		}
		
		if(lives<=0){
			loop = false;
		}
		
		//shot
		if(shot_delay <= 0){
			if(keys[KEY_SPACE]){
				my_shot.shot(rect_dsp.x,rect_dsp.y);
				shot_delay = 10;
			}
		}else{
			shot_delay--;
		}
		
		my_shot.update();
	}
};
