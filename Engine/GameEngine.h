#pragma once
#include <string>

class GameEngine //should be the only one -> make sure of it
{ 
public:
	void init(std::string windowTitle, int windowWidth, int windowHeight);

	void start();

	class Window* GetWindow();

	~GameEngine();

private:
	class SDLWrapper* sdl;
	class Window* window;
};

