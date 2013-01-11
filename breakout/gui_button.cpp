#include"gui_button.hpp"

GUI_Button::GUI_Button(std::string pname,int px,int py,int pw,int ph,char* img_path){
	sx = px;
	sy = py;
	w = pw;
	h = ph;
	s = BTT_NORMAL;
	name = pname;

	regions[BTT_NORMAL].x = 0;regions[BTT_NORMAL].y = 0;
	regions[BTT_NORMAL].w = w;regions[BTT_NORMAL].h = h;

	regions[BTT_HOVER].x = w;regions[BTT_HOVER].y = 0;
	regions[BTT_HOVER].w = w*2;regions[BTT_HOVER].h = h;

	regions[BTT_PRESSED].x = 0;regions[BTT_PRESSED].y = h;
	regions[BTT_PRESSED].w = w;regions[BTT_PRESSED].h = h*2;

	regions[BTT_INACTIVE].x = w;regions[BTT_INACTIVE].y = h;
	regions[BTT_INACTIVE].w = w*2;regions[BTT_INACTIVE].h = h*2;

	img = Surface::Load(img_path);
}

GUI_Button::~GUI_Button(){
	if(img != NULL){
		SDL_FreeSurface(img);
	}
}

void GUI_Button::Blit(SDL_Surface* dst){
	SDL_Rect rg = regions[s];

	Surface::Blit(img,rg.x,rg.y,rg.w,rg.h,dst,sx,sy);
}

void GUI_Button::Update(int mx,int my,int mst){
	if(s == BTT_INACTIVE){ return; }

	if(mx >= sx && mx <= sx+w && my >= sy && my <= sy+h){
		if(mst == 1){
			s = BTT_PRESSED;
		}else{
			s = BTT_HOVER;
		}
	}else{
		s = BTT_NORMAL;
	}
}