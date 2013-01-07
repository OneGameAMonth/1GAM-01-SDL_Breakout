#include "ball.hpp"

void Ball::DoColPad(Pad* p){
	AABB::coltype bt = AABB::IsCol(bbox,p->Col());
	AABB::coldepth bd = AABB::GetDepth(bbox,p->Col());

	Ball* ball = this;

	int obx = ox, oby = oy;

	p->padmove = false;

	switch(bt){
	case AABB::NO_COL:
		p->padmove = true;
		break;
	case AABB::COL_INSIDE:
		break;
	case AABB::TOP_COL:
	case AABB::BOTTOM_COL:
		ball->Set(obx,oby);
		ball->SetDir(1,-1);
		break;
	case AABB::LEFT_COL:
	case AABB::RIGHT_COL:
		ball->Set(obx,oby);
		ball->SetDir(-1,1);
		break;
	case AABB::COL_INTERSECT:

		if(bd.bottom == 0 && bd.right == 0){
			if(bd.top > bd.left){
				ball->Set(ball->GetX() - bd.left,ball->GetY());
				ball->SetDir(-1,1);
				//
				p->Move(bd.left,0);
			}else{
				ball->Set(ball->GetX(),ball->GetY() - bd.top);
				ball->SetDir(1,-1);
			}
		}else if(bd.top == 0 && bd.right == 0){
			if(bd.bottom > bd.left){
				ball->Set(ball->GetX() - bd.left,ball->GetY());
				ball->SetDir(-1,1);
				//
				p->Move(bd.left,0);
			}else{
				ball->Set(ball->GetX(),ball->GetY() + bd.bottom);
				ball->SetDir(1,-1);
			}
		}else if(bd.top == 0 && bd.left == 0){
			if(bd.bottom > bd.right){
				ball->Set(ball->GetX() + bd.right,ball->GetY());
				ball->SetDir(-1,1);
				//
				p->Move(-bd.right,0);
			}else{
				ball->Set(ball->GetX(),ball->GetY() + bd.bottom);
				ball->SetDir(1,-1);
			}

		}else if(bd.bottom == 0 && bd.left == 0){
			if(bd.top > bd.right){
				ball->Set(ball->GetX() + bd.right,ball->GetY());
				ball->SetDir(-1,1);
				//
				p->Move(-bd.right,0);
			}else{
				ball->Set(ball->GetX(),ball->GetY() - bd.top);
				ball->SetDir(1,-1);
			}
		}

		break;
	}
}

void Ball::DoColBlock(Block* blk){
	AABB* blk_dummy = new AABB(blk->GetX(),blk->GetY(),blk->GetW(),blk->GetH());

	AABB::coltype bt = AABB::IsCol(bbox,blk_dummy);
	AABB::coldepth bd = AABB::GetDepth(bbox,blk_dummy);

	Ball* ball = this;

	int obx = ox, oby = oy;

	if(blk->GetHealth() > 0){
		switch(bt){
		case AABB::NO_COL:
		case AABB::COL_INSIDE:
			break;
		case AABB::TOP_COL:
		case AABB::BOTTOM_COL:
			ball->Set(obx,oby);
			ball->SetDir(1,-1);
			blk->SetHealth(0);
			ball->dcd = true;
			break;
		case AABB::LEFT_COL:
		case AABB::RIGHT_COL:
			ball->Set(obx,oby);
			ball->SetDir(-1,1);
			blk->SetHealth(0);
			ball->dcd = true;
			break;
		case AABB::COL_INTERSECT:
			if(bd.bottom == 0 && bd.right == 0){
				if(bd.top > bd.left){
					ball->Set(ball->GetX() - bd.left,ball->GetY());
					ball->SetDir(-1,1);
					//
				}else{
					ball->Set(ball->GetX(),ball->GetY() - bd.top);
					ball->SetDir(1,-1);
				}
			}else if(bd.top == 0 && bd.right == 0){
				if(bd.bottom > bd.left){
					ball->Set(ball->GetX() - bd.left,ball->GetY());
					ball->SetDir(-1,1);
					//
				}else{
					ball->Set(ball->GetX(),ball->GetY() + bd.bottom);
					ball->SetDir(1,-1);
				}
			}else if(bd.top == 0 && bd.left == 0){
				if(bd.bottom > bd.right){
					ball->Set(ball->GetX() + bd.right,ball->GetY());
					ball->SetDir(-1,1);
					//
				}else{
					ball->Set(ball->GetX(),ball->GetY() + bd.bottom);
					ball->SetDir(1,-1);
				}

			}else if(bd.bottom == 0 && bd.left == 0){
				if(bd.top > bd.right){
					ball->Set(ball->GetX() + bd.right,ball->GetY());
					ball->SetDir(-1,1);
					//
				}else{
					ball->Set(ball->GetX(),ball->GetY() - bd.top);
					ball->SetDir(1,-1);
				}
			}

			ball->dcd = true;
			blk->SetHealth(0);
			break;
		}
	}

	delete blk_dummy;
}