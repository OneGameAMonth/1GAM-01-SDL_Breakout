#ifndef _STATE_HPP_
#define _STATE_HPP_

#include<SDL.h>
#include<string>

class State{
protected:
	bool halt;
	bool run;
	bool paused;
	std::string name;
public:
	State() : run(true) , paused(false) , halt(false){}
	virtual ~State(){}

	inline void Start(){
		run = true;
	}
	inline void Stop(){
		run = false;
	}
	inline void Pause(){
		paused = true;
	}
	inline void UnPause(){
		paused = false;
	}

	inline bool IsPaused() const{
		return paused;
	}

	inline bool IsRunning() const{
		return run;
	}


	void SetName(std::string n){ name = n; }
	std::string GetName() const{ return name;}
	virtual void Run() = 0;
	virtual void Draw(SDL_Surface* screen) = 0;
	virtual void OnEvent(SDL_Event* e) = 0;
	virtual int Listen() = 0;
};

#endif