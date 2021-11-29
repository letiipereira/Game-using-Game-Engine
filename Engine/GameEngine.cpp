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

	b2Vec2 gravity (0.0f, -10.0f);
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

	if (currentLevel == nullptr)
	{
		ActivateLevelByName("defaultLevel");
		currentLevel = defaultLevel;
	}

	world->SetContactListener(CollisionListener::GetInstance());

	//Texture* background= TextureManager::GetInstance()->LoadTexture("background", "assets/galaxy2.bmp");
}

void GameEngine::start()
{
	bool isRunning = true;
	SDL_Event ev;

	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	////World::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	//// Define the gravity vector. 
	//b2Vec2 gravity(0.0f, -10.0f);
	//// Construct a world object, which will hold and simulate the rigid bodies. 
	//b2World world(gravity);
	//CollisionListener tempListener;
	//world.SetContactListener(&tempListener);

	////Ground Body
	//b2BodyDef groundBodyDef;
	//groundBodyDef.position.Set(0.0f, -10.0f);
	//groundBodyDef.type = b2_staticBody;
	//// Call the body factory which allocates memory for the ground body 
	//// from a pool and creates the ground box shape (also from a pool). 
	//// The body is also added to the world. 
	//b2Body* groundBody = world.CreateBody(&groundBodyDef);

	//b2PolygonShape groundBox;
	//groundBox.SetAsBox(50.0f, 10.0f);

	//b2FixtureDef fixtureDef2;
	//fixtureDef2.shape = &groundBox;
	//fixtureDef2.isSensor = true;
	//groundBody->CreateFixture(&fixtureDef2);

	////Dynamic
	//b2BodyDef bodyDef;
	//bodyDef.type = b2_dynamicBody;
	//bodyDef.position.Set(0.0f, 4.0f);
	//b2Body* body = world.CreateBody(&bodyDef);

	//b2PolygonShape dynamicBox;
	//dynamicBox.SetAsBox(1.0f, 1.0f);

	//b2FixtureDef fixtureDef;
	//fixtureDef.shape = &dynamicBox;
	//fixtureDef.density = 1.0f;
	//fixtureDef.friction = 0.3f;
	//body->CreateFixture(&fixtureDef);

	//// This is our little game loop. 
	//for (int32 i = 0; i < 60; ++i)
	//{
	//	// Instruct the world to perform a single step of simulation. 
	//	// It is generally best to keep the time step and iterations fixed. 
	//	world.Step(timeStep, velocityIterations, positionIterations);

	//	// Now print the position and angle of the body. 
	//	b2Vec2 position = body->GetPosition();
	//	float angle = body->GetAngle();

	//	//printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
	//}

	while (isRunning)
	{
		// Now print the position and angle of the body. 
		//b2Vec2 position = groundBody->GetPosition();

		//printf("%4.2f %4.2f %4.2f\n", position.x, position.y);

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
							controllerIndex = temporaryControllerIndexMap.size() - 1;
							InputManager::GetInstance()->UpdateControllerIndex(temporaryControllerIndexMap);
						}

					}
					else
					{
						// Add controll at index 0
						temporaryControllerIndexMap.insert({ temporaryControllerIndexMap.size() , SDL_GameControllerOpen(ev.cdevice.which) });
						controllerIndex = temporaryControllerIndexMap.size() - 1;
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
			}
		}

		if (InputManager::GetInstance()->ControlledPawn.size())
		{
			// Check keyboard input
			InputManager::GetInstance()->CheckKeyboardInput(ev, InputManager::GetInstance()->ControlledPawn.begin()->first);

			// Check controller input
			InputManager::GetInstance()->CheckControllerInput(ev);
		}

		currentLevel->Update();
		currentLevel->Draw();
		window->updateSurface();
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
	// should vector of created levels?
}
