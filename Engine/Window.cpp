#include "Window.h"
#include "InitError.h"
#include <iostream>

Window::Window(std::string title, int windowWidth, int windowHeight)
{
	sdlWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_OPENGL);

	if (sdlWindow == nullptr)
	{
		throw InitError();
	}
}

SDL_Window* Window::GetSDLWindow() 
{
	if (sdlWindow == nullptr)
		std::cout << "Window::GetSDLWindow() " << SDL_GetError() << std::endl;
	return sdlWindow;
}

SDL_Surface* Window::getSurface()
{
	SDL_Surface* windowSurface= SDL_GetWindowSurface(sdlWindow);
	if (windowSurface == nullptr)
		std::cout << "Window::getSurface()" << SDL_GetError() << std::endl;
	return windowSurface;
}

void Window::updateSurface()
{
	SDL_UpdateWindowSurface(sdlWindow);
	std::cout << "Window::updateSurface(): " << SDL_GetError() << std::endl;
}

