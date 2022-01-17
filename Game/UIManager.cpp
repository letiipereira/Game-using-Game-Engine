#include "UIManager.h"
#include <iostream>
#include "Entity.h"
#include "level.h"
#include "Transform.h"
#include "Letter.h"

UIManager* UIManager::sInstance{ nullptr };

UIManager::UIManager()
{
    int count = 0;
    int bigCharCurrentRow = 12;
    int bigCharCurrentCol = 1;

    int smallCharCurrentRow = 16;
    int smallCharCurrentCol = 1;

    for (int character = 0; character < characters.size(); character++)
    {
        Character newSmallCharacter = {
            characters[character],
            16,
            8,
            smallCharCurrentRow,
            smallCharCurrentCol,
            16
        };

        std::cout << "characters[character] " << characters[character] << std::endl;

        Character newBigCharacter = {
            characters[character],
            12,
            8,
            bigCharCurrentRow,
            bigCharCurrentCol,
            16
        };

        smallCharacters.insert(std::pair<char, Character>(character, newSmallCharacter));
        bigCharacters.insert(std::pair<char, Character>(character, newBigCharacter));

        if (bigCharCurrentCol < 8 || smallCharCurrentCol < 8)
        {
            bigCharCurrentCol++;
            smallCharCurrentCol++;
        }
        else
        {
            bigCharCurrentCol = 1;
            smallCharCurrentCol = 1;

           bigCharCurrentRow--;
            smallCharCurrentRow--;
        }
    }
}

void UIManager::DrawText(std::string text, CharacterType type, float x, float y, int layer)
{
    switch (type)
    {
    case CharacterType::small:
    {
        for (char& character : text)
        {
            Character ch = smallCharacters[character];

            std::string textureID = std::to_string(character);

            Letter* newLetter = new Letter(textureID, "assets/font8x8.bmp", x, y, ch.rowCurrent, ch.colCurrent, ch.rowTotal, ch.colTotal, layer);

            // now advance cursors for the next character
            x += ch.Advance;

            std::cout << character << std::endl;
        }

        break;
    }
    case CharacterType::big:
    {
        for (char& character : text)
        {
            Character ch = bigCharacters[character];

            std::string textureID = std::to_string(character);

            Letter* newLetter = new Letter(textureID, "assets/Font16x16.bmp", x, y, ch.rowCurrent, ch.colCurrent, ch.rowTotal, ch.colTotal, layer);

            // now advance cursors for the next character
            x += ch.Advance;

            std::cout << character << std::endl;
        }

        break;
    }
    default:
        break;
    }
}
