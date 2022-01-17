#pragma once

//#ifndef UIMANAGER_M
//#define UIMANAGER_M

#include <string>
#include <vector>
#include <map>
#include "Letter.h"

struct Character {
	char letter;		   // Letter to render
	int rowTotal;          // Total number of rows
	int colTotal;          // Total number of columns
	int rowCurrent;        // Character current row
	int colCurrent;	       // Character current col
	int Advance;	       // Offset to advance to next character
};

enum class CharacterType { small, big };

class UIManager
{
public:

	UIManager();
	~UIManager() {};

	void DrawUI();
	//void UpdateScore(int newScore);
	//void UpdateHealth(int health);
	//void UpdateLifes(int lifeNumber);

	static UIManager* GetInstance() { return sInstance = (sInstance != nullptr) ? sInstance : new UIManager(); }
	void DrawText(std::string textToRender, CharacterType type, float x, float y, int layer, bool isStatic, std::vector<Letter*> letters);

private:

	static UIManager* sInstance;
	std::vector<char> characters
	{
	' ', '!', '"', '#', '$', '%', '&', '²',
	'(', ')', '*', '+', ',', '-', '.', '/',
	'0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', ':', ';', '<', '=', '>', '?',
	'©', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
	'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
	'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
	'X', 'Y', 'Z', '[', '³', ']', '^', '_',
	'`', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
	'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
	'p', 'q', 'r', 's', 't', 'u', 'v', 'w',
	'x', 'y', 'z', '{', '╎', '}', '~', '¤'
	};

	int scorePosX = {};
	int scorePosY = {};
	int hiScorePosX = {};
	int hiScorePosY = {};

	void DrawScore();
	void DrawHighScore();
	void DrawLifes();
	void DrawHealthBar();

	std::map<char, Character> smallCharacters{};
	std::map<char, Character> bigCharacters{};
	std::vector<Letter*> score{};
	std::vector<Letter*> highScore{};
};

//#endif // UIMANAGER_M