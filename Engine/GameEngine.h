#pragma once
#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <string>

 class GameEngine //should be the only one -> make sure of it
{ 
public:
	void init(std::string windowTitle, int windowWidth, int windowHeight);

	void start();

	class Window* GetWindow();

	static GameEngine* GetInstance();
	
	~GameEngine();

private:
	GameEngine() {};
	static GameEngine* sInstance;
	class TextureManager* textureManager{nullptr};
	class SDLWrapper* sdl{ nullptr };
	class Window* window{ nullptr };
};

#endif //