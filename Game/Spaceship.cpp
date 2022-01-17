#include "Spaceship.h"
#include "Bullet.h"
#include "Spawner.h"
#include "GameInput.h"

Spaceship::Spaceship()
{
	maxLifes = 2;
	currentLifes = maxLifes;
	maxHealth = 100;
	health = maxHealth;
	currentCompanions = 0;
	bulletLevel = 1;
	bulletMinLevel = 1;
	bulletMaxLevel = 3;
	AddComponent<Animator>();
	GetComponent<Transform>().myRotation = -90.0f;

	moveDown = new Animation("moveUp", "assets/Ship1.bmp", 1, 7, 1, 7, 1, 5, 14, false, 6, false, true, false);
	moveUp = new Animation("moveDown", "assets/Ship1.bmp", 1, 7, 1, 3, 1, 1, 14, false, 6, false, false, false);
	idle = new Animation("idle", "assets/Ship1.bmp", 1, 7, 1, 4, 1, 4, 7, false, 6, false, false, true);

	GetComponent<Animator>().AddAnimation("moveUp", moveUp);
	GetComponent<Animator>().AddAnimation("moveDown", moveDown);
	GetComponent<Animator>().AddAnimation("idle", idle);

	companionList.insert({ {10.0f, 70.0f} , nullptr });
	companionList.insert({ {11.0f, -70.0f} , nullptr });

	maxCompanions = companionList.size();

	KeyboardKeystate = GameInput::GetInstance()->GetKeyState();
	GamepadButtonstate = GameInput::GetInstance()->GetButtonState();
}

void Spaceship::Init()
{
	Pawn::Init();

	GetComponent<Animator>().PlayFromStart("idle", false, false);

	GetComponent<Transform>().myPosition.X = 50;
	GetComponent<Transform>().myPosition.Y = 220;

	AddComponent<Collider>().AddAttributes("Spaceship", this, Collider::BodyType::dynamicBody,
									       GetComponent<Transform>().myPosition.X,
									       GetComponent<Transform>().myPosition.Y,
										   GetComponent<Animator>().GetAnimationByName("idle")->frameWidth,
										   GetComponent<Animator>().GetAnimationByName("idle")->frameHeight, true, 0.0f);
}

void Spaceship::Update()
{
	Pawn::Update();

	time += GameEngine::GetInstance()->GetDeltatime();
	bulletDeltaTime += GameEngine::GetInstance()->GetDeltatime();

	if (time >= GameEngine::GetInstance()->GetDeltatime())
	{
		spaceshipXDir = GetComponent<Transform>().myPosition.Y - lastPosY;
		time = 0;
	}
	lastPosY = GetComponent<Transform>().myPosition.Y;

	ShipAnimation();
}

void Spaceship::OnKeyDown(std::string key)
{
	if (KeyboardKeystate[key] != true)
		KeyboardKeystate[key] = true;
}

void Spaceship::OnKeyUp(std::string key)
{
	if (KeyboardKeystate[key] != false)
		KeyboardKeystate[key] = false;
}

void Spaceship::OnButtonDown(std::string button)
{
	if (GamepadButtonstate[button] != true)
		GamepadButtonstate[button] = true;
}

void Spaceship::OnButtonUp(std::string button)
{
	if (GamepadButtonstate[button] != false)
		GamepadButtonstate[button] = false;
}

void Spaceship::Move()
{
	Vector2D movement{};

	//std::cout << movement.X << " " << movement.Y << std::endl;

	bool up{ false };
	bool down{ false };
	bool left{ false };
	bool right{ false };

	if ((KeyboardKeystate["Up"] || GamepadButtonstate["Joystick_YAxis_Up"]) && !up )
	{
		if (GetComponent<Transform>().myPosition.Y < GameEngine::GetInstance()->GameWindowHeight() - 32)
		{
			movement.Y += 1;
			up = true;
		}	
	}

	if ((KeyboardKeystate["Down"] || GamepadButtonstate["Joystick_YAxis_Down"]) && !down)
	{
		if (GetComponent<Transform>().myPosition.Y > 32)
		{
			movement.Y -= 1;
			down = true;
		}
	}

	if ((KeyboardKeystate["Left"] || GamepadButtonstate["Joystick_XAxis_Left"]) && !left)
	{
		if (GetComponent<Transform>().myPosition.X > 32)
		{
			movement.X -= 1;
			left = true;
		}
	}

	if ((KeyboardKeystate["Right"] || GamepadButtonstate["Joystick_XAxis_Right"]) && !right)
	{
		if (GetComponent<Transform>().myPosition.X < GameEngine::GetInstance()->GameWindowWidht() - 32)
		{
			movement.X += 1;
			right = true;
		}
	}

	movement.NormalizeVector();
	//std::cout << movement.X << " " << movement.Y << std::endl;

	if (HasComponent<Collider>())
	{
		GetComponent<Collider>().SetVelocity(moveSpeed);
		GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X + movement.X * moveSpeed * GameEngine::GetInstance()->GetDeltatime(),
			GetComponent<Transform>().myPosition.Y + movement.Y * moveSpeed * GameEngine::GetInstance()->GetDeltatime());

		GetComponent<Transform>().myPosition = GetComponent<Collider>().GetPosition();
	}
}

