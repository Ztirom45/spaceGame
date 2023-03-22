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
			SDL_RenderCopy(rend,textures[costume],&rect_img, &rect_dsp);
		};
};

class icon_bar{
	//a class to create for example live bars
	public:
		std::vector<particel> icons;
		int icon_dst = 10;//distance betwen every icon
		
		std::string icon_on;
		std::string icon_off;
		
		
		void init(int icon_count,std::string new_icon_on,std::string new_icon_off){
			icon_on  = new_icon_on;
			icon_off = new_icon_off;
			
			icons.resize(icon_count);
			for(int i=0;i<icons.size();i++){
				icons[i].init(icon_on);
				icons[i].rect_dsp.x = WIN_W-((i+1)*30);
				icons[i].rect_dsp.y = 10;
			}
		}
		
		void update(int bar_value){
				for(int i=0;i<icons.size();i++){
					if(i<bar_value){
						icons[i].costume = icon_on;
					}else{
						icons[i].costume = icon_off;
					}
				}
		}
		
		void draw(){
			for(int i=0;i<icons.size();i++){
				icons[i].draw();
			}
		}
};

class entity:public particel{
	public:
		std::vector<int> path = {1};//1:Up 2:Down 3:Left 4:Right
		int path_pos = 1;
		vec2f pos = {0,0};
		float speed = 10;
		
		void update(){
			if(path.size()<=path_pos){
				
				path_pos = 0;
			}
			switch(path[path_pos++]){
				case 1:pos.y-=speed;break;//Up
				case 3:pos.x+=speed;break;//Down
				case 2:pos.y+=speed;break;//Left
				case 4:pos.x-=speed;break;//Right
			}
			printf("%f %d\n",pos.y,speed);
			rect_dsp.x=pos.x;
			rect_dsp.y=pos.y;
		};
};

class basic_shots{
	public:
		std::vector<entity> shots = {};
		int dirc;
		std::string costume = "img/Shot2.png";
		
		void add(int x,int y){
			int new_size = shots.size();
			shots.resize(new_size+1);
			shots[new_size] = {};
			shots[new_size].init(costume);
			shots[new_size].path = {dirc};
			
			
			shots[new_size].pos.x = x-shots[new_size].rect_dsp.w;
			shots[new_size].pos.y = y-shots[new_size].rect_dsp.h;
		}
		void shot(int x,int y){//player 4x shot
			add(x+25,y+55);
			add(x+83,y+55);
			
			add(x+67,y+40);
			add(x+39,y+40);
		}
		void shot2(int x,int y){//enimy 4x shot
			add(x+13,y+80);
			add(x+70,y+80);
			
			add(x+26,y+70);
			add(x+57,y+70);
		}
		void shot3(int x,int y){//enimy 2x shot
			add(x+13,y+80);
			add(x+70,y+80);
		}
		
		void del(int Array_pos){
			//toggle pos and last position in array
			entity var = shots[shots.size()-1];
			
			shots[shots.size()-1] = shots[Array_pos];
			shots[Array_pos] 			= var;
			
			//del last shot(shot[pos] before)
			shots.resize(shots.size()-1);
		}
		
		std::vector<vec2i>get_pos(){
			std::vector<vec2i>ret_pos;
			ret_pos.resize(shots.size()-1);
			for(int i=0;i<shots.size();i++){
				ret_pos[i].x = shots[i].pos.x;
				ret_pos[i].y = shots[i].pos.y;
			}
			return ret_pos;
		}
		
