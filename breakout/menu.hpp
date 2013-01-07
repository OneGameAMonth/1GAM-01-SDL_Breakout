#ifndef _MENU_HPP_
#define _MENU_HPP_

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<vector>

#include"state.hpp"
#include"gui_button.hpp"

class Menu: public State{
private:
	int width,height,bpp;
	int ptsize;
	TTF_Font* font;
	SDL_Surface* draw_surf;
	int mx,my,mst;
	std::vector<Button*> buttons;
	bool newGame;
public:
	Menu(std::string n,TTF_Font* f,int ptsz,int w,int h,int bpp);
	~Menu();
	void Run();
	void Draw(SDL_Surface* screen);
	void OnEvent(SDL_Event* e);
	int Listen();
};

#endif