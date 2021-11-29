#pragma once
#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <vector>
#include <string>
#include <map>

class GameEngine
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

	class b2World* GetWorld();

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
	class b2World* world;
	class b2World* world2;
	static GameEngine* instance;
	class TextureManager* textureManager{ nullptr };
	class SDLWrapper* sdl{ nullptr };
	class Window* window{ nullptr };
	class Level* currentLevel{ nullptr };
	class Level* defaultLevel{ nullptr };
	std::map<std::string, class Level*> levelMap;
	class Temp* tempListener;
};

#endif //