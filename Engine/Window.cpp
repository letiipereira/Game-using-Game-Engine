#include "Window.h"
#include "InitError.h"

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
	return sdlWindow;
}

SDL_Surface* Window::getSurface()
{
	return SDL_GetWindowSurface(sdlWindow);
}

void Window::updateSurface()
{
	SDL_UpdateWindowSurface(sdlWindow);
}

