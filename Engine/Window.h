#pragma once
#include <SDL.h>
#include <string>
class Window
{
public:
	Window(std::string title, int windowWidth, int windowHeight);

	SDL_Surface* getSurface();

	void updateSurface();

	SDL_Window* GetSDLWindow();

	~Window() 
	{ 
		SDL_DestroyWindow(sdlWindow); 
	};
private:
	SDL_Window* sdlWindow;
};
