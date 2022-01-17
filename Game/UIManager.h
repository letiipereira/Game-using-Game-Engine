#pragma once

//#ifndef UIMANAGER_M
//#define UIMANAGER_M

#include <string>
#include <vector>
#include <map>

struct Character {
	int TextureID;         // ID handle of the character texture
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

	static UIManager* GetInstance() { return sInstance = (sInstance != nullptr) ? sInstance : new UIManager(); }
	void DrawText(std::string text, CharacterType type, float x, float y, int layer);

private:

	static UIManager* sInstance;
	/*std::vector<char> characters{
	' ', '!', '"', '#', '$', '%', '&', 'ˈ', '(', ')', '*', '+', ',', '-', '.', '/',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	':', ';', '<', '=', '>', '?', '©',
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	'[', ' ', ']', '^', '_', '`',
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	'{', '╎', '}', '—', '☐' };*/
	std::vector<char> characters
	{
		'x', 'y', 'z', '{', '╎', '}', '—', '~',
		'p', 'q', 'r', 's', 't', 'u', 'v', 'w',
		'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
		'`', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
		'X', 'Y', 'Z', '[', ' ', ']', '^', '_',
		'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
		'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
		'©', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
		'8', '9', ':', ';', '<', '=', '>', '?',
		'0', '1', '2', '3', '4', '5', '6', '7',
		'(', ')', '*', '+', ',', '-', '.', '/',
		' ', '!', '"', '#', '$', '%', '&', 'ˈ'
	};
	std::map<char, Character> smallCharacters{};
	std::map<char, Character> bigCharacters{};
};

//#endif // UIMANAGER_M