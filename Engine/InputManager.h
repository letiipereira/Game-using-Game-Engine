#pragma once

#ifndef INPUTMANAGER_M
#define INPUTMANAGER_M

#include <SDL.h>
#include <iostream>
#include "Pawn.h"
#include "SDL_gamecontroller.h"

class InputManager
{

public:
	InputManager();

	~InputManager()
	{
		delete sInstance;
	};

	static InputManager* GetInstance() { return sInstance = (sInstance != nullptr) ? sInstance : new InputManager(); }

	void CheckInput(SDL_Event gamepadEvent/*, Pawn* pawn*/);

	enum class InputType { move_right, move_left, move_up, move_down, attack };

private:
	static InputManager* sInstance;
	const Uint8* keyState;
};

#endif // INPUTMANAGER_M