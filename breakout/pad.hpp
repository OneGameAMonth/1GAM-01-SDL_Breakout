#ifndef _PAD_HPP_
#define _PAD_HPP_

#include"aabb.hpp"

class Pad{
private:
	int x,y,w,h;
	AABB* colbox;
public:
	bool padmove;

	Pad(int px,int py,int pw,int ph): x(px), y(py), w(pw), h(ph), padmove(true){
		colbox = new AABB(x,y,w,h);
	}
	~Pad(){
		delete colbox;
	}

	void Move(int dx,int dy){ if(padmove){ x+=dx; y+=dy; } }
	void Set(int px,int py){ x = px; y = py; }
	int GetX() const { return x; }
	int GetY() const { return y; }
	AABB* Col() const { return colbox; }
};

#endif