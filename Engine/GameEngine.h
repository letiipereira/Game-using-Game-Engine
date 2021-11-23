#pragma once
#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <vector>
#include <string>
#include <map>

class GameEngine //should be the only one -> make sure of it
{
public:
	void init(std::string windowTitle, int windowWidth, int windowHeight);
	void start();

	class Window* GetWindow();
	static GameEngine* GetInstance();

	void ActivateLevelByName(std::string levelName);
	class Level* GetActiveLevel();
	class InputManager* GetInputManager();
	void CreateNewLevel(std::string levelName);
	void DeleteLevelByName(std::string levelName);
	class Level* GetLevelByName(std::string levelName);
	float GetDeltatime() { return deltaTime; }

	/*enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupColliders,
		groupProjectiles,
		groupBackground,
		groupUI,
	};*/

	GameEngine();

	~GameEngine();

private:
	int prevTime;
	int currentTime;
	float deltaTime;
	static GameEngine* instance;
	class TextureManager* textureManager{ nullptr };
	class SDLWrapper* sdl{ nullptr };
	class Window* window{ nullptr };
	class Level* currentLevel{ nullptr };
	class Level* defaultLevel{ nullptr };
	std::map<std::string, class Level*> levelMap;
};

#endif //