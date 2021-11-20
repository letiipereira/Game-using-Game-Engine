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
	void CreateNewLevel(std::string levelName);
	void DeleteLevelByName(std::string levelName);
	class Level* GetLevelByName(std::string levelName);

	/*enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupColliders,
		groupProjectiles,
		groupBackground,
		groupUI,
	};*/

	~GameEngine();

private:

	GameEngine() {};
	static GameEngine* instance;
	class TextureManager* textureManager{nullptr};
	class SDLWrapper* sdl{ nullptr };
	class Window* window{ nullptr };
	class Level* currentLevel{ nullptr };
	class Level* defaultLevel{ nullptr };
	std::map<std::string, class Level*> levelMap;
};

#endif //