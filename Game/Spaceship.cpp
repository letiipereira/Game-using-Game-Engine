#include "Spaceship.h"
#include "Bullet.h"
#include "Spawner.h"
#include "GameInput.h"
#include "UIManager.h"

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

	moveDown = new Animation("moveUp", "assets/Ship1.bmp", 1, 7, 1, 7, 1, 5, 14, false, 6, false, true, false);
	moveUp = new Animation("moveDown", "assets/Ship1.bmp", 1, 7, 1, 3, 1, 1, 14, false, 6, false, false, false);
	idle = new Animation("idle", "assets/Ship1.bmp", 1, 7, 1, 4, 1, 4, 7, false, 6, false, false, true);

	GetComponent<Animator>().AddAnimation("moveUp", moveUp);
	GetComponent<Animator>().AddAnimation("moveDown", moveDown);
	GetComponent<Animator>().AddAnimation("idle", idle);

	companionPos1 = std::pair<Vector2D, Companion*>((-51.0f, 80.0f), nullptr);
	companionPos2 = std::pair<Vector2D, Companion*>((50.0f, -81.0f), nullptr);

	maxCompanions = 2;

	gameInput = GameInput::GetInstance();
	UIManager::GetInstance()->SetMaxLifes(currentLifes);

	KeyboardKeystate = gameInput->GetKeyState();
	GamepadButtonstate = gameInput->GetButtonState();
}

void Spaceship::Init()
{
	Pawn::Init();

	GetComponent<Animator>().PlayFromStart("idle", false, false);

	GetComponent<Transform>().myRotation = -90.0f;

	colliderHeight = static_cast<float>(GetComponent<Animator>().GetAnimationByName("idle")->frameHeight);
	colliderWidth = static_cast<float>(GetComponent<Animator>().GetAnimationByName("idle")->frameWidth);

	AddComponent<Collider>().AddAttributes("Spaceship", this, Collider::BodyType::dynamicBody,
									       GetComponent<Transform>().myPosition.X,
									       GetComponent<Transform>().myPosition.Y,
											colliderWidth, colliderHeight, true, 0.0f);
}

void Spaceship::Update()
{
	//std::cout << health << std::endl;

	Pawn::Update();

	time += GameEngine::GetInstance()->GetDeltatime();
	bulletDeltaTime += GameEngine::GetInstance()->GetDeltatime();

	if (time >= GameEngine::GetInstance()->GetDeltatime())
	{
		spaceshipXDir = GetComponent<Transform>().myPosition.Y - lastPosY;
		time = 0;
	}
	lastPosY = GetComponent<Transform>().myPosition.Y;

	//ShipAnimation();
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
		if (GetComponent<Transform>().myPosition.Y <= GameEngine::GetInstance()->GameWindowHeight() - 32)
		{
			movement.Y += 1;
			up = true;
		}	
	}

	if ((KeyboardKeystate["Down"] || GamepadButtonstate["Joystick_YAxis_Down"]) && !down)
	{
		if (GetComponent<Transform>().myPosition.Y >=  32)
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

		if (companionPos1.second != nullptr)
			companionPos1.second->Attack();

		if (companionPos2.second != nullptr)
			companionPos2.second->Attack();
	}
}

void Spaceship::CheckKeyState()
{
	Move();
	Attack();
}

void Spaceship::IncreaseCompanionCount()
{
	++currentCompanions;

	std::cout << " companion count " << currentCompanions << std::endl;
	std::cout << " companion max " << maxCompanions << std::endl;
	std::cout << std::endl;
}

void Spaceship::DecreaseCompanionCount()
{
	--currentCompanions;

	std::cout << " companion count " << currentCompanions << std::endl;
	std::cout << " companion max " << maxCompanions << std::endl;
	std::cout << std::endl;
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
			++bulletLevel;
		}
	}
	else if (!willIncrease)
	{
		if (bulletLevel != bulletMinLevel)
		{
			--bulletLevel;
		}
	}
}

void Spaceship::RemoveCompanion(float posX, float posY, Companion* companion)
{
	if (companion != nullptr)
	{
		if (companionPos1.second == companion)
		{
			DecreaseCompanionCount();
			companionPos1.second->GetSpawner()->CompanionNecessity(true);
			companionPos1.second->Destroy();
			companionPos1.second = nullptr;
		}
		else if (companionPos2.second == companion)
		{
			DecreaseCompanionCount();
			companionPos2.second->GetSpawner()->CompanionNecessity(true);
			companionPos2.second->Destroy();
			companionPos2.second = nullptr;
		}
	}
}

void Spaceship::WasHit(Entity* collidedObject)
{
	if (collidedObject->GetComponent<Collider>().GetId() == "Companion")
	{
		Companion* collidedCompanion = static_cast<Companion*>(collidedObject);

		
		if (!HasMaxCompanions() && !collidedCompanion->IsTaken())
		{
			if (companionPos1.second == nullptr)
			{
				companionPos1.second = collidedCompanion;
				collidedCompanion->SetDisplacement(companionPos1.first);
				
				
			}
			else if (companionPos2.second == nullptr)
			{
				companionPos2.second = collidedCompanion;
				collidedCompanion->SetDisplacement(companionPos2.first);
				
			}

			if (companionPos1.second != nullptr)
			{
				collidedCompanion->SetPlayerReference(this);
				collidedCompanion->TakeCompanion(true);
				IncreaseCompanionCount();
				if (HasMaxCompanions())
				{
					collidedCompanion->GetSpawner()->CompanionNecessity(false);
				}

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

	UIManager::GetInstance()->UpdateHealth(maxHealth, health);
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
			UIManager::GetInstance()->UpdateLifes(currentLifes);
		}
		else
		{
			// quit
		}		
	}

	UIManager::GetInstance()->UpdateHealth(maxHealth, health);
}
