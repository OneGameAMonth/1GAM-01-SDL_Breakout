#ifndef _SURF_HPP_
#define _SURF_HPP_

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

class Surface{
public:
	static SDL_Surface* Load(char* filename);
	static void Blit(SDL_Surface* src,SDL_Surface* dest,int x1,int y1);
	static void Blit(SDL_Surface* src,int x,int y,int w,int h,SDL_Surface* dest,int x1,int y1);
};

#endif