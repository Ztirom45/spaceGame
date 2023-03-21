typedef struct _GameModeInit{
	std::string costume;
	int my_GameMode;
}GameModeInit;

class GameMode{
	public:
		std::string costume;
		int xpos = 0;
		int my_GameMode = 0;
		void init(GameModeInit var){
			costume = var.costume;
			my_GameMode = var.my_GameMode;
		}
		
		void draw(int pos){
			draw_image("img/Background.png",{244+pos+xpos,194},2);
			draw_image(costume,{250+pos+xpos,200});
		};
		void end(){
			switch(my_GameMode){
				case 0://normal mode
					loop = true;
					break;
				case 1://Harcore mode
					loop = true;
					my_player.lives = 1;
					break;
			}
			
		}
		
};

class GameModes{
	public:
		std::vector<GameMode> my_GameModes;
		
		int xpos = 0;
		int xpos_goal = 0;
		int speed = 20;
		
		
		
		void init(std::vector<GameModeInit> new_GameModes){
			my_GameModes.resize(new_GameModes.size());
			int xposes = -600;
			
			for(int i=0;i<new_GameModes.size();i++){
				
				my_GameModes[i].init(new_GameModes[i]);
				my_GameModes[i].xpos = xposes;
				//my_GameModes[i].function_ptr = function1;
				xposes += 600;
			}
		}
		
		void draw(){
			for(int i=0;i<my_GameModes.size();i++){
				my_GameModes[i].draw(xpos);
			}
		}
		
		void update(){
			if(xpos>xpos_goal){
				xpos-=speed;
			}
			if(xpos<xpos_goal){
				xpos+=speed;
			}
		}
		
		void end(){
			for(int i=0;i<my_GameModes.size();i++){
				if(my_GameModes[i].xpos+xpos==0){
					my_GameModes[i].end();
					break;
				}
		}
		}
	
};
