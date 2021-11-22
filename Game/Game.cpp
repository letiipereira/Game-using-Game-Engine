// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "GameEngine.h"
#include "Spaceship.h"
#include "Entity.h"
#include <Vector2D.h>

int main(int argc, char** argv)
{

    GameEngine::GetInstance()->init("Xennon Clone.", 640, 480);

    //set up do level

    Entity newEnt;
    newEnt.AddComponent<SpriteComponent>("background", "assets/galaxy2.bmp", 0);

    Entity newEnt2;
    newEnt2.AddComponent<SpriteComponent>("logo", "assets/logo.bmp", 1);
    //newEnt->AddGroup(GameEngine::GetInstance()->groupMap);

    //Entity gAster;
    //gAster.AddComponent<Animation>("AsteroidAnim", "assets/LonerB.bmp", 1, 4, 4, 100, false, 2);
    //gAster.GetComponent<Transform>().myPosition.X = 100;
    //gAster.GetComponent<Transform>().myPosition.Y = 100;
    //gAster.AddComponent<Rigidbody>();

    Spaceship currentPlayer;

    // maybe we could have this code in the player init function 

    currentPlayer.AddComponent<Animator>();

    Animation* moveRight = new Animation("moveRight", "assets/Ship1.bmp", 1, 7, 1, 7, 1, 5, 7, false, 6, false, true, false);
    Animation* moveLeft = new Animation("moveLeft", "assets/Ship1.bmp", 1, 7, 1, 3, 1, 1, 7, false, 6, false, false, false);
    Animation* idle = new Animation("idle", "assets/Ship1.bmp", 1, 7, 1, 4, 1, 4, 7, false, 6, false, false, false);

    currentPlayer.GetComponent<Animator>().AddAnimation("moveRight", moveRight);
    currentPlayer.GetComponent<Animator>().AddAnimation("moveLeft", moveLeft);
    currentPlayer.GetComponent<Animator>().AddAnimation("idle",idle);

    currentPlayer.GetComponent<Transform>().myPosition.X = 100;
    currentPlayer.GetComponent<Transform>().myPosition.Y = 100;

    //newEnt2->AddGroup(GameEngine::GetInstance()->groupUI);

    GameEngine::GetInstance()->start();

    // game logic

    delete moveRight, moveLeft, idle;

    return 0;
}
