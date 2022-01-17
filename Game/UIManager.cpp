#include "UIManager.h"
#include <iostream>
#include "Entity.h"
#include "level.h"
#include "Transform.h"

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
            8
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

void UIManager::DrawText(std::string textToRender, CharacterType type, float x, float y, int layer, bool isStatic, std::vector<Letter*> letters)
{
    switch (type)
    {
    case CharacterType::small:
    {
        for (char& character : textToRender)
        {
            Character ch = smallCharacters[character];

            std::string textureID = std::to_string(character);

            Letter* newLetter = new Letter(textureID, "assets/Font8x8.bmp", x, y, ch.rowCurrent, ch.colCurrent, ch.rowTotal, ch.colTotal, layer);
            
            // If the text is refered to a varaible that will be updated from time to time
            if (!isStatic)
            {
                letters.push_back(newLetter);
            }

            // now advance cursors for the next character
            x += ch.Advance;
        }

        break;
    }
    case CharacterType::big:
    {
        for (char& character : textToRender)
        {
            Character ch = bigCharacters[character];

            std::string textureID = std::to_string(character);

            Letter* newLetter = new Letter(textureID, "assets/font16x16.bmp", x, y, ch.rowCurrent, ch.colCurrent, ch.rowTotal, ch.colTotal, layer);

            // If the text is refered to a varaible that will be updated from time to time
            if (!isStatic)
            {
                letters.push_back(newLetter);
            }

            // now advance cursors for the next character
            x += ch.Advance;
        }

        break;
    }
    default:
        break;
    }
}

void UIManager::DrawUI()
{
    DrawScore();
    DrawHighScore();
    //DrawLifes();
    //DrawHealthBar();
}

void UIManager::DrawScore()
{
    // Draw the high score title
    int titlePosX = (GameEngine::GetInstance()->GameWindowWidht() / 2) - 40.f;
    int titlePosY = (GameEngine::GetInstance()->GameWindowHeight() / 2) + 220.f;
    DrawText("Hi Score", CharacterType::small, titlePosX, titlePosY, 10, true, {});

    // Draw the high score
    int scorePosX = (GameEngine::GetInstance()->GameWindowWidht() / 2) - 47.f;
    int scorePosY = (GameEngine::GetInstance()->GameWindowHeight() / 2) + 205.f;
    DrawText("0000000000", CharacterType::small, scorePosX, scorePosY, 10, false, highScore);
}

void UIManager::DrawHighScore()
{
    // Draw the title
    int titlePosX = (GameEngine::GetInstance()->GameWindowWidht() / 2) - 300.f;
    int titlePosY = (GameEngine::GetInstance()->GameWindowHeight() / 2) + 220.f;
    DrawText("Player One", CharacterType::small, titlePosX, titlePosY, 10, true, {});

    // Draw the current score
    hiScorePosX = (GameEngine::GetInstance()->GameWindowWidht() / 2) - 300.f;
    hiScorePosY = (GameEngine::GetInstance()->GameWindowHeight() / 2) + 200.f;
    DrawText("0000000000", CharacterType::big, hiScorePosX, hiScorePosY, 10, true, {});
}
