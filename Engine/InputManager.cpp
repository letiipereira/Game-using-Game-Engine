#include <SDL.h>
#include <iostream>
#include "Pawn.h"
#include "InputManager.h"

InputManager* InputManager::sInstance{ nullptr };

InputManager::InputManager()
{
	class Pawn* pawn = nullptr;
	numControllers = 0;
	keyState = SDL_GetKeyboardState(NULL);

	KeyboardKeys.insert({ "SPACE", SDL_SCANCODE_SPACE });
	KeyboardKeys.insert({ "RIGHT", SDL_SCANCODE_RIGHT });
	KeyboardKeys.insert({ "LEFT", SDL_SCANCODE_LEFT });
	KeyboardKeys.insert({ "UP", SDL_SCANCODE_UP });
	KeyboardKeys.insert({ "DOWN", SDL_SCANCODE_DOWN });
	KeyboardKeys.insert({ "D", SDL_SCANCODE_D });
	KeyboardKeys.insert({ "A", SDL_SCANCODE_A });
	KeyboardKeys.insert({ "W", SDL_SCANCODE_W });
	KeyboardKeys.insert({ "S", SDL_SCANCODE_S });
}

void InputManager::AddPawn(Pawn* pawn)
{
	ControlledPawn.insert({ pawn, nullptr });
}

void InputManager::MapNewController(int controllerIndex)
{
	SDL_GameController* controller;

	if (SDL_IsGameController(controllerIndex)) {
		char* mapping;
		std::cout << "Index '" << controllerIndex << "' is a compatible controller, named '" <<
			SDL_GameControllerNameForIndex(controllerIndex) << "'" << std::endl;
		controller = SDL_GameControllerOpen(controllerIndex);
		mapping = SDL_GameControllerMapping(controller);
		std::cout << "Controller " << controllerIndex << " is mapped as \"" << mapping << std::endl;
		SDL_free(mapping);
		SDL_GameControllerUpdate();
	}
	else {
		std::cout << "Index '" << controllerIndex << "' is not a compatible controller." << std::endl;
	}
}

void InputManager::CheckKeyboardInput(SDL_Event gamepadEvent, class Pawn* currentPlayer)
{
	if (keyState[SDL_SCANCODE_RIGHT])
	{
		currentPlayer->Move(Pawn::MovementType::move_right);
		/*std::cout << "Right" << std::endl;*/
	}

	if (keyState[SDL_SCANCODE_LEFT])
	{
		currentPlayer->Move(Pawn::MovementType::move_left);
	}

	if (keyState[SDL_SCANCODE_UP])
	{
		currentPlayer->Move(Pawn::MovementType::move_up);
	}

	if (keyState[SDL_SCANCODE_DOWN])
	{
		currentPlayer->Move(Pawn::MovementType::move_down);
	}

	if (keyState[SDL_SCANCODE_SPACE])
	{
		currentPlayer->Attack();
	}
}

void InputManager::CheckControllerInput(SDL_Event gamepadEvent)
{
	Pawn* currentPlayer = nullptr;

	if (gamepadEvent.type == SDL_JOYAXISMOTION && (ControlledPawn.size() != 0))
	{
		std::map<Pawn*, SDL_GameController*>::iterator it;
		for (it = ControlledPawn.begin(); it != ControlledPawn.end(); it++)
		{
			if (it->second == SDL_GameControllerOpen(gamepadEvent.cdevice.which))
			{
				currentPlayer = it->first;

				break;
			}
		}

		if (currentPlayer)
		{
			if (gamepadEvent.jaxis.axis == 0)
			{
				//if (-32768 <= gamepadEvent.jaxis.value && gamepadEvent.jaxis.value < 128)
				if (gamepadEvent.jaxis.value < -joystickDeadZone)
				{
					currentPlayer->Move(Pawn::MovementType::move_left);
					std::cout << "Left" << std::endl;
				}

				//if (128 < gamepadEvent.jaxis.value && gamepadEvent.jaxis.value <= 32767)
				if (gamepadEvent.jaxis.value > joystickDeadZone)
				{
					currentPlayer->Move(Pawn::MovementType::move_right);
					std::cout << "Right" << std::endl;
				}
			}

			if (gamepadEvent.jaxis.axis == 1)
			{
				//if (-32768 <= gamepadEvent.jaxis.value && gamepadEvent.jaxis.value < 128)
				if (gamepadEvent.jaxis.value < -joystickDeadZone)
				{
					currentPlayer->Move(Pawn::MovementType::move_up);
				}

				//if (128 < gamepadEvent.jaxis.value && gamepadEvent.jaxis.value <= 32767)
				if (gamepadEvent.jaxis.value > joystickDeadZone)
				{
					currentPlayer->Move(Pawn::MovementType::move_down);
				}
			}
		}
	}

	if (gamepadEvent.type == SDL_CONTROLLERBUTTONDOWN && (ControlledPawn.size() != 0))
	{
		std::map<Pawn*, SDL_GameController*>::iterator it;
		for (it = ControlledPawn.begin(); it != ControlledPawn.end(); it++)
		{
			if (it->second == SDL_GameControllerFromInstanceID(gamepadEvent.cdevice.which))
			{
				currentPlayer = it->first;

				break;
			}
		}

		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_A && currentPlayer != nullptr)
		{
			currentPlayer->Attack();
			std::cout << "Attack" << std::endl;
		}
	}
}

InputManager::~InputManager()
{
	delete sInstance;

	std::map<Pawn*, SDL_GameController*>::iterator it;
	for (it = ControlledPawn.begin(); it != ControlledPawn.end(); it++)
	{
		ControlledPawn.erase(it);
	}

	std::map<int, SDL_GameController*>::iterator it2;
	for (it2 = ControllerIndex.begin(); it2 != ControllerIndex.end(); it2++)
	{
		ControllerIndex.erase(it2);
	}

	std::map<std::string, SDL_Scancode>::iterator it3;
	for (it3 = KeyboardKeys.begin(); it3 != KeyboardKeys.end(); it3++)
	{
		KeyboardKeys.erase(it3);
	}
}