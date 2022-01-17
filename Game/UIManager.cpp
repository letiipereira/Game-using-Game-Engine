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

    int bigCharCurrentRow = 1;
    int bigCharCurrentCol = 1;

    int smallCharCurrentRow = 1;
    int smallCharCurrentCol = 1;

    for (int character = 0; character < characters.size(); character++)
    {
        Character newSmallCharacter ={
            characters[character],
            16,
            8,
            smallCharCurrentRow,
            smallCharCurrentCol,
            16
        };

        Character newBigCharacter = {
            characters[character],
            12,
            8,
            bigCharCurrentRow,
            bigCharCurrentCol,
            16
        };

        smallCharacters.insert(std::pair<char, Character>(characters[character], newSmallCharacter));
        bigCharacters.insert(std::pair<char, Character>(characters[character], newBigCharacter));

        if (bigCharCurrentCol < 8 || smallCharCurrentCol < 8)
        {
            bigCharCurrentCol++;
            smallCharCurrentCol++;
        }
        else if (bigCharCurrentCol >= 8 || smallCharCurrentCol >= 8)
        {
            bigCharCurrentCol = 1;
            smallCharCurrentCol = 1;

            bigCharCurrentRow++;
            smallCharCurrentRow++;
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
        }

        break;
    }
    default:
        break;
    }
}
