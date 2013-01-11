#ifndef _GUI_BUTTON_HPP_
#define _GUI_BUTTON_HPP_

#include<SDL.h>
#include<string>
#include"surf.hpp"


enum ButtonState{ BTT_NORMAL = 0, BTT_HOVER = 1, BTT_PRESSED = 2, BTT_INACTIVE = 3 };

class GUI_Button{
private:
	int w,h;
	int sx,sy;
	bool draw;
	SDL_Surface* img;
	SDL_Rect regions[4];
	ButtonState s;
	std::string name;
public:
	GUI_Button(std::string pname,int px,int py,int pw,int ph,char* img_path);
	virtual ~GUI_Button();

	bool IsDraw() const{ return draw; }
	void SetDraw(bool pdr){ draw = pdr; }
	void SetActive(){ s = BTT_NORMAL; }
	void SetInactive(){ s = BTT_INACTIVE; }
	void MoveTo(int px,int py){ sx = px; sy = py; }
	ButtonState GetState() const{ return s; }
	void SetState(ButtonState st){ s = st; }
	std::string GetName() const{ return name; }

	virtual void Blit(SDL_Surface* dst);
	virtual void Update(int mx,int my,int mst);
};

#endif