#include <SDL.h>
#include <iostream>
#include "InputManager.h"

InputManager* InputManager::sInstance{ nullptr };

InputManager::InputManager()
{
	keyState = SDL_GetKeyboardState(NULL);

	SDL_GameController* controller;

	const int numJoysticks = SDL_NumJoysticks();
	for (int i = 0; i < numJoysticks; i++)
	{
		if (SDL_IsGameController(i)) {
			char* mapping;
			std::cout << "Index '" << i << "' is a compatible controller, named '" <<
				SDL_GameControllerNameForIndex(i) << "'" << std::endl;
			controller = SDL_GameControllerOpen(i);
			mapping = SDL_GameControllerMapping(controller);
			std::cout << "Controller " << i << " is mapped as \"" << mapping << std::endl;
			SDL_free(mapping);
			SDL_GameControllerUpdate();
		}
		else {
			std::cout << "Index '" << i << "' is not a compatible controller." << std::endl;
		}

	}
}

void InputManager::CheckInput(SDL_Event gamepadEvent/*, Pawn* pawn*/)
{
	if (keyState[SDL_SCANCODE_RIGHT] || (gamepadEvent.type == SDL_CONTROLLERBUTTONDOWN && gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
	{
		//pawn->Move(Pawn::MovementType::move_right);
		std::cout << "Right" << std::endl;
	}

	if (keyState[SDL_SCANCODE_LEFT] || (gamepadEvent.type == SDL_CONTROLLERBUTTONDOWN && gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT))
	{
		//pawn->Move(Pawn::MovementType::move_left);
		std::cout << "Left" << std::endl;
	}

	if (keyState[SDL_SCANCODE_UP] || (gamepadEvent.type == SDL_CONTROLLERBUTTONDOWN && gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP))
	{
		//pawn->Move(Pawn::MovementType::move_up);
		std::cout << "Up" << std::endl;
	}

	if (keyState[SDL_SCANCODE_DOWN] || (gamepadEvent.type == SDL_CONTROLLERBUTTONDOWN && gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN))
	{
		//pawn->Move(Pawn::MovementType::move_down);
		std::cout << "Down" << std::endl;
	}

	if (keyState[SDL_SCANCODE_SPACE] /* || (gamepadEvent.type == SDL_CONTROLLERBUTTONDOWN && gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_A)*/)
	{
		//pawn->Attack();
		std::cout << "Attack" << std::endl;
	}

	if (gamepadEvent.type == SDL_CONTROLLERBUTTONDOWN)
	{
		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_B)
		{
			std::cout << "Right" << std::endl;
		}

		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT)
		{
			std::cout << "Left" << std::endl;
		}

		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP)
		{
			std::cout << "Up" << std::endl;
		}

		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN)
		{
			std::cout << "Down" << std::endl;
		}

		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_A)
		{
			std::cout << "Attack" << std::endl;
		}
	}

}
