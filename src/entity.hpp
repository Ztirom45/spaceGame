class particel{
	public:
		SDL_Rect rect_dsp;;	//size and pos on display
		SDL_Rect rect_img;	//pixel positions in images
		std::string costume;  
		int scale = 2;
	
		void update_texture(std::string new_costume){
			costume = new_costume;
			SDL_QueryTexture(textures[costume], NULL, NULL, &rect_dsp.w, &rect_dsp.h);
			SDL_QueryTexture(textures[costume], NULL, NULL, &rect_img.w, &rect_img.h);
			rect_dsp.w *= scale;
			rect_dsp.h *= scale;
			rect_img.w *= scale;
			rect_img.h *= scale;
		};
		
		void init(std::string new_costume){
			costume = new_costume;
			rect_dsp.x = 0;
			rect_dsp.y = 0;
			rect_img.x = 0;
			rect_img.y = 0;
			update_texture(costume);
		};
	
		void draw(){
			SDL_Rect t1;
			SDL_RenderCopy(rend,textures[costume],&rect_img, &rect_dsp);
		};
};

class entity:public particel{
	public:
		std::vector<int> path = {1};//1:Up 2:Down 3:Left 4:Right
		int path_pos = 1;
		
		int speed = 10;
		
		void update(){
			if(path.size()<=path_pos){
				
				path_pos = 0;
			}
			switch(path[path_pos++]){
				case 1:rect_dsp.y-=speed;break;//Up
				case 3:rect_dsp.x+=speed;break;//Down
				case 2:rect_dsp.y+=speed;break;//Left
				case 4:rect_dsp.x-=speed;break;//Right
			}
		};
		
};

class basic_shots{
	public:
		std::vector<entity> shots = {};
		int dirc;
		
		void add(int x,int y){
			int new_size = shots.size();
			shots.resize(new_size+1);
			shots[new_size] = {};
			shots[new_size].init("img/Shot.png");
			shots[new_size].path = {dirc};
			
			
			shots[new_size].rect_dsp.x = x-shots[new_size].rect_dsp.w;
			shots[new_size].rect_dsp.y = y-shots[new_size].rect_dsp.h;
		}
		void shot(int x,int y){
			add(x+25,y+55);
			add(x+83,y+55);
			
			add(x+67,y+40);
			add(x+39,y+40);
		}
		
		void del(int pos){
			//toggle pos and last position in array
			entity var = shots[shots.size()-1];
			
			shots[shots.size()-1] = shots[pos];
			shots[pos] 			= var;
			
			//del last shot(shot[pos] before)
			shots.resize(shots.size()-1);
		}
		
		std::vector<vec2i>get_pos(){
			std::vector<vec2i>pos;
			pos.resize(shots.size()-1);
			for(int i=0;i<shots.size();i++){
				pos[i].x = shots[i].rect_dsp.x;
				pos[i].y = shots[i].rect_dsp.y;
			}
			return pos;
		}
		
		void init(std::string new_costume,int new_dirc){
			dirc = new_dirc;
			printf("%d\n",dirc);
			for(int i=0;i<shots.size();i++){
				shots[i].init(new_costume);
				shots[i].path = {dirc};
				
				shots[i].rect_dsp.x = rand()%(WIN_W/2)+100;
				shots[i].rect_dsp.y = WIN_H;
				
				shots[i].rect_dsp.w *= 10;
				shots[i].rect_dsp.h *= 10;
			}
		}
		void update(){
			for(int i=0;i<shots.size();i++){
				shots[i].update();
				if(shots[i].rect_dsp.y<0){
					del(i);
				}
			}
		}
		void draw(){
			for(int i=0;i<shots.size();i++){
				shots[i].draw();
			}
		}
};

class enemy:public entity{
	public:
		int lives = 10;
		
		void init(std::string new_costume){
			costume = new_costume;
			rect_dsp.x = 0;
			rect_dsp.y = 0;
			rect_img.x = 0;
			rect_img.y = 0;
			update_texture(costume);
			speed = 2;
			path.resize(160);
			for(int i=0;i<40;i++){
				path[i] = 1;
			}
			for(int i=40;i<80;i++){
				path[i] = 3;
			}
			
			for(int i=80;i<120;i++){
				path[i] = 2;
			}
			for(int i=120;i<160;i++){
				path[i] = 4;
			}
			rect_dsp.w /= 20;
			rect_dsp.h /= 20;
	
			rect_dsp.x = 20;
			rect_dsp.y = 100;
		}
};

