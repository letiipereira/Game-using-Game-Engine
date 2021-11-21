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
		currentPlayer->Move(Pawn::MovementType::move_right, GameEngine::GetInstance()->GetDeltatime());
		std::cout << "Right" << std::endl;
	}

	if (keyState[SDL_SCANCODE_LEFT])
	{
		currentPlayer->Move(Pawn::MovementType::move_left, GameEngine::GetInstance()->GetDeltatime());
	}

	if (keyState[SDL_SCANCODE_UP])
	{
		currentPlayer->Move(Pawn::MovementType::move_up, GameEngine::GetInstance()->GetDeltatime());
	}

	if (keyState[SDL_SCANCODE_DOWN])
	{
		currentPlayer->Move(Pawn::MovementType::move_down, GameEngine::GetInstance()->GetDeltatime());
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

		if (gamepadEvent.jaxis.axis == 0)
		{
			if (-32768 <= gamepadEvent.jaxis.value && gamepadEvent.jaxis.value < 128)
			{
				currentPlayer->Move(Pawn::MovementType::move_left, GameEngine::GetInstance()->GetDeltatime());
				std::cout << "Left" << std::endl;
			}

			if (128 < gamepadEvent.jaxis.value && gamepadEvent.jaxis.value <= 32767)
			{
				currentPlayer->Move(Pawn::MovementType::move_right, GameEngine::GetInstance()->GetDeltatime());
				std::cout << "Right" << std::endl;
			}
		}

		if (gamepadEvent.jaxis.axis == 1)
		{
			if (-32768 <= gamepadEvent.jaxis.value && gamepadEvent.jaxis.value < 128)
			{
				currentPlayer->Move(Pawn::MovementType::move_up, GameEngine::GetInstance()->GetDeltatime());
			}

			if (128 < gamepadEvent.jaxis.value && gamepadEvent.jaxis.value <= 32767)
			{
				currentPlayer->Move(Pawn::MovementType::move_down, GameEngine::GetInstance()->GetDeltatime());
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