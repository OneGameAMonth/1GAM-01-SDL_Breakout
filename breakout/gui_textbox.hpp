#ifndef _GUI_TEXTBOX_HPP_
#define _GUI_TEXTBOX_HPP_

#include<SDL.h>
#include<SDL_ttf.h>
#include<string>
#include<deque>
#include<cctype>

#include"surf.hpp"
#include"font.hpp"

class GUI_Textbox{
	int x,y,w,h,rows,cols;
	bool focused,can_in,line_break;
	std::string name;

	std::string line;
	std::deque<std::string> text;

	SDL_Surface* box_surf;

	TTF_Font* fnt;
	int ptsize;

public:
	GUI_Textbox(std::string n,int px,int py,int pw,int ph,int prows,int pcols,TTF_Font* font,int ptsz){
		x = px; y = py; w = pw; h = ph; 
		rows = prows; cols = pcols;
		fnt = font; ptsize  = ptsz;
		name = n;

		focused = false;
		line_break = false;
		can_in = true;

		line = "";

		line.reserve(cols);

		box_surf = SDL_CreateRGBSurface(SDL_SWSURFACE,w,h,32,0,0,0,0);
	}

	~GUI_Textbox(){
		if(box_surf != NULL){
			SDL_FreeSurface(box_surf);
		}
	}

	void Move(int nx,int ny){ x = nx; y = ny; }
	void SetFocus(bool s){ focused = s; }
	void SetName(std::string n){ name = n; }
	void Clear(){
		line = "";
		text.clear();
		focused = false;
	}

	std::string GetName() const{ return name; }
	std::deque<std::string> GetText() const{
		std::deque<std::string> retval = text;

		if(line != ""){
			retval.push_back(line);
		}

		return retval;
	}
	bool IsFocused() const{ return focused; }


	void Update(int mx,int my,int mst);
	void Draw(SDL_Surface* dest);
	void HandleInputEvent(SDL_Event* e);
};

#endif