#include "CollisionListener.h"
#include "GameEngine.h"
#include "Collider.h"
#include <iostream>

CollisionListener* CollisionListener::sInstance{ nullptr };

CollisionListener::CollisionListener()
{
    //GameEngine::GetInstance()->GetWorld()->SetContactListener(this);
}

void CollisionListener::BeginContact(b2Contact* contact)
{
    std::cout << "GenericHello" << std::endl;

    void* userData = (void*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;

    if (userData)
    {
        GameEngine* textCol = static_cast<GameEngine*>(userData);

        if (textCol)
        {
            std::cout << "hello" << std::endl;
        }
        else
        {
            std::cout << "helloNull" << std::endl;
        }

    }
}