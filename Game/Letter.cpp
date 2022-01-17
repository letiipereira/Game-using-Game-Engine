#include "Letter.h"
#include "Transform.h"

Letter::Letter(std::string textureID, std::string filePath, int posX, int posY, int rowCurrent, int columnCurrent, int rowTotal, int columnTotal, int layer)
{
    AddComponent<SpriteComponent>(textureID, filePath, 0, layer, true, rowCurrent, columnCurrent, rowTotal, columnTotal);
	GetComponent<Transform>().myPosition.X = posX;
	GetComponent<Transform>().myPosition.Y = posY;
}

Letter::~Letter()
{

}

void Letter::Init()
{
	Entity::Init();
}

void Letter::Update()
{
	Entity::Update();
}
