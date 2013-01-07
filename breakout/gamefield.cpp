#include"gamefield.hpp"
#include"surf.hpp"
#include"font.hpp"

GameField::GameField(std::string n,TTF_Font* f,int ptsz,int w,int h,int bpp){
	name = n;
	width = w;
	height = h;
	depth = bpp;

	mx = my = mst = 0;

	font = f;
	ptsize = ptsz;

	draw_surf = SDL_CreateRGBSurface(SDL_SWSURFACE,width,height,depth,0,0,0,0);
	b_surf = SDL_CreateRGBSurface(SDL_SWSURFACE,B_W,B_H,depth,0,0,0,0);
	p_surf = SDL_CreateRGBSurface(SDL_SWSURFACE,P_W,P_H,depth,0,0,0,0);
	t_surf = SDL_CreateRGBSurface(SDL_SWSURFACE,32,16,depth,0,0,0,0);
	ball_surf = SDL_CreateRGBSurface(SDL_SWSURFACE,BALL_W,BALL_H,depth,0,0,0,0);
	quit_btn = new Button("game_field_quit",490,400,128,64,"media/img/test_button.bmp");

	p = new Pad(P_SX,P_SY,P_W,P_H);
	p->padmove = true;
	test_bb = new AABB(mx,my,32,16);
	ball = new Ball(220,300,BALL_W,BALL_H);

	obx = ball->GetOX();
	oby = ball->GetOY();

	Init();
}

GameField::~GameField(){
	if(draw_surf != NULL){
		SDL_FreeSurface(draw_surf);
	}
	if(quit_btn != NULL){
		delete quit_btn;
	}
	if(b_surf != NULL){
		SDL_FreeSurface(b_surf);
	}
	if(p_surf != NULL){
		SDL_FreeSurface(p_surf);
	}

	if(t_surf != NULL){
		SDL_FreeSurface(t_surf);
	}

	if(ball_surf != NULL){
		SDL_FreeSurface(ball_surf);
	}

	if(p != NULL){
		delete p;
	}

	if(test_bb != NULL){
		delete test_bb;
	}
	if(ball != NULL){
		delete ball;
	}
}

void GameField::Init(){
	for(int i = 0; i < F_HEIGHT;i++){
		for(int j = 0; j < F_WIDTH;j++){
			grid[i][j] = Block(F_SX+j*B_W,F_SY+i*B_H,B_W,B_H,0,0);
		}
	}

	for(int i = 2; i < 8;i++){
		for(int j = 2; j < 12;j++){
			Block* dummy = &grid[i][j];
			dummy->SetHealth(100);
		}
	}
}

void GameField::Run(){
	if(run){

		ball->SetO();
		ball->dcd = false;

		if(p->GetX() + P_W > (F_SX +(F_WIDTH*B_W))){
			p->Set((F_SX + (F_WIDTH*B_W)) - P_W,p->GetY());
		}

		if(p->GetX() < F_SX){
			p->Set(F_SX,p->GetY());
		}

		p->Col()->Update(p->GetX(),p->GetY(),P_W,P_H);
	
		if(ball->GetX() + BALL_W > (F_SX +(F_WIDTH*B_W))){
			ball->Set((F_SX +(F_WIDTH*B_W)) - BALL_W,ball->GetY());
			ball->SetDir(-1,1);
		}

		if(ball->GetX() < F_SX){
			ball->Set(F_SX,ball->GetY());
			ball->SetDir(-1,1);
		}

		if(ball->GetY() < F_SY){
			ball->Set(ball->GetX(),F_SY);
			ball->SetDir(1,-1);
		}

		if(ball->GetY() + BALL_H > (F_SY + (F_HEIGHT*B_H))){
			ball->Set(ball->GetX(),(F_SY + (F_HEIGHT*B_H)) - BALL_H);
			ball->SetDir(1,-1);
		}

		//paused = true;
		if(!paused){
			ball->DoColPad(p);

			for(int i = 0;i < F_HEIGHT;i++){
				for(int j = 0; j < F_WIDTH; j++){
					ball->DoColBlock(&grid[i][j]);
				}
			}

			ball->Update();
		}else{

		}

		quit_btn->Update(mx,my,mst);
		if(quit_btn->GetState() == BTT_PRESSED){
			halt = true;
		}
	}
}

void GameField::Draw(SDL_Surface* screen){
	SDL_Color red = {255,0,0};

	SDL_FillRect(draw_surf,NULL,SDL_MapRGB(draw_surf->format,0,0,0));

	for(int i = 0; i < F_HEIGHT;i++){
		for(int j = 0; j < F_WIDTH;j++){
			Uint32 col;
			if(grid[i][j].GetHealth() > 0){
				switch(grid[i][j].GetType()){
				case 0:
					col = SDL_MapRGB(b_surf->format,255,0,0);
				break;
				case 1:
					col = SDL_MapRGB(b_surf->format,0,255,0);
				break;
				}
			}else{
				col = SDL_MapRGB(b_surf->format,255,255,255);
			}
			SDL_FillRect(b_surf,NULL,col);
			Surface::Blit(b_surf,0,0,B_W,B_H,draw_surf,F_SX+j*B_W,F_SY+i*B_H);
		}
	}

	SDL_FillRect(p_surf,NULL,SDL_MapRGB(p_surf->format,255,128,0));
	Surface::Blit(p_surf,0,0,P_W,P_H,draw_surf,p->GetX(),p->GetY());

	SDL_FillRect(ball_surf,NULL,SDL_MapRGB(ball_surf->format,0,255,0));
	Surface::Blit(ball_surf,0,0,BALL_W,BALL_H,draw_surf,ball->GetX(),ball->GetY());

	Font::Blitf(draw_surf,10,10,font,ptsize,red," Testing collisions, no death ");

	quit_btn->Blit(draw_surf);

	Surface::Blit(draw_surf,0,0,width,height,screen,0,0);
}

void GameField::OnEvent(SDL_Event* e){
	switch(e->type){
	case SDL_MOUSEMOTION:
		mx = e->motion.x;
		my = e->motion.y;
		break;
	case SDL_MOUSEBUTTONDOWN:
		mst = 1;
		break;
	case SDL_MOUSEBUTTONUP:
		mst = 0;
		break;
	case SDL_KEYDOWN:
		if(!paused){
			switch(e->key.keysym.sym){
			if(p->padmove){
				case SDLK_LEFT:
					p->Move(-1,0);
					break;
				case SDLK_RIGHT:
					p->Move(1,0);
					break;
				}
			}
		}
		break;
	}
}

int GameField::Listen(){
	if(halt){ halt = false; return -1; }
	return 0;
}
