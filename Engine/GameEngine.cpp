#include "GameEngine.h"
#include "SDLWrapper.h"
#include "Window.h"
#include "CollisionListener.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "Texture.h"
#include "Level.h"
#include "Pawn.h"
#include <map>
#include <iostream>

GameEngine* GameEngine::instance = nullptr;

GameEngine::GameEngine()
{
	prevTime = 0;
	currentTime = 0;
	deltaTime = 0;

	b2Vec2 gravity(0.0f, -10.0f);
	world = new b2World(gravity);
}

void GameEngine::init(std::string windowTitle, int windowWidth, int windowHeight)
{
	sdl = new SDLWrapper(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) < 0)
	{
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;

		SDL_Quit();
	}

	window = new Window(windowTitle, windowWidth, windowHeight);
	defaultLevel = new Level("defaultLevel");
	myWindowWidth = windowWidth;
	myWindowHeigth = windowHeight;

	if (currentLevel == nullptr)
	{
		ActivateLevelByName("defaultLevel");
		currentLevel = defaultLevel;
	}

	world->SetContactListener(CollisionListener::GetInstance());
}

void GameEngine::start()
{
	currentLevel->Init();

	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	bool isRunning = true;
	SDL_Event ev;

	while (isRunning)
	{
		prevTime = currentTime;
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - prevTime) / 1000.0f;

		world->Step(timeStep, velocityIterations, positionIterations);

		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_QUIT)
				isRunning = false;

			switch (ev.type)
			{
				case SDL_CONTROLLERDEVICEADDED:
				{
					std::cout << "A controller was connected. " << std::endl;

					// Mapping controller
					int controllerIndex = 0;
					std::map<int, SDL_GameController*> temporaryControllerIndexMap = InputManager::GetInstance()->ControllerIndex;

					if (temporaryControllerIndexMap.size())
					{
						bool controllerIncluded = false;

						std::map<int, SDL_GameController*>::iterator it;
						for (it = temporaryControllerIndexMap.begin(); it != temporaryControllerIndexMap.end(); it++)
						{
							// If a controller was removed and there is a free index
							if (it->second == nullptr)
							{
								//it->second = SDL_GameControllerFromInstanceID(ev.cdevice.which);
								it->second = SDL_GameControllerOpen(ev.cdevice.which);
								controllerIndex = it->first;
								InputManager::GetInstance()->UpdateControllerIndex(temporaryControllerIndexMap);
								controllerIncluded = true;
								break;
							}
						}

						// If there is no free index
						if (controllerIncluded == false)
						{
							temporaryControllerIndexMap.insert({ temporaryControllerIndexMap.size() , SDL_GameControllerOpen(ev.cdevice.which) });
							controllerIndex = static_cast<int>(temporaryControllerIndexMap.size() - 1);
							InputManager::GetInstance()->UpdateControllerIndex(temporaryControllerIndexMap);
						}

					}
					else
					{
						// Add controll at index 0
						temporaryControllerIndexMap.insert({ temporaryControllerIndexMap.size() , SDL_GameControllerOpen(ev.cdevice.which) });
						controllerIndex = static_cast<int>(temporaryControllerIndexMap.size() - 1);
						InputManager::GetInstance()->UpdateControllerIndex(temporaryControllerIndexMap);
					}

					InputManager::GetInstance()->MapNewController(controllerIndex);

					// Associate controller with available pawn
					std::map<Pawn*, SDL_GameController*> pawnController = InputManager::GetInstance()->ControlledPawn;
					if (pawnController.size())
					{
						std::map<Pawn*, SDL_GameController*>::iterator it;
						for (it = pawnController.begin(); it != pawnController.end(); it++)
						{
							if (it->second == nullptr)
							{
								it->second = SDL_GameControllerOpen(ev.cdevice.which);
								std::cout << "Found a pawn! " << std::endl;
								std::cout << SDL_GameControllerNameForIndex(ev.cdevice.which) << " pawn: " << it->first << std::endl;
								InputManager::GetInstance()->UpdateController(pawnController);
								break;
							}
						}
					}

					break;
				}

				case SDL_CONTROLLERDEVICEREMOVED:
				{
					std::cout << "A controller was disconnected. " << std::endl;

					// Remove controller from index map
					std::map<int, SDL_GameController*> temporaryControllerIndexMap = InputManager::GetInstance()->ControllerIndex;
					std::map<int, SDL_GameController*>::iterator it;
					for (it = temporaryControllerIndexMap.begin(); it != temporaryControllerIndexMap.end(); it++)
					{
						if (it->second == SDL_GameControllerFromInstanceID(ev.cdevice.which))
						{
							it->second = nullptr;
							break;
						}
					}
					InputManager::GetInstance()->UpdateControllerIndex(temporaryControllerIndexMap);

					// Dissociate pawn connected with controller
					std::map<Pawn*, SDL_GameController*> pawnController = InputManager::GetInstance()->ControlledPawn;
					if (pawnController.size())
					{
						std::map<Pawn*, SDL_GameController*>::iterator it;
						for (it = pawnController.begin(); it != pawnController.end(); it++)
						{
							if (it->second == SDL_GameControllerFromInstanceID(ev.cdevice.which))
							{
								it->second = nullptr;
								InputManager::GetInstance()->UpdateController(pawnController);
								break;
							}
						}
					}

					break;
				}
				case (SDL_KEYDOWN):
				{
					InputManager::GetInstance()->OnKeyDown(SDL_GetKeyName(ev.key.keysym.sym), InputManager::GetInstance()->ControlledPawn.begin()->first);
					
					break;
				}
				case (SDL_KEYUP):
				{
					InputManager::GetInstance()->OnKeyUp(SDL_GetKeyName(ev.key.keysym.sym), InputManager::GetInstance()->ControlledPawn.begin()->first);
					break;
				}
				case (SDL_CONTROLLERBUTTONDOWN):
				{
					InputManager::GetInstance()->OnButtonDown(ev);
					break;
				}
				case (SDL_CONTROLLERBUTTONUP):
				{
					InputManager::GetInstance()->OnButtonUp(ev);
					break;
				}
			}
		}

		if (InputManager::GetInstance()->ControlledPawn.size())
		{
			// Check keyboard input
			InputManager::GetInstance()->ControlledPawn.begin()->first->CheckKeyState();

			// Check controller input
			InputManager::GetInstance()->OnAxisMotion(ev);
		}

		currentLevel->Update();
		currentLevel->Draw();
		currentLevel->Refresh();
		//window->updateSurface();
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

int GameEngine::GameWindowWidht()
{
	return myWindowWidth;
}

int GameEngine::GameWindowHeight()
{
	return myWindowHeigth;
}

void GameEngine::ActivateLevelByName(std::string levelName)
{
	currentLevel = levelMap[levelName];
	
}

InputManager* GameEngine::GetInputManager()
{
	return InputManager::GetInstance();
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

b2World* GameEngine::GetWorld()
{
	return world;
}

GameEngine::~GameEngine()
{
	delete currentLevel;
	delete defaultLevel;
	delete window;
	delete sdl;
	delete textureManager;
	delete instance;

	std::map<std::string, Level*>::iterator it;
	for (it = levelMap.begin(); it != levelMap.end(); it++)
	{
		delete it->second;
	}
	levelMap.clear();
}