		void init(std::string new_costume,int new_dirc){
			dirc = new_dirc;
			costume = new_costume;
			shots.resize(0);
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
				if(shots[i].rect_dsp.y<0||shots[i].rect_dsp.y>WIN_H){
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
		int HitTickCounter = 0;
		int shot_mode = 1;
		std::string costume_hit;
		int lives = 10;
		void create_path(std::vector<vec2i> new_path){//{value,steps}
			
			path.resize(0);
			int c = 0;
			for(int i=0;i<new_path.size();i++){
				path.resize(c+new_path[i].y);
				for(int j=0;j<new_path[i].y;j++){
					path[c++] = new_path[i].x;
				}
			}
			

			
		}
		
		void init(std::string new_costume,std::string new_costume_hit){
			costume = new_costume;
			costume_hit = new_costume_hit;
			rect_dsp.x = 0;
			rect_dsp.y = 0;
			rect_img.x = 0;
			rect_img.y = 0;
			
			create_path({{1,100},{3,100},{2,100},{4,100}});
			speed = 1;
			
			update_texture(costume);
			
			
			
			rect_dsp.x = 20;
			rect_dsp.y = 100;
			
			rect_dsp.w *= 2;
			rect_dsp.h *= 2;
		}
		void draw(){
			if(HitTickCounter>=0){
				HitTickCounter--;
				SDL_RenderCopy(rend,textures[costume_hit],&rect_img, &rect_dsp);
			}
			else{
				SDL_RenderCopy(rend,textures[costume],&rect_img, &rect_dsp);
			}
		};
};

class level{
	public:
		std::vector<enemy> enemys = {};
		basic_shots my_shots;
		//settings for enemy generation
		std::string costume;
		int shot_mode = 1;
		int lives = 10;
		float speed = 1;
		
		void set_enemys(std::vector<enemy> new_enemys){
			enemys.resize(new_enemys.size()-1);
			enemys = new_enemys;
		}
		
		void add_enemys(std::vector<enemy> new_enemys){
			int old_size = enemys.size();
			enemys.resize(old_size+new_enemys.size());
			for(int i=0;i<new_enemys.size();i++){
				enemys[i+old_size] = new_enemys[i];
			}
		}
		
		void set_enemys(std::vector<vec2i> pos){
			std::vector<enemy> new_enemys;
			new_enemys.resize(pos.size());
			for(int i=0;i<new_enemys.size();i++){
				new_enemys[i].init(costume,"img/Enemy_hit.png");
				new_enemys[i].pos.x = pos[i].x;
				new_enemys[i].pos.y = pos[i].y;
				new_enemys[i].shot_mode = shot_mode;
				new_enemys[i].speed = speed;
				new_enemys[i].lives = lives;
			}
			set_enemys(new_enemys);
			
			
		}
		
		void add_enemys(std::vector<vec2i> pos,std::vector<vec2i> path){
			std::vector<enemy> new_enemys;
			new_enemys.resize(pos.size());
			for(int i=0;i<new_enemys.size();i++){
				new_enemys[i].init(costume,"img/Enemy_hit.png");
				new_enemys[i].pos.x = pos[i].x;
				new_enemys[i].pos.y = pos[i].y;
				new_enemys[i].create_path(path);
				new_enemys[i].shot_mode = shot_mode;
				new_enemys[i].speed = speed;
				new_enemys[i].lives = lives;
			}
			add_enemys(new_enemys);
			
			
		}

		void add(int x,int y){
			int new_size = enemys.size();
			enemys.resize(new_size+1);
			enemys[new_size] = {};
			enemys[new_size].init(costume,"img/Enemy_hit.png");
			
			enemys[new_size].pos.x = x-enemys[new_size].rect_dsp.w;
			enemys[new_size].pos.y = y-enemys[new_size].rect_dsp.h;
			enemys[new_size].shot_mode = shot_mode;
			enemys[new_size].speed = speed;
			enemys[new_size].lives = lives;
		}
		
		void add(int x,int y,std::vector<vec2i> path){
			int new_size = enemys.size();
			enemys.resize(new_size+1);
			enemys[new_size].create_path(path);
			enemys[new_size] = {};
			enemys[new_size].init(costume,"img/Enemy_hit.png");
			
			enemys[new_size].pos.x = x-enemys[new_size].rect_dsp.w;
			enemys[new_size].pos.y = y-enemys[new_size].rect_dsp.h;
			enemys[new_size].shot_mode = shot_mode;
			enemys[new_size].speed = speed;
			enemys[new_size].lives = lives;
		}

		void del(int pos){
			//toggle pos and last position in array
			enemy var = enemys[enemys.size()-1];
			
			enemys[enemys.size()-1] = enemys[pos];
			enemys[pos] 			= var;
			
			//del last enemy(enemys[pos] before)
			enemys.resize(enemys.size()-1);
		}
		
		void shot(int i){
			switch(enemys[i].shot_mode){
			case 1://enimy1
				if(rand()%200 == 1){
					printf("1\n");
					if (rand()%5 == 1){
						my_shots.shot2(enemys[i].pos.x,enemys[i].pos.y);
					}else{
						my_shots.shot3(enemys[i].pos.x,enemys[i].pos.y);
					}
				}
				break;
			case 2://enimy2
				if(rand()%50 == 1&&enemys[i].path[enemys[i].path_pos]!=5){
					my_shots.shot2(enemys[i].pos.x,enemys[i].pos.y);
				}
				break;
			}
		}
		
		void init(std::string new_costume){
			costume = new_costume;
			shot_mode = 1;
			speed = 1;
			lives = 10;
			for(int i=0;i<enemys.size();i++){
				enemys[i].init(new_costume,"img/Enemy_hit.png");
				enemys[i].rect_dsp.x = rand()%(WIN_W/2)+100;
				enemys[i].rect_dsp.y = WIN_H;
				enemys[i].rect_dsp.w *= 10;
				enemys[i].rect_dsp.h *= 10;
			}
			my_shots.init("img/Shot2.png",2);
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
							enemys[i].HitTickCounter=3;
							j--;
						}
				}
				//update
				enemys[i].update();
				
				//shot
				shot(i);
				
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

class game{
	public:
		std::vector<level> my_levels;
		int level_now = 0;
		int tick_delay = 100;//if == 0:update else:tick--
		
		void init(){
			my_levels.resize(3);
			level_now = 0;
			tick_delay = 100;
			/*
			----------------------------------------Levels------------------------------------
			*/
			//1
			my_levels[0].init("img/Enemy.png");
			
			my_levels[0].set_enemys(
			{
				{50,200},{150,200},{250,200},{350,200},{450,200},{550,200},{650,200},{750,200},
				{50,300},{150,300},{250,300},{350,300},{450,300},{550,300},{650,300},{750,300}
			});
			//2
			my_levels[1].init("img/Enemy.png");
			
			my_levels[1].set_enemys(
			{
				{150,200},{250,200},{350,200},{450,200},{550,200},{650,200},
						  {250,300},{350,300},{450,300},{550,300},
									{350,400},{450,400}
			});
			//3
			my_levels[2].init("img/Enemy.png");
			
			my_levels[2].set_enemys(
			{
				{500,200},{600,200},{700,200},{800,200},
				{500,300},{600,300},{700,300},{800,300}}
			);
			
			my_levels[2].add_enemys({
				//pos
				{100,200},{200,200},{300,200},{400,200},
				{100,300},{200,300},{300,300},{400,300}}
				//path
				,{{1,100},{4,100},{2,100},{3,100}});
			
			
			my_levels[2].costume = "img/Enemy2.png";
			my_levels[2].shot_mode = 2;
			my_levels[2].speed = 1.5;
			my_levels[2].lives = 20;
			
			my_levels[2].add_enemys({
			//pos
			{400,0},{500,0}}
			//path
			,{{5,150},{2,100},{1,100},{5,50}});
			/*
			----------------------------------------------------------------------------------
			*/
		
		};
		
		void draw(){
			if(!(level_now==my_levels.size())){
				my_levels[level_now].draw();
			}
		};
		
		bool update(basic_shots* shot_pointer){
			if(tick_delay<=0){
				if(level_now==my_levels.size()){
					GameEndEvent = 2;
					loop=false;
					return false;
				}else{
					if(my_levels[level_now].enemys.size() == 0){
						if(++level_now==my_levels.size()){return false;}
						else{tick_delay = 100;}
					}
					my_levels[level_now].update(shot_pointer);
					return true;
				}
			}else{
				tick_delay--;
				return true;
			}
		};
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
