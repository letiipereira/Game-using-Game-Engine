#include "Loner.h"

Loner::Loner()
{
	AddComponent<Animator>();
	idleLoner = new Animation("idleLoner", "assets/LonerA.bmp", 4, 4, 4, 4, 1, 1, 2, false, 2, true, true, true);
	GetComponent<Animator>().AddAnimation("idle",idleLoner);
	std::cout << "loner construtor\n";
	health = 10;
}

Loner::~Loner()
{
}

void Loner::Init()
{
	Enemy::Init();
	std::cout << "loner init\n";
	GetComponent<Transform>().myPosition.X = 200;
	GetComponent<Transform>().myPosition.Y = 200;
}

//void Loner::Update()
//{
//	Enemy::Update();
//}

