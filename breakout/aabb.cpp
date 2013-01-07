#include"aabb.hpp"

AABB::coltype AABB::IsCol(AABB* a,AABB* b){
	int ax = a->x, ay = a->y, aw = a->w, ah = a->h;
	int bx = b->x, by = b->y, bw = b->w, bh = b->h;

	if( (ax >= bx && ax <= bx + bw) && ((ax + aw) >= bx && ((ax + aw) <= (bx + bw))) ){
		if( (ay >= by && ay <= by + bh) && ((ay + ah) >= by && ((ay + ah) <= (by + bh))) ){
			return COL_INSIDE;
		}
	}

	if( (ax >= bx && ax <= bx + bw) && ((ax+aw) >= bx && ((ax+aw) <= (bx + bw))) ){
		if(( ay+ah >= by) && ( ay+ah <= by + bh )){
			return TOP_COL;
		}else if(( ay >= by) && ( ay <= by + bh )){
			return BOTTOM_COL;
		}
	}

	if( (ax >= bx && ax <= bx + bw) ){
		if(( ay >= by) && ( ay <= by + bh )){
			if(( ay+ah >= by) && ( ay+ah <= by + bh )){
				return RIGHT_COL;
			}
			return COL_INTERSECT;
		}
		if(( ay+ah >= by) && ( ay+ah <= by + bh )){
			return COL_INTERSECT;
		}
	}

	if( ((ax+aw) >= bx && ((ax+aw) <= (bx + bw))) ){
		if(( ay >= by) && ( ay <= by + bh )){
			if(( ay+ah >= by) && ( ay+ah <= by + bh )){
				return LEFT_COL;
			}
			return COL_INTERSECT;
		}
		if(( ay+ah >= by) && ( ay+ah <= by + bh )){
			return COL_INTERSECT;
		}
	}

	return NO_COL;
}

AABB::coldepth AABB::GetDepth(AABB* a,AABB* b){
	AABB::coldepth ret = { 0,0,0,0 };
	int ax = a->x, ay = a->y, aw = a->w, ah = a->h;
	int bx = b->x, by = b->y, bw = b->w, bh = b->h;

	if(IsCol(a,b) == COL_INTERSECT){
		if( (ax >= bx && ax <= bx+bw && ay <= by+bh && ay >= by)){
			ret.right = (bx + bw) - ax;
			ret.bottom = (by + bh) - ay;
		}
		if((ax >= bx && ax <= bx+bw && ay+ah <= by+bh && ay+ah >= by )){
			ret.right = (bx + bw) - ax;
			ret.top = (ay + ah) - (by);
		}
		if((ax+aw >= bx && ax+aw <= bx+bw && ay+ah <= by+bh && ay+ah >= by )){
			ret.left = (ax+aw) - bx;
			ret.top = (ay+ah) - by;
		}
		if((ax+aw >= bx && ax+aw <= bx+bw && ay <= by+bh && ay >= by )){
			ret.left = (ax + aw) - bx;
			ret.bottom = (by+bh) - ay;
		}
	}

	return ret;
}