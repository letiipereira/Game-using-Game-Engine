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

int main(int argc, char** argv)
{
    GameEngine::GetInstance()->init("Xennon Clone.", 640, 480);

    //set up do level

    Entity newEnt;
    newEnt.AddComponent<SpriteComponent>("background", "assets/galaxy2.bmp", 0);

    Entity newEnt2;
    newEnt2.AddComponent<SpriteComponent>("logo", "assets/logo.bmp", 1);
    //newEnt->AddGroup(GameEngine::GetInstance()->groupMap);

    Spawner spawner;
    Spaceship currentPlayer;

    //newEnt2->AddGroup(GameEngine::GetInstance()->groupUI);

    GameEngine::GetInstance()->start();

    // game logic

    return 0;
}
