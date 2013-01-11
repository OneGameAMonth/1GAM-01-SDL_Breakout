#ifndef _EDITOR_HPP_
#define _EDITOR_HPP_

#include<SDL.h>
#include<SDL_ttf.h>
#include<vector>
#include<cstdlib>

#include "state.hpp"
#include "surf.hpp"
#include "font.hpp"
#include "gui_button.hpp"
#include "gui_textbox.hpp"

//for defines
#include "gamefield.hpp"

#define LVL_FOLDER "levels/"

class Editor : public State{
private:
	int width,height,bpp;

	TTF_Font* font;
	int ptsize;

	SDL_Surface* draw_surf;

	GUI_Button* quit_btn;
	GUI_Button* load_btn;
	GUI_Button* close_btn;
	GUI_Textbox* level_path;

	Block grid[F_HEIGHT][F_WIDTH];
	SDL_Rect block_clips[B_TYPES];
	SDL_Surface* b_surf,*dum_surf;
	int block_mode;

	FILE* lvl_file;
	std::string laststat;

	int edit_mode;

	int mx,my,mst;
public:
	Editor(std::string n,TTF_Font* fnt,int ptsz,int pw,int ph,int pbpp);
	~Editor();

	void Init();
	void DrawGrid();
	void UpdateGrid();

	void Run();
	void Draw(SDL_Surface* screen);
	void OnEvent(SDL_Event* e);
	int Listen();
};

#endif