#include "GameEngine.h"
#include "SDLWrapper.h"
#include "Window.h"
#include "TextureManager.h"

GameEngine* GameEngine::sInstance = nullptr;

void GameEngine::init(std::string windowTitle, int windowWidth, int windowHeight )
{
	sdl = new SDLWrapper(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	window = new Window(windowTitle, windowWidth, windowHeight);
	textureManager = new TextureManager;
}

void GameEngine::start()
{
	bool isRunning = true;
	SDL_Event ev;

	while (isRunning)
	{
		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_QUIT)
				isRunning = false;
		}
		window->updateSurface();

		//for reach element of the leval do stuff
	}
}

Window* GameEngine::GetWindow()
{
	return window;
}

GameEngine* GameEngine::GetInstance()
{
	if (sInstance == nullptr)
		sInstance = new GameEngine();
		
	return sInstance;
}

GameEngine::~GameEngine()
{
	delete window;
	delete sdl;
	delete textureManager;
}
