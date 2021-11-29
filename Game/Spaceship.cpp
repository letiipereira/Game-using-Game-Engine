#include "Spaceship.h"
#include "Bullet.h"
#include "GameInput.h"

Spaceship::Spaceship()
{
	health = 100;
	AddComponent<Animator>();

	moveRight = new Animation("moveRight", "assets/Ship1.bmp", 1, 7, 1, 7, 1, 5, 14, false, 6, false, true, false);
	moveLeft = new Animation("moveLeft", "assets/Ship1.bmp", 1, 7, 1, 3, 1, 1, 14, false, 6, false, false, false);
	idle = new Animation("idle", "assets/Ship1.bmp", 1, 7, 1, 4, 1, 4, 7, false, 6, false, false, true);

	GetComponent<Animator>().AddAnimation("moveRight", moveRight);
	GetComponent<Animator>().AddAnimation("moveLeft", moveLeft);
	GetComponent<Animator>().AddAnimation("idle", idle);

	KeyboardKeystate = GameInput::GetInstance()->GetKeyState();
	GamepadButtonstate = GameInput::GetInstance()->GetButtonState();
}

void Spaceship::Init()
{
	Pawn::Init();
	
	GetComponent<Animator>().PlayFromStart("idle", false, false);

	GetComponent<Transform>().myPosition.X = 300;
	GetComponent<Transform>().myPosition.Y = 350;

	AddComponent<Collider>().AddAttributes("Spaceship", this, Collider::BodyType::dynamicBody,
									       GetComponent<Transform>().myPosition.X,
									       GetComponent<Transform>().myPosition.Y,
										   GetComponent<Animator>().GetAnimationByName("idle")->frameWidth,
										   GetComponent<Animator>().GetAnimationByName("idle")->frameHeight, true, 0.0f);
}



void Spaceship::OnKeyDown(std::string key)
{
	std::map<std::string, bool>::iterator it;

	for (it = KeyboardKeystate.begin(); it != KeyboardKeystate.end(); it++)
	{
		if (it->first == key)
		{
			if (it->second != true)
			{
				it->second = true;

				break;
			}
		}
	}
}

void Spaceship::OnKeyUp(std::string key)
{
	std::map<std::string, bool>::iterator it;

	for (it = KeyboardKeystate.begin(); it != KeyboardKeystate.end(); it++)
	{
		if (it->first == key)
		{
			if (it->second != false)
			{
				it->second = false;

				break;
			}
		}
	}
}

void Spaceship::OnButtonDown(std::string button)
{
	std::map<std::string, bool>::iterator it;

	for (it = GamepadButtonstate.begin(); it != GamepadButtonstate.end(); it++)
	{
		if (it->first == button)
		{
			if (it->second != true)
			{
				it->second = true;

				break;
			}
		}
	}
}

void Spaceship::OnButtonUp(std::string button)
{
	std::map<std::string, bool>::iterator it;

	for (it = GamepadButtonstate.begin(); it != GamepadButtonstate.end(); it++)
	{
		if (it->first == button)
		{
			if (it->second != false)
			{
				it->second = false;

				break;
			}
		}
	}
}

