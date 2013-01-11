#include "menu.hpp"

Menu::Menu(std::string n,TTF_Font* f,int ptsz,int pw,int ph,int pbpp){
	SetName(n);
	font = f;
	ptsize = ptsz;
	mx = 0; my = 0; mst = 0;
	width = pw;
	height = ph;
	bpp = pbpp;
	newGame = false;
	editor = false;

	draw_surf = SDL_CreateRGBSurface(SDL_SWSURFACE,width,height,bpp,0,0,0,0);

	buttons.push_back(new GUI_Button("main_button_start",(width/2) - 64,10,128,64,"media/img/play_btn.bmp"));
	buttons.push_back(new GUI_Button("main_button_editor",(width/2) - 64,100,128,64,"media/img/edit_btn.bmp"));
	buttons.push_back(new GUI_Button("main_button_quit",(width/2) - 64,190,128,64,"media/img/quit_btn.bmp"));

}

Menu::~Menu(){
	while(!buttons.empty()){
		GUI_Button * b = buttons.back();
		delete b;
		buttons.pop_back();
	}

	if(draw_surf != NULL){
		SDL_FreeSurface(draw_surf);
	}
}

void Menu::Run(){
	if(run){
		std::vector<GUI_Button*>::iterator itr;

		for(itr = buttons.begin(); itr!=buttons.end();itr++){
			GUI_Button* b = (*itr);
			b->Update(mx,my,mst);
			if(b->GetName() == "main_button_quit"){
				if(b->GetState() == BTT_PRESSED){
					halt = true;
				}
			}else if(b->GetName() == "main_button_start"){
				if(b->GetState() == BTT_PRESSED){
					newGame = true;
					mx = 0; my = 0; mst = 0;
					break;
				}
			}else if(b->GetName() =="main_button_editor"){
				if(b->GetState() == BTT_PRESSED){
					editor = true;
					mx = 0; my = 0; mst = 0;
					break;
				}
			}
		}
	}
}

void Menu::Draw(SDL_Surface* screen){
	std::vector<GUI_Button*>::iterator itr;

	SDL_FillRect(draw_surf,NULL,SDL_MapRGB(draw_surf->format,255,204,102));

	for(itr = buttons.begin(); itr!=buttons.end();itr++){
		(*itr)->Blit(draw_surf);
	}

	Surface::Blit(draw_surf,0,0,width,height,screen,0,0);
}

void Menu::OnEvent(SDL_Event* e){
	switch(e->type){
	case SDL_MOUSEMOTION:
		mx = e->motion.x;
		my = e->motion.y;
		break;
	case SDL_MOUSEBUTTONDOWN:
		mst = 1;
		break;
	case SDL_MOUSEBUTTONUP:
		mst = 0;
		break;
	}
}

int Menu::Listen(){
	if(halt){ halt = false;return -1; }
	if(newGame){ newGame = false; return 2;}
	if(editor){ editor = false; return 3;}
	return 0;
}