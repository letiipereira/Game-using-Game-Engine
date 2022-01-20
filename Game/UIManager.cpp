#include "UIManager.h"
#include <iostream>
#include "Transform.h"
#include "Text.h"

UIManager* UIManager::sInstance{ nullptr };

UIManager::UIManager()
{
    /*int count = 0;

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
    }*/
}

//void UIManager::DrawText(std::string textToRender, CharacterType type, float x, float y, int layer, bool isStatic, std::vector<Icon*>& letters)
//{
//    switch (type)
//    {
//    case CharacterType::small:
//    {
//        for (char& character : textToRender)
//        {
//            Character ch = smallCharacters[character];
//
//            std::string textureID = std::to_string(character);
//
//            Icon* newLetter = new Icon(textureID, "assets/Font8x8.bmp", x, y, true, ch.rowCurrent, ch.colCurrent, ch.rowTotal, ch.colTotal, layer);
//            
//            // If the text is refered to a varaible that will be updated from time to time
//            if (!isStatic)
//            {
//                letters.push_back(newLetter);
//            }
//
//            // now advance cursors for the next character
//            x += ch.Advance;
//        }
//
//        break;
//    }
//    case CharacterType::big:
//    {
//        for (char& character : textToRender)
//        {
//            Character ch = bigCharacters[character];
//
//            std::string textureID = std::to_string(character);
//
//            Icon* newLetter = new Icon(textureID, "assets/font16x16.bmp", x, y, true, ch.rowCurrent, ch.colCurrent, ch.rowTotal, ch.colTotal, layer);
//
//            // If the text is refered to a varaible that will be updated from time to time
//            if (!isStatic)
//            {
//                letters.push_back(newLetter);
//            }
//
//            // now advance cursors for the next character
//            x += ch.Advance;
//        }
//
//        break;
//    }
//    default:
//        break;
//    }
//}

void UIManager::DrawIcons(std::string textureID, std::string filePath, float x, float y, int layer, std::vector<Icon*>& icons)
{
    Icon* newIcon = new Icon(textureID, filePath, x, y, true, 1, 1, 1, 1, layer);

    icons.push_back(newIcon);
    //lifes.push_back(newIcon);
}

void UIManager::SetMaxLifes(int maxLifes)
{
    playerLifes = maxLifes;
    DrawLifes(playerLifes);
}

void UIManager::DrawUI()
{
    DrawTitles();
    DrawScore("0000000000");
    DrawHighScore();
    DrawHealthBar();
}

void UIManager::UpdateScore(int newScore)
{
    for (Icon* number : score)
    {
        number->Destroy();
    }

    std::cout << score.size() << std::endl;
    std::cout << score[1] << std::endl;

    score.clear();

    playerScore += newScore;

    std::string updatedScore = std::to_string(playerScore);

    int charNumber = updatedScore.size();
    int zeros = 10 - charNumber;
    std::string zerosString{};

    for (int i = 0; i < zeros; i++)
    {
        zerosString.append("0");
    }

    std::string finalScore = zerosString.append(updatedScore);

    DrawScore(finalScore);
}

void UIManager::UpdateHealth(int maxHealth, int health)
{
    float percentage = (float)health / (float)maxHealth;
    int healthWidth = healthBar->GetComponent<SpriteComponent>().GetWidth();

    healthBar->GetComponent<Transform>().myScale.X = percentage;
    //healthBar->GetComponent<Transform>().myPosition.X = barPosition.X - (barPosition.X / 1.6);
}

void UIManager::UpdateLifes(int lifeNumber)
{
    for (Icon* lifeIcon : lifes)
    {
        lifeIcon->Destroy();
    }

    lifes.clear();

    DrawLifes(lifeNumber);
}

void UIManager::DrawTitles()
{
    int hiPosX = (GameEngine::GetInstance()->GameWindowWidht() / 2) - 40.f;
    int hiPosY = (GameEngine::GetInstance()->GameWindowHeight() / 2) + 220.f;
    //DrawText("Hi Score", CharacterType::small, hiPosX, hiPosY, 10, true, staticIcons);
    Text* hiScoreTitle = new Text("Hi Score", "hiScoreTitle", TextType::small, 0, hiPosX, hiPosY, 10, true);

    int scoreTitlePosX = (GameEngine::GetInstance()->GameWindowWidht() / 2) - 300.f;
    int scoreTitlePosY = (GameEngine::GetInstance()->GameWindowHeight() / 2) + 220.f;
    //DrawText("Player One", CharacterType::small, scoreTitlePosX, scoreTitlePosY, 10, true, staticIcons);
    Text* playerTitle = new Text("Player One", "playerTitle", TextType::small, 0, scoreTitlePosX, scoreTitlePosY, 10, true);
}

void UIManager::DrawScore(std::string currentScore)
{
    // Draw the high score
    int scorePosX = (GameEngine::GetInstance()->GameWindowWidht() / 2) - 300.f;
    int scorePosY = (GameEngine::GetInstance()->GameWindowHeight() / 2) + 200.f;

    //DrawText(currentScore, CharacterType::big, scorePosX, scorePosY, 10, false, score);
    Text* score = new Text(currentScore, "currentScore", TextType::big, 0, scorePosX, scorePosY, 10, false);
}

void UIManager::DrawHighScore()
{
    // Draw the current score
    hiScorePosX = (GameEngine::GetInstance()->GameWindowWidht() / 2) - 47.f;
    hiScorePosY = (GameEngine::GetInstance()->GameWindowHeight() / 2) + 205.f;

    //DrawText("0000000000", CharacterType::small, hiScorePosX, hiScorePosY, 10, false, highScore);
    Text* hiScore = new Text("0000000000", "hiScore", TextType::big, 0, scorePosX, scorePosY, 10, false);
}

void UIManager::DrawLifes(int totalLifes)
{
    float posX = 30.f;
    float posY = 60.f;

    for (int i = 0; i < totalLifes; i++)
    {        
        DrawIcons("icon", "assets/PULife.bmp", posX, posY, 10, lifes);

        // now advance cursors for the next character
        posX += 40.f;
    }    
}

void UIManager::DrawHealthBar()
{
   healthBar = new Icon("healthBorder", "assets/healthBar.bmp", barPosition.X, barPosition.Y, false, 1, 1, 1, 1, 9);

   Icon* healthBorder = new Icon("healthBorder", "assets/healthBorder.bmp", barPosition.X, barPosition.Y, false, 1, 1, 1, 1, 10);
   staticIcons.push_back(healthBorder);
}
