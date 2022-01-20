#pragma once

//#ifndef UIMANAGER_M
//#define UIMANAGER_M

#include <string>
#include <vector>
#include <map>
#include "Icon.h"
#include "Text.h"

//struct Character {
//	char letter;		   // Letter to render
//	int rowTotal;          // Total number of rows
//	int colTotal;          // Total number of columns
//	int rowCurrent;        // Character current row
//	int colCurrent;	       // Character current col
//	int Advance;	       // Offset to advance to next character
//};

enum class CharacterType { small, big };

class UIManager : public Entity
{
public:

	UIManager();
	~UIManager() {};

	void DrawUI();
	void UpdateScore(int newScore);
	void UpdateHealth(int maxHealth, int health);
	void UpdateLifes(int lifeNumber);

	static UIManager* GetInstance() { return sInstance = (sInstance != nullptr) ? sInstance : new UIManager(); }
	void DrawIcons(std::string textureID, std::string filePath, float x, float y, int layer, std::vector<Icon*>& icons);
	void SetMaxLifes(int maxLifes);

private:

	static UIManager* sInstance;

	int playerScore = {};
	int scorePosX = {};
	int scorePosY = {};
	int hiScorePosX = {};
	int hiScorePosY = {};
	int playerLifes = {};

	void DrawTitles();
	void DrawScore(std::string currentScore);
	void DrawHighScore();
	void DrawLifes(int totalLifes);
	void DrawHealthBar();

	Icon* healthBar{};
	Text* hiScoreText{};
	Text* scoreText{};
	Vector2D barPosition{ 100.f, 25.f};
	std::vector<Icon*> staticIcons{};
	std::vector<Icon*> lifes{};
};

//#endif // UIMANAGER_M