#ifndef _FONT_HPP_
#define _FONT_HPP_

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<cstdarg>
#include<deque>

#define MAX_LEN 4096

class Font{
public:
	static TTF_Font* Load(char* filename,int ptsize);
	static void Blit(SDL_Surface* dst,int x,int y,TTF_Font* font,SDL_Color col,const char* text);

	//Formats ints ,floats
	//Supports \n , %d and %f
	//Separate %d's and \n's with spaces please
	//Note for self: Don't use C strings next time
	static void Blitf(SDL_Surface* dst,int x,int y,TTF_Font* font,int ptsize,SDL_Color col,const char* text, ...);
};

#endif