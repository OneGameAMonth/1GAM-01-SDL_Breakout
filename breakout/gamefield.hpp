#ifndef _GAMEFIELD_HPP_
#define _GAMEFIELD_HPP_

#include<SDL_ttf.h>
#include<string>

#include"state.hpp"
#include"gui_button.hpp"
#include"block.hpp"
#include"pad.hpp"
#include"ball.hpp"

#define F_SX 10
#define F_SY 40
#define F_WIDTH 14
#define F_HEIGHT 24
#define B_W 32
#define B_H 16
#define P_W 64
#define P_H 16
#define P_SX 200
#define P_SY 370
#define BALL_W 10
#define BALL_H 10

class GameField: public State{
private:
	int width,height,depth,ptsize;
	TTF_Font* font;
	SDL_Surface* draw_surf;

	Button* quit_btn;
	int mx,my,mst;

	Block grid[F_HEIGHT][F_WIDTH];
	SDL_Surface* b_surf;

	Pad* p;
	bool padmove;
	SDL_Surface* p_surf;

	Ball* ball;
	int obx,oby;
	SDL_Surface* ball_surf;

	AABB* test_bb;
	SDL_Surface* t_surf;
public:
	GameField(std::string n,TTF_Font* f,int ptsz,int w,int h,int bpp);
	~GameField();
	void Init();
	void Run();
	void Draw(SDL_Surface* screen);
	void OnEvent(SDL_Event* e);
	int Listen();
};

#endif