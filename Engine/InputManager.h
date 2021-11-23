#pragma once

#ifndef INPUTMANAGER_M
#define INPUTMANAGER_M

#include <iostream>
#include <map>
#include <vector>
#include "SDL.h"
#include "SDL_gamecontroller.h"

class InputManager
{

public:
	InputManager();

	~InputManager();

	int numControllers;

	// Create a singleton
	static InputManager* GetInstance() { return sInstance = (sInstance != nullptr) ? sInstance : new InputManager(); }

	void AddPawn(class Pawn* pawn);

	// Map the new connected controller
	void MapNewController(int controllerIndex);

	// Check the player's keyboard input
	void CheckKeyboardInput(SDL_Event gamepadEvent, class Pawn* currentPlayer);

	// Check the player's controller input
	void CheckControllerInput(SDL_Event gamepadEvent);

	// Pawn and their respective controller
	std::map<Pawn*, SDL_GameController*> ControlledPawn{};

	// Controller and corresponding index
	std::map<int, SDL_GameController*> ControllerIndex{};

	std::map<std::string, SDL_Scancode> KeyboardKeys{};

	// Update the pawn and controller relation
	void UpdateController(std::map<Pawn*, SDL_GameController*> updatedControllerMap) { ControlledPawn = updatedControllerMap; }

	void UpdateControllerIndex(std::map<int, SDL_GameController*> updatedIndex) { ControllerIndex = updatedIndex; };

private:
	static InputManager* sInstance;
	const Uint8* keyState;
	float joystickDeadZone = 8000.0f;
};

#endif // INPUTMANAGER_M#pragma once
