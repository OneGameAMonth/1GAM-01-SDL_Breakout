#ifndef _BALL_HPP_
#define _BALL_HPP_

#include "aabb.hpp"
#include "pad.hpp"
#include "block.hpp"

class Ball{
private:
	int x,y,w,h,dx,dy,ox,oy;
	AABB* bbox;
public:

	//don't change dir
	bool dcd;

	Ball(int px, int py,int pw, int ph) : x(px) , y(py) , w(pw), h(ph), dx(1), dy(-1), ox(px), oy(py), dcd(false){
		bbox = new AABB(x,y,w,h);
	}

	~Ball(){
		delete bbox;
	}

	void Update(){
		x += dx;
		y += dy;
		bbox->Update(x,y,w,h);
	}

	int GetX() const{ return x;}
	int GetY() const{ return y;}
	int GetOX() const { return ox; }
	int GetOY() const { return oy; }
	AABB* Col() const{ return bbox; }
	void Set(int px,int py){ x = px; y = py; }
	void SetO(){ ox = x; oy = y; }
	void SetDir(int mpdx,int mpdy){ if(!dcd){ dx *= mpdx; dy *= mpdy; } }

	void DoColPad(Pad* p);
	void DoColBlock(Block* blk);
};

#endif