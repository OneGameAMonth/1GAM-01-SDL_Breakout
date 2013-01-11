#include "editor.hpp"

Editor::Editor(std::string n,TTF_Font* fnt,int ptsz,int pw,int ph,int pbpp){
	SetName(n);
	width = pw;
	height = ph;
	bpp = pbpp;
	font = fnt;
	ptsize = ptsz;
	mx = my = mst = 0;
	lvl_file = NULL;

	edit_mode = 1;
	block_mode = 0;
	laststat = "";
	
	Init();

	draw_surf = SDL_CreateRGBSurface(SDL_SWSURFACE,width,height,bpp,0,0,0,0);

	b_surf = Surface::Load("media/img/block_sheet.bmp");
	dum_surf = SDL_CreateRGBSurface(SDL_SWSURFACE,B_W,B_H,bpp,0,0,0,0);

	quit_btn = new GUI_Button("editor_button_quit",width - 160,height - 96,128,64,"media/img/quit_btn.bmp");
	close_btn = new GUI_Button("editor_button_close",width - 160,height - 192,128,64,"media/img/close_btn.bmp");
	load_btn = new GUI_Button("editor_button_load",210,10,128,16,"media/img/loadsave_btn.bmp");

	level_path = new GUI_Textbox("editor_textbox_lvlpath",10,10,190,16,1,20,font,ptsize);

}

Editor::~Editor(){
	if(draw_surf != NULL){
		SDL_FreeSurface(draw_surf);
	}

	if(b_surf != NULL){
		SDL_FreeSurface(b_surf);
	}

	if(dum_surf != NULL){
		SDL_FreeSurface(dum_surf);
	}

	if(quit_btn != NULL){
		delete quit_btn;
	}

	if(close_btn != NULL){
		delete close_btn;
	}

	if(load_btn != NULL){
		delete load_btn;
	}

	if(level_path != NULL){
		delete level_path;
	}
}

void Editor::Init(){

	for(int i = 0;i < B_TYPES;i++){
		block_clips[i].x = 0;
		block_clips[i].y = (i*B_H);
		block_clips[i].w = B_W;
		block_clips[i].h = B_H;
	}

	for(int i = 0; i < F_HEIGHT; i++){
		for(int j = 0; j < F_WIDTH; j++){
			grid[i][j] = Block(F_SX+j*B_W,F_SY+i*B_H,B_W,B_H,0,0);
		}
	}

}

void Editor::DrawGrid(){
	for(int i = 0; i < F_HEIGHT;i++){
		for(int j = 0; j < F_WIDTH;j++){
			Uint32 col;
			if(grid[i][j].GetHealth() > 0){
				Surface::Blit(b_surf,0,block_clips[grid[i][j].GetType()].y,B_W,B_H,draw_surf,F_SX+j*B_W,F_SY+i*B_H);
			}else{
				int x = grid[i][j].GetX();
				int y = grid[i][j].GetY();
				int w = P_W;
				int h = P_H;
				col = SDL_MapRGB(dum_surf->format,255,255,255);

				if(x>= P_SX && x <= P_SX+P_W && y >= P_SY && y<= P_SY + P_H){
					col = SDL_MapRGB(dum_surf->format,255,0,0);
				}

				SDL_FillRect(dum_surf,NULL,col);
				Surface::Blit(dum_surf,0,0,B_W,B_H,draw_surf,F_SX+j*B_W,F_SY+i*B_H);
			}
		}
	}
}

void Editor::UpdateGrid(){
	for(int i = 0;i < F_HEIGHT;i++){
		for(int j = 0;j < F_WIDTH;j++){
			int x = grid[i][j].GetX();
			int y = grid[i][j].GetY();
			int w = grid[i][j].GetW();
			int h = grid[i][j].GetH();

			if(mx >= x && mx <= x + w && my >= y && my <= y+h){
				if(mst == 1){
					grid[i][j].SetType(block_mode);
					grid[i][j].SetHealth(100);
				}else if(mst == 2){
					grid[i][j].SetHealth(0);
				}
			}
		}
	}
}

