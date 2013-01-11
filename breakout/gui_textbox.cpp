#include "gui_textbox.hpp"

void GUI_Textbox::Update(int mx,int my,int mst){

	if(mx >= x && mx <= x+w && my >= y && my <= y+h){
		if(mst == 1){
			focused = true;
			SDL_EnableUNICODE(SDL_ENABLE);
		}
	}else{
		if(mst == 1){
			focused = false;
			SDL_EnableUNICODE(SDL_DISABLE);
		}
	}
	//break a line
	if(line.length() >= cols || line_break){
		text.push_back(line);
		line = "";
		line_break = false;
	}
}

void GUI_Textbox::Draw(SDL_Surface* dest){
	SDL_Color tcol = {0,0,0};
	if(focused){
		SDL_FillRect(box_surf,NULL,SDL_MapRGB(box_surf->format,128,128,255));
		tcol.r = tcol.g = tcol.b = 255;
	}else{
		SDL_FillRect(box_surf,NULL,SDL_MapRGB(box_surf->format,192,192,192));
		tcol.r = tcol.g = tcol.b = 0;
	}

	int yoff = 0;

	std::deque<std::string>::iterator itrt;

	for(itrt = text.begin();itrt != text.end();++itrt){
		//SDL_Color col = {0,0,0};

		std::string data = (*itrt);

		SDL_Surface* data_surf = TTF_RenderText_Solid(fnt,data.c_str(),tcol);
		SDL_Rect ofst;

		ofst.x = 0;
		ofst.y = yoff;

		Surface::Blit(data_surf,0,0,data_surf->w,data_surf->h,box_surf,0,yoff);

		yoff +=ptsize;

		SDL_FreeSurface(data_surf);
	}


	Font::Blit(box_surf,0,yoff,fnt,tcol,line.c_str());
	Surface::Blit(box_surf,0,0,w,h,dest,x,y);
}

void GUI_Textbox::HandleInputEvent(SDL_Event* e){
	switch(e->type){
	case SDL_KEYDOWN:
		if(focused && can_in){
			if(text.size() < rows){
				Uint16 in_ch = e->key.keysym.unicode;
				if( (in_ch == (Uint16)' ') || (in_ch >= (Uint16)'a' && in_ch <= (Uint16)'z') || (in_ch >= (Uint16)'A' && in_ch <= (Uint16)'Z') || (in_ch >= (Uint16)'0' && in_ch <= (Uint16)'9') ){
					line += (char)in_ch;
					can_in = false;
				}

				if( in_ch >= 0 && in_ch < 256){
					if(ispunct(in_ch)){
						line += (char)in_ch;
						can_in = false;
					}
				}

				if(e->key.keysym.sym == SDLK_RETURN){
					line_break = true;
					can_in = false;
				}
			}
			if(e->key.keysym.sym == SDLK_BACKSPACE){
				if(line == "" && !text.empty()){
					line = text.back();
					text.pop_back();
				}
				if(line.length() > 0){
					line.erase(line.length() - 1);
					can_in = false;
				}
			}
		}
		break;
	case SDL_KEYUP:
		can_in = true;
		break;
	}
}