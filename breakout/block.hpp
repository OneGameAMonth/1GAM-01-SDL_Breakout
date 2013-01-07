#ifndef _BLOCK_HPP_
#define _BLOCK_HPP_

#include<SDL.h>

#include"aabb.hpp"

class Block{
private:
	int health;
	int x,y,w,h;
	int type;
public:
	Block(int px = 0,int py = 0,int pw = 0,int ph = 0,int ptype = 0,int phealth = 0){
		x = px;y = py;
		w = pw;h = ph;
		type = ptype;
		health = phealth;
	}
	~Block(){}

	int GetHealth() const{ return health; }
	int GetType() const{ return type; }
	int GetX() const{ return x; }
	int GetY() const{ return y; }
	int GetW() const{ return w; }
	int GetH() const{ return h; }

	void SetHealth(int phealth){ health = phealth; }
};

#endif