void Spaceship::Move()
{
	if (KeyboardKeystate["Up"] == true && KeyboardKeystate["Left"] == true)
	{
		if (GetComponent<Transform>().myPosition.X > 0 && GetComponent<Transform>().myPosition.Y > 0)
		{
			GetComponent<Collider>().SetVelocity(moveSpeed * uniform);

			GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X -= (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform), GetComponent<Transform>().myPosition.Y -= (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform));

			GetComponent<Transform>().myPosition = GetComponent<Collider>().GetPosition();

			if (GetComponent<Animator>().GetCurrentAnimation() != GetComponent<Animator>().GetAnimationByName("moveLeft"))
			{
				GetComponent<Animator>().PlayFromStart("moveLeft", false, false);
			}
		}
	}
	else if (KeyboardKeystate["Up"] == true && KeyboardKeystate["Right"] == true)
	{
		if (GetComponent<Transform>().myPosition.X < (GameEngine::GetInstance()->GameWindowWidht() - 64) && GetComponent<Transform>().myPosition.Y > 0)
		{
			GetComponent<Collider>().SetVelocity(moveSpeed * uniform);

			GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X += (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform), GetComponent<Transform>().myPosition.Y -= (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform));

			GetComponent<Transform>().myPosition = GetComponent<Collider>().GetPosition();

			if (GetComponent<Animator>().GetCurrentAnimation() != GetComponent<Animator>().GetAnimationByName("moveRight"))
			{
				GetComponent<Animator>().PlayFromStart("moveRight", false, true);
			}
		}
	}
	else if (KeyboardKeystate["Down"] == true && KeyboardKeystate["Left"] == true)
	{
		if (GetComponent<Transform>().myPosition.X > 0 && GetComponent<Transform>().myPosition.Y < (GameEngine::GetInstance()->GameWindowHeight() - 64))
		{
			GetComponent<Collider>().SetVelocity(moveSpeed * uniform);

			GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X -= (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform), GetComponent<Transform>().myPosition.Y += (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform));

			GetComponent<Transform>().myPosition = GetComponent<Collider>().GetPosition();

			if (GetComponent<Animator>().GetCurrentAnimation() != GetComponent<Animator>().GetAnimationByName("moveLeft"))
			{
				GetComponent<Animator>().PlayFromStart("moveLeft", false, false);
			}
		}
	}
	else if (KeyboardKeystate["Down"] == true && KeyboardKeystate["Right"] == true)
	{
		if (GetComponent<Transform>().myPosition.X < (GameEngine::GetInstance()->GameWindowWidht() - 64) && GetComponent<Transform>().myPosition.Y < (GameEngine::GetInstance()->GameWindowHeight() - 64))
		{
			if (GetComponent<Transform>().myPosition.X < (GameEngine::GetInstance()->GameWindowWidht() - 64) && GetComponent<Transform>().myPosition.Y > 0)
			{
				GetComponent<Collider>().SetVelocity(moveSpeed * uniform);

				GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X += (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform), GetComponent<Transform>().myPosition.Y += (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform));

				GetComponent<Transform>().myPosition = GetComponent<Collider>().GetPosition();

				if (GetComponent<Animator>().GetCurrentAnimation() != GetComponent<Animator>().GetAnimationByName("moveRight"))
				{
					GetComponent<Animator>().PlayFromStart("moveRight", false, true);
				}
			}
		}
	}
	
	if (KeyboardKeystate["Left"] == true && KeyboardKeystate["Up"] == false && KeyboardKeystate["Down"] == false)
	{
		if (GetComponent<Transform>().myPosition.X > 0)
		{
			GetComponent<Collider>().SetVelocity(moveSpeed * uniform);

			GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X -= (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform), GetComponent<Transform>().myPosition.Y);

			GetComponent<Transform>().myPosition.X = GetComponent<Collider>().GetPosition().X;

			if (GetComponent<Animator>().GetCurrentAnimation() != GetComponent<Animator>().GetAnimationByName("moveLeft"))
			{
				GetComponent<Animator>().PlayFromStart("moveLeft", false, false);
			}
		}
	}
	
	if (KeyboardKeystate["Right"] == true && KeyboardKeystate["Up"] == false && KeyboardKeystate["Down"] == false)
	{
		if (GetComponent<Transform>().myPosition.X < (GameEngine::GetInstance()->GameWindowWidht() - 64))
		{
			GetComponent<Collider>().SetVelocity(moveSpeed * uniform);

			GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X += (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform), GetComponent<Transform>().myPosition.Y);

			GetComponent<Transform>().myPosition.X = GetComponent<Collider>().GetPosition().X;

			if (GetComponent<Animator>().GetCurrentAnimation() != GetComponent<Animator>().GetAnimationByName("moveRight"))
			{
				GetComponent<Animator>().PlayFromStart("moveRight", false, true);
			}
		}
	}
	
	if (KeyboardKeystate["Up"] == true && KeyboardKeystate["Left"] == false && KeyboardKeystate["Right"] == false)
	{
		if (GetComponent<Transform>().myPosition.Y > 0)
		{
			GetComponent<Collider>().SetVelocity(moveSpeed * uniform);

			GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X, GetComponent<Transform>().myPosition.Y -= (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform));

			GetComponent<Transform>().myPosition.Y = GetComponent<Collider>().GetPosition().Y;
		}
	}

	if (KeyboardKeystate["Down"] == true && KeyboardKeystate["Left"] == false && KeyboardKeystate["Right"] == false)
	{
		if (GetComponent<Transform>().myPosition.Y < (GameEngine::GetInstance()->GameWindowHeight() - 64))
		{
			GetComponent<Collider>().SetVelocity(moveSpeed * uniform);

			GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X, GetComponent<Transform>().myPosition.Y += (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform));

			GetComponent<Transform>().myPosition.Y = GetComponent<Collider>().GetPosition().Y;
		}
	}
}

