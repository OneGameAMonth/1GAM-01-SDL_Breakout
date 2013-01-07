#include "font.hpp"

TTF_Font* Font::Load(char* filename,int ptsize){
	return TTF_OpenFont(filename,ptsize);
}

void Font::Blit(SDL_Surface* dst,int x,int y,TTF_Font* font,SDL_Color col,const char* text){
	SDL_Surface* msg = TTF_RenderText_Solid(font,text,col);
	SDL_Rect dr;

	dr.x = x;
	dr.y = y;

	SDL_BlitSurface(msg,NULL,dst,&dr);

	SDL_FreeSurface(msg);
}

void Font::Blitf(SDL_Surface* dst,int x,int y,TTF_Font* font,int ptsize,SDL_Color col,const char* text, ...){
	std::va_list nums;
	std::deque<std::string> ftext;
	char buff[MAX_LEN];
	char buff2[MAX_LEN];
	int inum = 0.0;
	double fnum = 0.0;

	va_start(nums,text);
	strcpy(buff,"");
	strcpy(buff2,"");

	for(int i = 0;text[i] != '\0';i++){
		if(text[i]!=' '){
			//if newline
			if(text[i]=='\n'){
				//push full string to deque
				ftext.push_back(std::string(buff2));
				//empty full string
				strcpy(buff2,"");
				//skip the iteration(don't copy current character)
				continue;
			}
			//copy new char to first buffer
			strncat(buff,&text[i],1);
		}else{
			if(strcmp(buff,"")!=0){
				//if %d then replace it with number
				if(strcmp(buff,"%d")==0){
					inum = va_arg(nums,int);
					itoa(inum,buff,10);
				}else if(strcmp(buff,"%f")==0){
					fnum = va_arg(nums,double);
					sprintf(buff,"%.2f",fnum);
				}
				//add missed space
				strncat(buff," ",1);
				//copy piece of text to full string
				strncat(buff2,buff,strlen(buff));
				//empty piece of string
				strcpy(buff,"");
			}
		}
	}

	//push last full string or piece of string
	if(strcmp(buff,"")==0){
		ftext.push_back(std::string(buff2));
	}else{
		ftext.push_back(std::string(buff));
	}

	va_end(nums);

	int yoff = y;
	while(!ftext.empty()){
		//get text from the front
		std::string txt = ftext.front();
		//render it
		SDL_Surface* msg = TTF_RenderText_Solid(font,txt.c_str(),col);
		SDL_Rect rc;

		//set coords
		rc.x = x;
		rc.y = yoff;
		//text to dest
		SDL_BlitSurface(msg,NULL,dst,&rc);
		//offset for newline
		yoff+=ptsize;
		//free blitted text surface
		SDL_FreeSurface(msg);
		//pop current text
		ftext.pop_front();
	}
}
