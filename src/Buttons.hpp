class button{
	public:
		SDL_Rect rect_dsp;;	//size and pos on display
		SDL_Rect rect_img;	//pixel positions in images
		
		void init(int button_num,vec2i pos){
			rect_dsp.x = pos.x;
			rect_dsp.y = pos.y;
			rect_dsp.w = 80;
			rect_dsp.h = 80;
			
			rect_img.x = 0;
			rect_img.y = button_num*ButtonRes;
			rect_img.w = ButtonRes;
			rect_img.h = ButtonRes;
		};
	
		void draw(bool click){
			rect_img.x = click*ButtonRes;
			SDL_RenderCopy(rend,textures["img/Buttons.png"],&rect_img, &rect_dsp);
		};
};
