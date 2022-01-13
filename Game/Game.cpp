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
    
    newEnt.GetComponent<Transform>().myPosition.X = GameEngine::GetInstance()->GameWindowWidht() / 2;
    newEnt.GetComponent<Transform>().myPosition.Y = GameEngine::GetInstance()->GameWindowHeight() / 2;

    /*Entity newEnt2;
    newEnt2.AddComponent<Animator>();
    Animation* anim = new Animation("idleLoner", "assets/LonerA.bmp", 4, 4, 4, 4, 1, 1, 4, false, 2, true, true, true);
    newEnt2.GetComponent<Animator>().AddAnimation("idleLoner", anim);

    newEnt2.GetComponent<Transform>().myPosition.X = GameEngine::GetInstance()->GameWindowWidht() / 2;
    newEnt2.GetComponent<Transform>().myPosition.Y = GameEngine::GetInstance()->GameWindowHeight() / 2;*/

    Spawner spawner;
    Spaceship currentPlayer;
    spawner.SetPlayerReference(&currentPlayer);

    //newEnt2->AddGroup(GameEngine::GetInstance()->groupUI);

    GameEngine::GetInstance()->start();

    // game logic
    delete GameEngine::GetInstance();

    return 0;
}
