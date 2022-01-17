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

    Entity newEnt;
    newEnt.AddComponent<SpriteComponent>("background", "assets/galaxy2.bmp", 0, 0);
    
    newEnt.GetComponent<Transform>().myPosition.X = GameEngine::GetInstance()->GameWindowWidht() / 2;
    newEnt.GetComponent<Transform>().myPosition.Y = GameEngine::GetInstance()->GameWindowHeight() / 2;


    UIManager::GetInstance()->DrawText("NEW SCORE0123", CharacterType::big, 300.f, 300.f, 10);
    UIManager::GetInstance()->DrawText("MIAU", CharacterType::small, 100.f, 100.f, 10);

    Spawner spawner;
    Spaceship currentPlayer;
    spawner.SetPlayerReference(&currentPlayer);

    //newEnt2->AddGroup(GameEngine::GetInstance()->groupUI);

    GameEngine::GetInstance()->start();

    // game logic
    delete UIManager::GetInstance();
    delete GameEngine::GetInstance();

    return 0;
}