void Spaceship::ControllerMove()
{
	if (GamepadButtonstate["Joystick_YAxis_Up"] == true && GamepadButtonstate["Joystick_XAxis_Left"] == true)
	{
		if (GetComponent<Transform>().myPosition.X > 0 && GetComponent<Transform>().myPosition.Y > 0)
		{
			GetComponent<Collider>().SetVelocity(moveSpeed * uniform);

			GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X -= (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform), GetComponent<Transform>().myPosition.Y -= (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform));

			GetComponent<Transform>().myPosition = GetComponent<Collider>().GetPosition();

			if (GetComponent<Animator>().GetCurrentAnimation() != GetComponent<Animator>().GetAnimationByName("moveLeft"))
			{
				GetComponent<Animator>().PlayFromStart("moveLeft", false, false);
			}
		}
	}
	else if (GamepadButtonstate["Joystick_YAxis_Up"] == true && GamepadButtonstate["Joystick_XAxis_Right"] == true)
	{
		if (GetComponent<Transform>().myPosition.X < (GameEngine::GetInstance()->GameWindowWidht() - 64) && GetComponent<Transform>().myPosition.Y > 0)
		{
			GetComponent<Collider>().SetVelocity(moveSpeed * uniform);

			GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X += (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform), GetComponent<Transform>().myPosition.Y -= (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform));

			GetComponent<Transform>().myPosition = GetComponent<Collider>().GetPosition();

			if (GetComponent<Animator>().GetCurrentAnimation() != GetComponent<Animator>().GetAnimationByName("moveRight"))
			{
				GetComponent<Animator>().PlayFromStart("moveRight", false, true);
			}
		}
	}
	else if (GamepadButtonstate["Joystick_YAxis_Down"] == true && GamepadButtonstate["Joystick_XAxis_Left"] == true)
	{
		if (GetComponent<Transform>().myPosition.X > 0 && GetComponent<Transform>().myPosition.Y < (GameEngine::GetInstance()->GameWindowHeight() - 64))
		{
			GetComponent<Collider>().SetVelocity(moveSpeed * uniform);

			GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X -= (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform), GetComponent<Transform>().myPosition.Y += (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform));

			GetComponent<Transform>().myPosition = GetComponent<Collider>().GetPosition();

			if (GetComponent<Animator>().GetCurrentAnimation() != GetComponent<Animator>().GetAnimationByName("moveLeft"))
			{
				GetComponent<Animator>().PlayFromStart("moveLeft", false, false);
			}
		}
	}
	else if (GamepadButtonstate["Joystick_YAxis_Down"] == true && GamepadButtonstate["Joystick_XAxis_Right"] == true)
	{
		if (GetComponent<Transform>().myPosition.X < (GameEngine::GetInstance()->GameWindowWidht() - 64) && GetComponent<Transform>().myPosition.Y < (GameEngine::GetInstance()->GameWindowHeight() - 64))
		{
			if (GetComponent<Transform>().myPosition.X < (GameEngine::GetInstance()->GameWindowWidht() - 64) && GetComponent<Transform>().myPosition.Y > 0)
			{
				GetComponent<Collider>().SetVelocity(moveSpeed * uniform);

				GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X += (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform), GetComponent<Transform>().myPosition.Y += (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform));

				GetComponent<Transform>().myPosition = GetComponent<Collider>().GetPosition();

				if (GetComponent<Animator>().GetCurrentAnimation() != GetComponent<Animator>().GetAnimationByName("moveRight"))
				{
					GetComponent<Animator>().PlayFromStart("moveRight", false, true);
				}
			}
		}
	}
	
	if (GamepadButtonstate["Joystick_XAxis_Left"] == true && GamepadButtonstate["Joystick_YAxis_Up"] == false && GamepadButtonstate["Joystick_YAxis_Down"] == false)
	{
		if (GetComponent<Transform>().myPosition.X > 0)
		{
			GetComponent<Collider>().SetVelocity(moveSpeed * uniform);

			GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X -= (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform), GetComponent<Transform>().myPosition.Y);

			GetComponent<Transform>().myPosition.X = GetComponent<Collider>().GetPosition().X;

			if (GetComponent<Animator>().GetCurrentAnimation() != GetComponent<Animator>().GetAnimationByName("moveLeft"))
			{
				GetComponent<Animator>().PlayFromStart("moveLeft", false, false);
			}
		}
	}
	
	if (GamepadButtonstate["Joystick_XAxis_Right"] == true && GamepadButtonstate["Joystick_YAxis_Up"] == false && GamepadButtonstate["Joystick_YAxis_Down"] == false)
	{
		if (GetComponent<Transform>().myPosition.X < (GameEngine::GetInstance()->GameWindowWidht() - 64))
		{
			GetComponent<Collider>().SetVelocity(moveSpeed * uniform);

			GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X += (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform), GetComponent<Transform>().myPosition.Y);

			GetComponent<Transform>().myPosition.X = GetComponent<Collider>().GetPosition().X;

			if (GetComponent<Animator>().GetCurrentAnimation() != GetComponent<Animator>().GetAnimationByName("moveRight"))
			{
				GetComponent<Animator>().PlayFromStart("moveRight", false, true);
			}
		}
	}
	
	if (GamepadButtonstate["Joystick_YAxis_Up"] == true && GamepadButtonstate["Joystick_XAxis_Left"] == false && GamepadButtonstate["Joystick_XAxis_Right"] == false)
	{
		if (GetComponent<Transform>().myPosition.Y > 0)
		{
			GetComponent<Collider>().SetVelocity(moveSpeed * uniform);

			GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X, GetComponent<Transform>().myPosition.Y -= (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform));

			GetComponent<Transform>().myPosition.Y = GetComponent<Collider>().GetPosition().Y;
		}
	}
	
	if (GamepadButtonstate["Joystick_YAxis_Down"] == true && GamepadButtonstate["Joystick_XAxis_Left"] == false && GamepadButtonstate["Joystick_XAxis_Right"] == false)
	{
		if (GetComponent<Transform>().myPosition.Y < (GameEngine::GetInstance()->GameWindowHeight() - 64))
		{
			GetComponent<Collider>().SetVelocity(moveSpeed * uniform);

			GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X, GetComponent<Transform>().myPosition.Y += (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform));

			GetComponent<Transform>().myPosition.Y = GetComponent<Collider>().GetPosition().Y;
		}
	}
}