void Editor::Run(){
	if(!paused){

		quit_btn->Update(mx,my,mst);
		if(quit_btn->GetState() == BTT_PRESSED){
			halt = true;
		}

		level_path->Update(mx,my,mst);
		load_btn->Update(mx,my,mst);
		switch(edit_mode){
		//load mode
		case 1:
			
			if(load_btn->GetState() == BTT_PRESSED){
				std::string load;

				if(!level_path->GetText().empty()){
					load = level_path->GetText().front();
				}

				load.insert(0,LVL_FOLDER);

				lvl_file = fopen(load.c_str(),"rb");


				if(lvl_file != 0){

					for(int i = 0;i < F_HEIGHT;i++){
						for(int j = 0; j < F_WIDTH;j++){
							if(!feof(lvl_file)){
								int pos = (F_WIDTH*i + j);
								fseek(lvl_file,pos*sizeof(Block),SEEK_SET);
								fread(&grid[i][j],sizeof(Block),1,lvl_file);
							}
						}
					}



					laststat = "Loaded "+load;
					fclose(lvl_file);
				}else{
					laststat = "Failed to load "+load;
				}


				level_path->Clear();
				edit_mode = 2;
				mx = my = mst = 0;
			}

			break;
		//edit/save/close mode
		case 2:

			if(load_btn->GetState() == BTT_PRESSED){
				std::string save;

				if(!level_path->GetText().empty()){
					save = level_path->GetText().front();
				}

				save.insert(0,LVL_FOLDER);

				lvl_file = fopen(save.c_str(),"wb");


				if(lvl_file != 0){

					for(int i = 0;i < F_HEIGHT;i++){
						for(int j = 0; j < F_WIDTH;j++){
							int pos = (F_WIDTH*i + j);
							fseek(lvl_file,pos*sizeof(Block),SEEK_SET);
							fwrite(&grid[i][j],sizeof(Block),1,lvl_file);
						}
					}

					laststat = "Saved to "+save;
					fclose(lvl_file);
				}else{
					laststat = "Failed to save "+save;
				}

				level_path->Clear();
				Init();
				edit_mode = 1;
				mx = my = mst = 0;
			}

			if(close_btn->GetState() == BTT_PRESSED){
				Init();
				laststat = "";
				edit_mode = 1;
				mx = my = mst = 0;
			}

			UpdateGrid();

			close_btn->Update(mx,my,mst);
			break;
		}
	}
}

void Editor::Draw(SDL_Surface* screen){
	SDL_Color tcol = {0,0,0};
	std::string mode,status;
	SDL_FillRect(draw_surf,NULL,SDL_MapRGB(draw_surf->format,255,204,102));

	quit_btn->Blit(draw_surf);
	load_btn->Blit(draw_surf);
	level_path->Draw(draw_surf);
	switch(edit_mode){
		//load mode
		case 1:
			mode = "Load mode";
			break;
		//edit/save/close mode
		case 2:
			mode = "Edit mode";
			DrawGrid();
			Font::Blitf(draw_surf,500,50,font,ptsize,tcol,"Block: %d ",block_mode);
			close_btn->Blit(draw_surf);
			break;
		}

	Font::Blit(draw_surf,400,0,font,tcol,mode.c_str());
	Font::Blit(draw_surf,400,20,font,tcol,laststat.c_str());
	Surface::Blit(draw_surf,screen,0,0);
}

void Editor::OnEvent(SDL_Event* e){
	level_path->HandleInputEvent(e);
	switch(e->type){
	case SDL_MOUSEMOTION:
		mx = e->motion.x;
		my = e->motion.y;
		break;
	case SDL_MOUSEBUTTONDOWN:
		if(e->button.button == SDL_BUTTON_LEFT){
			mst = 1;
		}
		if(e->button.button == SDL_BUTTON_RIGHT){
			mst = 2;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		mst = 0;
		break;
	case SDL_KEYDOWN:


		Uint16 ch = e->key.keysym.sym;
		if(edit_mode == 2){
			if(ch >= (Uint16)'0' && ch < (Uint16)'6'){
				block_mode = (int)ch - 48;
			}
		}
	}

}

int Editor::Listen(){
	if(halt){ halt = false; return -1; }
	return 0;
}