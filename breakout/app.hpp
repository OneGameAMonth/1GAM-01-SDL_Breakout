#ifndef _APP_HPP_
#define _APP_HPP_

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<vector>

#include"surf.hpp"
#include"font.hpp"
#include"state.hpp"

class Application{
private:
	int width,height,bpp;
	bool run;
	SDL_Surface* screen;
	TTF_Font* arial;
	SDL_Event e;
	std::vector<State*> gamestate;

	bool Init(int w,int h,int bpp);
	bool Load();
	void OnEvent();
public:
	Application(int argc,char* argv[]);
	~Application();

	void PushState(State* s);
	void PopState();
	void PauseState();
	void ResumeState();
	void StopState();
	void StartState();
	void ClearStates();

	int Run();
};

#endif