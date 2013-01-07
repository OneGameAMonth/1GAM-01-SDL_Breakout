#ifndef _AABB_HPP_
#define _AABB_HPP_

class AABB{
	int x,y,w,h;
public:
	enum coltype{ NO_COL, TOP_COL, BOTTOM_COL, LEFT_COL, RIGHT_COL, COL_INSIDE, COL_INTERSECT };
	struct coldepth{ int top,bottom,left,right; };
	AABB(int px,int py,int pw,int ph) : x(px), y(py), w(pw), h(ph) {}
	~AABB(){}

	void Update(int px,int py,int pw,int ph){
		x = px;y = py;
		w = pw;h = ph;
	}

	//Test if A collides B
	static coltype IsCol(AABB* a,AABB* b);
	//Get the depth of penetration of A into B
	static coldepth GetDepth(AABB* a,AABB* b);
};

#endif