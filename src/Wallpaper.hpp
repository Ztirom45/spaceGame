class wallpaper{
	public:
		std::string costume;
		int xpos = 0;
		
		void init(std::string new_costume){
			costume = new_costume;
		}
		
		void draw(int pos){
			draw_image("img/Background.png",{244+pos+xpos,194},2);
			draw_image(costume,{250+pos+xpos,200});
		};
};

class wallpapers{
	public:
		std::vector<wallpaper> my_wallpapers;
		
		int xpos = 0;
		int xpos_goal = 0;
		int speed = 20;
		
		
		
		void init(std::vector<std::string> new_wallpapers){
			my_wallpapers.resize(new_wallpapers.size());
			int xposes = -600;
			
			for(int i=0;i<new_wallpapers.size();i++){
				my_wallpapers[i].init(new_wallpapers[i]);
				my_wallpapers[i].xpos = xposes;
				xposes += 600;
			}
		}
		
		void draw(){
			for(int i=0;i<my_wallpapers.size();i++){
				my_wallpapers[i].draw(xpos);
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
	
};
