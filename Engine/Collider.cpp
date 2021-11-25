#include "Collider.h"
#include "Rigidbody.h"
#include "Entity.h"
#include "GameEngine.h"
#include <box2d/box2d.h>

Collider::~Collider()
{
	GameEngine::GetInstance()->GetWorld()->DestroyBody(body);
	//std::cout << "DESTROY COLIDER" << std::endl;
}

bool Collider::Init()
{
	transform = &entity->GetComponent<Transform>();

	return true;
}

void Collider::Update()
{
	transform = &entity->GetComponent<Transform>();
}

void Collider::AddAttributes(float objectLocationX, float objectLocationY, float colliderWidth, float colliderHeight, float gravity)
{
	//Define the dynamic body. We set its position and call the body factory.

	b2BodyDef objectBodyDef;
	objectBodyDef.type = b2_dynamicBody;
	objectBodyDef.position.Set(objectLocationX, objectLocationY);
	objectBodyDef.userData.pointer = (uintptr_t)this;
	objectBodyDef.bullet = true;

	body = GameEngine::GetInstance()->GetWorld()->CreateBody(&objectBodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(colliderWidth / 2.0f, colliderHeight / 2.0f);
	colliderHalfWidth = colliderWidth / 2.0f;
	colliderHalfHeight = colliderHeight / 2.0f;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	fixtureDef.density = 1.0f;
	fixtureDef.isSensor = true;

	body->CreateFixture(&fixtureDef);
	//body->SetLinearVelocity(b2Vec2(0, -80.0f));
	body->SetGravityScale(gravity);
}

void Collider::SetPosition(float objectLocationX, float objectLocationY)
{
	b2Vec2 newPos;
	newPos.x = objectLocationX + colliderHalfWidth;
	newPos.y = objectLocationY + colliderHalfHeight;
	body->SetTransform(newPos, 0.0f);
}

void Collider::SetVelocity(Vector2D newVelocity)
{
	b2Vec2 newVel;
	newVel.x = newVelocity.X;
	newVel.y = newVelocity.Y;
	body->SetLinearVelocity(newVel);
}

Vector2D Collider::GetPosition()
{
	Vector2D returnPosition;
	b2Vec2 bodyPos;
	bodyPos = body->GetPosition(),

		returnPosition.X = bodyPos.x - colliderHalfWidth;
	returnPosition.Y = bodyPos.y - colliderHalfHeight;

	return returnPosition;
}
