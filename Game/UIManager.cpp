#include "UIManager.h"
#include <iostream>
#include "Transform.h"

UIManager* UIManager::sInstance{ nullptr };

UIManager::UIManager()
{
    
}


void UIManager::DrawIcons(std::string textureID, std::string filePath, float x, float y, int layer, std::vector<Icon*>& icons)
{
    Icon* newIcon = new Icon(textureID, filePath, x, y, true, 1, 1, 1, 1, layer);

    icons.push_back(newIcon);
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
    scoreText->Destroy();
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

    if (percentage > 0.5)
    {

    }
    else if (percentage <= 0.5 && percentage > 0.3)
    {

    }
    else if (percentage <= 0.3)
    {

    }
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
    Text* hiScoreTitle = new Text("Hi Score", "hiScoreTitle", TextType::small, 0, hiPosX, hiPosY, 10);

    int scoreTitlePosX = (GameEngine::GetInstance()->GameWindowWidht() / 2) - 300.f;
    int scoreTitlePosY = (GameEngine::GetInstance()->GameWindowHeight() / 2) + 220.f;
    Text* playerTitle = new Text("Player One", "playerTitle", TextType::small, 0, scoreTitlePosX, scoreTitlePosY, 10);
}

void UIManager::DrawScore(std::string currentScore)
{
    // Draw the high score
    int scorePosX = (GameEngine::GetInstance()->GameWindowWidht() / 2) - 300.f;
    int scorePosY = (GameEngine::GetInstance()->GameWindowHeight() / 2) + 200.f;

    scoreText = new Text(currentScore, "currentScore", TextType::big, 0, scorePosX, scorePosY, 10);
}

void UIManager::DrawHighScore()
{
    // Draw the high score
    hiScorePosX = (GameEngine::GetInstance()->GameWindowWidht() / 2) - 47.f;
    hiScorePosY = (GameEngine::GetInstance()->GameWindowHeight() / 2) + 205.f;

    hiScoreText = new Text("0000000000", "hiScore", TextType::small, 0, hiScorePosX, hiScorePosY, 10);
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
