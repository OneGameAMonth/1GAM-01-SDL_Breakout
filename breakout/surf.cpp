#include "surf.hpp"

SDL_Surface* Surface::Load(char* filename){
	SDL_Surface* loaded = NULL;
	SDL_Surface* optimized = NULL;

	loaded = IMG_Load(filename);

	if(loaded != NULL){
		optimized = SDL_DisplayFormat(loaded);
		SDL_FreeSurface(loaded);

		if(optimized != NULL){
			Uint32 ck = SDL_MapRGB(optimized->format,0xFF,0xFF,0xFF);
			SDL_SetColorKey(optimized,SDL_SRCCOLORKEY,ck);
		}
	}
	
	return optimized;
}

void Surface::Blit(SDL_Surface* src,SDL_Surface* dest,int x1,int y1){
	SDL_Rect off;

	off.x = x1;
	off.y = y1;

	SDL_BlitSurface(src,NULL,dest,&off);
}

void Surface::Blit(SDL_Surface* src,int x,int y,int w,int h,SDL_Surface* dest,int x1,int y1){
	SDL_Rect srcOff,destOff;

	srcOff.x = x; srcOff.y = y;
	srcOff.w = w; srcOff.h = h;

	destOff.x = x1; destOff.y = y1;

	SDL_BlitSurface(src,&srcOff,dest,&destOff);
}