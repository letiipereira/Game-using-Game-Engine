#include "GameObject.h"

void GameObject::Start()
{
	//render object in the given position
}

void GameObject::Update()
{
	
}

std::vector<float> GameObject::GetPosition()
{
	return position;
}

std::vector<float> GameObject::GetRotation()
{
	return rotation;
}

std::vector<float> GameObject::GetScale()
{
	return scale;
}

void GameObject::ChangePosition(float posX, float posY)
{
	position.at(0) = posX;
	position.at(1) = posY;

	//should change on screen 
}

std::string GameObject::GetName()
{
	return name;
}