class level{
	public:
		std::vector<enemy> enemys = {};
		basic_shots my_shots;
		
		void set_enemys(std::vector<enemy> new_enemys){
			enemys.resize(new_enemys.size()-1);
			enemys = new_enemys;
		}
		
		void set_enemys(std::vector<vec2i> pos){
			std::vector<enemy> new_enemys;
			new_enemys.resize(pos.size());
			for(int i=0;i<new_enemys.size();i++){
				new_enemys[i].init("img/Ztirom.png");
				new_enemys[i].rect_dsp.x = pos[i].x;
				new_enemys[i].rect_dsp.y = pos[i].y;
			}
			set_enemys(new_enemys);
			
			
		}
		void add(int x,int y){
			int new_size = enemys.size();
			enemys.resize(new_size+1);
			enemys[new_size] = {};
			enemys[new_size].init("img/Shot.png");
			
			
			enemys[new_size].rect_dsp.x = x-enemys[new_size].rect_dsp.w;
			enemys[new_size].rect_dsp.y = y-enemys[new_size].rect_dsp.h;
		}

		
		void del(int pos){
			//toggle pos and last position in array
			enemy var = enemys[enemys.size()-1];
			
			enemys[enemys.size()-1] = enemys[pos];
			enemys[pos] 			= var;
			
			//del last enemy(enemys[pos] before)
			enemys.resize(enemys.size()-1);
		}
		
		void init(std::string new_costume){
			for(int i=0;i<enemys.size();i++){
				enemys[i].init(new_costume);
				enemys[i].rect_dsp.x = rand()%(WIN_W/2)+100;
				enemys[i].rect_dsp.y = WIN_H;
				enemys[i].rect_dsp.w *= 10;
				enemys[i].rect_dsp.h *= 10;
			}
			my_shots.init("img/Shot.png",2);
		}
		void update(basic_shots* shot_pointer){
			for(int i=0;i<enemys.size();i++){
				//touch shots
				for(int j=0;j<shot_pointer->shots.size();j++){
					SDL_Rect s_rect =  shot_pointer->shots[j].rect_dsp; //rect of current shot
					if(TOUCH_RECT(s_rect.x,s_rect.y,s_rect.w+s_rect.x,s_rect.h+s_rect.y,
						enemys[i].rect_dsp.x,enemys[i].rect_dsp.y,
						enemys[i].rect_dsp.w+enemys[i].rect_dsp.x,enemys[i].rect_dsp.h+enemys[i].rect_dsp.y))
						{
							shot_pointer->del(j);
							enemys[i].lives--;
							j--;
						}
				}
				//update
				enemys[i].update();
				//shot
				if(rand()%100 == 1){
					my_shots.shot(enemys[i].rect_dsp.x,enemys[i].rect_dsp.y);
				}
				//die
				if(enemys[i].lives<=0){
					del(i);
					i--;
				}
				
			}
			my_shots.update();
		}
		void draw(){
			for(int i=0;i<enemys.size();i++){
				enemys[i].draw();
			}
			my_shots.draw();
		}
};

class star:public particel{
	public:
		
		int speed = rand()%5+5;
		
		void init(std::string new_costume){
			costume = new_costume;
			rect_dsp.x = rand()%WIN_W;
			rect_dsp.y = 0;
			rect_img.x = 0;
			rect_img.y = 0;
			
			scale = speed/3;
			update_texture(costume);
			
		};
		void update(){
			rect_dsp.y += speed;
		};
		

};

class sky{
	public:
	
		std::vector<star> stars = {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}};
		void init(){
			for(int i=0;i<stars.size();i++){
				stars[i].init("img/Star.png");
				stars[i].rect_dsp.y = rand()%WIN_H;
			}
		};
		
		void update(){
			if((rand()%2)==1){
				int new_size = stars.size();
				stars.resize(new_size+1);
				stars[new_size] = {};
				stars[new_size].init("img/Star.png");
				
			}
			
			star var;
			for(int i=0;i<stars.size();i++){
				stars[i].update();
				
				if(WIN_H<stars[i].rect_dsp.y){
					//change pos last star and curren star
					var = stars[stars.size()-1];
					
					stars[stars.size()-1] = stars[i];
					stars[i] 			= var;
					
					//del last star(now current star) i--
					stars.resize(stars.size()-1);
					i--;
				}
			}
			
		};
		
		void draw(){
			for(int i=0;i<stars.size();i++){
				stars[i].draw();
			}
		};
};