void Spaceship::Attack()
{
	if (KeyboardKeystate["Space"] == true || GamepadButtonstate["SDL_CONTROLLER_BUTTON_A"] == true)
	{
		if (bulletDeltaTime > bulletCoolDown)
		{
			Bullet* bullet = new Bullet(GetComponent<Transform>().myPosition.X + 24, GetComponent<Transform>().myPosition.Y - 20);
			bulletDeltaTime = 0;
		}
	}
}

void Spaceship::CheckKeyState()
{
	Move();
	Attack();
	ControllerMove();
}

void Spaceship::Update()
{
	Pawn::Update();

	time += GameEngine::GetInstance()->GetDeltatime();
	bulletDeltaTime += GameEngine::GetInstance()->GetDeltatime();           

	if (time >= GameEngine::GetInstance()->GetDeltatime())
	{
		spaceshipXDir = GetComponent<Transform>().myPosition.X - lastPosX;
		time = 0;
	}
	lastPosX = GetComponent<Transform>().myPosition.X;
	
	ShipAnimation();
}

void Spaceship::ShipAnimation()
{
	if (spaceshipXDir > 0 && animDir != 1)
	{
		if ((GetComponent<Animator>().GetCurrentAnimation() == GetComponent<Animator>().GetAnimationByName("moveLeft")))
		{
			GetComponent<Animator>().PlayFromStart("moveLeft", false, true);
			GetComponent<Animator>().ClearAnimationQueu();
			GetComponent<Animator>().AddToAnimationQueue("moveRight", false, true);
		}
		else if (GetComponent<Animator>().GetCurrentAnimation() == GetComponent<Animator>().GetAnimationByName("idle"))
		{
			GetComponent<Animator>().PlayFromStart("moveRight", false, true);
		}
		animDir = 1;
	}
	else if (spaceshipXDir < 0 && animDir != -1)
	{
		if (GetComponent<Animator>().GetCurrentAnimation() == GetComponent<Animator>().GetAnimationByName("moveRight"))
		{
			GetComponent<Animator>().PlayFromStart("moveRight", false, false);
			GetComponent<Animator>().ClearAnimationQueu();
			GetComponent<Animator>().AddToAnimationQueue("moveLeft", false, false);
		}
		else if (GetComponent<Animator>().GetCurrentAnimation() == GetComponent<Animator>().GetAnimationByName("idle"))
		{
			GetComponent<Animator>().PlayFromStart("moveLeft", false, false);
		}

		animDir = -1;
	}
	else if (spaceshipXDir == 0 && animDir != 0)
	{
		if (GetComponent<Animator>().GetCurrentAnimation() == GetComponent<Animator>().GetAnimationByName("moveLeft"))
		{
			if (GetComponent<Animator>().GetCurrentAnimation()->foward == false)
			{

				GetComponent<Animator>().PlayFromStart("moveLeft", false, true);
				GetComponent<Animator>().ClearAnimationQueu();
				GetComponent<Animator>().AddToAnimationQueue("idle", true, true);
			}
			else
			{
				GetComponent<Animator>().PlayFromStart("idle", false, true);
			}
		}
		else if (GetComponent<Animator>().GetCurrentAnimation() == GetComponent<Animator>().GetAnimationByName("moveRight"))
		{
			if (GetComponent<Animator>().GetCurrentAnimation()->foward == true)
			{
				GetComponent<Animator>().PlayFromStart("moveRight", false, false);
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
