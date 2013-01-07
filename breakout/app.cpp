#include "app.hpp"
#include "menu.hpp"
#include "gamefield.hpp"

Application::Application(int argc,char* argv[]){
	screen = NULL;
	//load settings from file passed as args
	width = 640;
	height = 480;
	bpp = 32;
	
	run = true;
}

Application::~Application(){

	ClearStates();

	TTF_CloseFont(arial);

	TTF_Quit();

	SDL_Quit();
}

bool Application::Init(int w,int h,int bpp){
	
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
		return false;
	}

	if(TTF_Init() == -1){
		return false;
	}

	SDL_WM_SetCaption("SDL Breakout",NULL);
	screen = SDL_SetVideoMode(w,h,bpp,SDL_SWSURFACE);
	
	if(screen == NULL){
		return false;
	}

	return true;
}

bool Application::Load(){

	arial = Font::Load("media/arial.ttf",14);

	if(!arial){
		return false;
	}

	PushState(new Menu("main_menu",arial,14,width,height,bpp));

	return true;
}

void Application::OnEvent(){
	while(SDL_PollEvent(&e)){
		switch(e.type){
		case SDL_QUIT:
			run = false;
			break;
		}
	}
}

void Application::PushState(State* s){
	gamestate.push_back(s);
}

void Application::PopState(){
	if(!gamestate.empty()){
		State* s = gamestate.back();
		delete s;
		gamestate.pop_back();
	}
}

void Application::PauseState(){
	if(!gamestate.empty()){
		gamestate.back()->Pause();
	}
}

void Application::ResumeState(){
	if(!gamestate.empty()){
		gamestate.back()->UnPause();
	}
}

void Application::StopState(){
	if(!gamestate.empty()){
		gamestate.back()->Stop();
	}
}

void Application::StartState(){
	if(!gamestate.empty()){
		gamestate.back()->Start();
	}
}

void Application::ClearStates(){
	while(!gamestate.empty()){
		State* s = gamestate.back();
		delete s;
		gamestate.pop_back();
	}
}


int Application::Run(){
	SDL_Color red = {255,0,0};

	if(!Init(width,height,bpp)){
		return 1;
	}

	if(!Load()){
		return 2;
	}

	while(run){
		//clear screen
		SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
		OnEvent();

		if(!gamestate.empty()){
			gamestate.back()->OnEvent(&e);
			gamestate.back()->Run();
			gamestate.back()->Draw(screen);

			if(gamestate.back()->GetName() == "main_menu"){
				switch(gamestate.back()->Listen()){
				case -1:
					PopState();
					break;
				case 2:
					PushState(new GameField("game_field",arial,14,width,height,bpp));
					break;
				}
			}else if(gamestate.back()->GetName() == "game_field"){
				switch(gamestate.back()->Listen()){
				case -1:
					PopState();
					break;
				}
			}
		}else{
			run = false;
		}

		if(SDL_Flip(screen) == -1){
			return 1;
		}
	}

	return 0;
}