void Spaceship::Attack()
{
	if (KeyboardKeystate["Space"] == true || GamepadButtonstate["SDL_CONTROLLER_BUTTON_A"] == true)
	{
		if (bulletDeltaTime > bulletCoolDown)
		{
			Bullet* bullet = new Bullet(GetComponent<Transform>().myPosition.X + 55, GetComponent<Transform>().myPosition.Y, bulletLevel);
			bulletDeltaTime = 0;
		}

		std::map<Vector2D, Companion*, Vector2DCompare>::iterator it;

		for (it = companionList.begin(); it != companionList.end(); it++)
		{
			if (it->second != nullptr && it->second->IsActive())
			{
				it->second->Attack();
			}
		}
	}
}

void Spaceship::CheckKeyState()
{
	Move();
	Attack();
}

void Spaceship::IncreaseCompanionCount()
{
	currentCompanions++;
}

void Spaceship::DecreaseCompanionCount()
{
	currentCompanions--;
}

bool Spaceship::HasMaxCompanions()
{
	return currentCompanions >= maxCompanions;
}

void Spaceship::ShipAnimation()
{
	if (spaceshipXDir > 0 && animDir != 1)
	{
		if ((GetComponent<Animator>().GetCurrentAnimation() == GetComponent<Animator>().GetAnimationByName("moveLeft")))
		{
			GetComponent<Animator>().PlayFromStart("moveUp", false, true);
			GetComponent<Animator>().ClearAnimationQueu();
			GetComponent<Animator>().AddToAnimationQueue("moveDown", false, true);
		}
		else if (GetComponent<Animator>().GetCurrentAnimation() == GetComponent<Animator>().GetAnimationByName("idle"))
		{
			GetComponent<Animator>().PlayFromStart("moveDown", false, true);
		}
		animDir = 1;
	}
	else if (spaceshipXDir < 0 && animDir != -1)
	{
		if (GetComponent<Animator>().GetCurrentAnimation() == GetComponent<Animator>().GetAnimationByName("moveDown"))
		{
			GetComponent<Animator>().PlayFromStart("moveDown", false, false);
			GetComponent<Animator>().ClearAnimationQueu();
			GetComponent<Animator>().AddToAnimationQueue("moveUp", false, false);
		}
		else if (GetComponent<Animator>().GetCurrentAnimation() == GetComponent<Animator>().GetAnimationByName("idle"))
		{
			GetComponent<Animator>().PlayFromStart("moveUp", false, false);
		}

		animDir = -1;
	}
	else if (spaceshipXDir == 0 && animDir != 0)
	{
		if (GetComponent<Animator>().GetCurrentAnimation() == GetComponent<Animator>().GetAnimationByName("moveUp"))
		{
			if (GetComponent<Animator>().GetCurrentAnimation()->foward == false)
			{
				GetComponent<Animator>().PlayFromStart("moveUp", false, true);
				GetComponent<Animator>().ClearAnimationQueu();
				GetComponent<Animator>().AddToAnimationQueue("idle", true, true);
			}
			else
			{
				GetComponent<Animator>().PlayFromStart("idle", false, true);
			}
		}
		else if (GetComponent<Animator>().GetCurrentAnimation() == GetComponent<Animator>().GetAnimationByName("moveDown"))
		{
			if (GetComponent<Animator>().GetCurrentAnimation()->foward == true)
			{
				GetComponent<Animator>().PlayFromStart("moveDown", false, false);
				GetComponent<Animator>().ClearAnimationQueu();
				GetComponent<Animator>().AddToAnimationQueue("idle", true, true);
			}
			else
			{
				GetComponent<Animator>().PlayFromStart("idle", false, true);
			}
		}
		animDir = 0;
	}
}

void Spaceship::ChangeBulletLevel(bool willIncrease)
{
	if (willIncrease)
	{
		if (bulletLevel != bulletMaxLevel)
		{
			bulletLevel++;
		}
	}
	else if (!willIncrease)
	{
		if (bulletLevel != bulletMinLevel)
		{
			bulletLevel--;
		}
	}
}

void Spaceship::RemoveCompanion(Companion* companion)
{
	std::map<Vector2D, Companion*, Vector2DCompare>::iterator itr;

	for (itr = companionList.begin(); itr != companionList.end(); itr++)
	{
		if (itr->second == companion)
		{
			DecreaseCompanionCount();
			itr->second->GetSpawner()->CompanionNecessity(true);
			itr->second->Destroy();
			itr->second = nullptr;
			
			break;
		}
	}
}

void Spaceship::WasHit(Entity* collidedObject)
{
	if (collidedObject->GetComponent<Collider>().GetId() == "Companion")
	{
		Companion* collidedCompanion = static_cast<Companion*>(collidedObject);

		std::map<Vector2D, Companion*, Vector2DCompare>::iterator itr;

		for (itr = companionList.begin(); itr != companionList.end(); itr++)
		{
			if (itr->second == nullptr && !HasMaxCompanions())
			{
				itr->second = collidedCompanion;
				collidedCompanion->SetDisplacement(itr->first);
				collidedCompanion->SetPlayerReference(this);
				collidedCompanion->TakeCompanion(true);

				IncreaseCompanionCount();

				if (HasMaxCompanions())
				{
					collidedCompanion->GetSpawner()->CompanionNecessity(false);
				}

				break;
			}
		}
	}
}

void Spaceship::ApplyShield(int shieldValue)
{
	health += shieldValue;

	if (health > maxHealth)
	{
		health = maxHealth;
	}
}

void Spaceship::ApplyDamage(int damageReceived)
{
	health -= damageReceived;

	if (health <= 0)
	{
		if (currentLifes != 0)
		{
			currentLifes--;
			health = maxHealth;
		}
		else
		{
			// quit
		}		
	}
}
