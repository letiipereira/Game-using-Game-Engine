#include "GameEngine.h"
#include "SDLWrapper.h"
#include "Window.h"
#include "TextureManager.h"
#include "Texture.h"
#include "Level.h"
#include <iostream>

GameEngine* GameEngine::instance = nullptr;

void GameEngine::init(std::string windowTitle, int windowWidth, int windowHeight )
{
	sdl = new SDLWrapper(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	window = new Window(windowTitle, windowWidth, windowHeight);
	defaultLevel = new Level("defaultLevel");

	if (currentLevel == nullptr)
	{
		ActivateLevelByName("defaultLevel");
		currentLevel = defaultLevel;
	}
		
	//Texture* background= TextureManager::GetInstance()->LoadTexture("background", "assets/galaxy2.bmp");
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
		//TextureManager::GetInstance()->DrawTexture("background", 0, 0, 640, 480, 0);
		currentLevel->Update();
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
	if (instance == nullptr)
		instance = new GameEngine();
		
	return instance;
}

void GameEngine::ActivateLevelByName(std::string levelName)
{
	currentLevel = levelMap[levelName];
}

Level* GameEngine::GetActiveLevel()
{
	return currentLevel;
}

void GameEngine::CreateNewLevel(std::string levelName)
{
	Level* newLevel = new Level(levelName);
	levelMap[levelName] = newLevel;
}

void GameEngine::DeleteLevelByName(std::string levelName)
{
	delete levelMap[levelName];
	levelMap.erase(levelName);
}

class Level* GameEngine::GetLevelByName(std::string levelName)
{
	return levelMap[levelName];
}

GameEngine::~GameEngine()
{	
	delete currentLevel;
	delete defaultLevel;
	delete window;
	delete sdl;
	delete textureManager;

	std::map<std::string, Level*>::iterator it;
	for (it = levelMap.begin(); it != levelMap.end(); it++)
	{
		delete it->second;
	}
	levelMap.clear();
	 // should vector of created levels?
}
