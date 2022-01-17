// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "GameEngine.h"
#include "Spaceship.h"
#include "Entity.h"
#include <Vector2D.h>
#include "Spawner.h"
#include "level.h"
#include "loner.h"
#include "rusher.h"
#include "UIManager.h"

int main(int argc, char** argv)
{

    GameEngine::GetInstance()->init("Xennon Clone.", 640, 480);

    //set up do level

    Entity* newEnt = new Entity;
    newEnt->AddComponent<SpriteComponent>("background", "assets/galaxy2.bmp", 0);
    newEnt->GetComponent<Transform>().myPosition.X = static_cast<float>(GameEngine::GetInstance()->GameWindowWidht() / 2);
    newEnt->GetComponent<Transform>().myPosition.Y = static_cast<float>(GameEngine::GetInstance()->GameWindowHeight() / 2);


    Spawner* spawner = new Spawner;

    Spaceship* currentPlayer = new Spaceship;
    currentPlayer->GetComponent<Transform>().myPosition.X = static_cast<float>(GameEngine::GetInstance()->GameWindowWidht() / 2);
    currentPlayer->GetComponent<Transform>().myPosition.Y = static_cast<float>(GameEngine::GetInstance()->GameWindowHeight() / 2);

    spawner->SetPlayerReference(currentPlayer);
    
    //não é necessario dar delete dos "Enities" criados. O nível cuida disto :)

    UIManager::GetInstance()->DrawUI();

    //newEnt2->AddGroup(GameEngine::GetInstance()->groupUI);

    GameEngine::GetInstance()->start();

    // game logic
    delete UIManager::GetInstance();
    delete GameEngine::GetInstance();
    
    return 0;
}
