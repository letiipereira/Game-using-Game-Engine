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
		if(GetComponent<Transform>().myPosition.Y > 0)
			movement.Y -= 1;
			up = true;
	}
	if ((KeyboardKeystate["Down"] || GamepadButtonstate["Joystick_YAxis_Down"]) && !down)
	{
		if(GetComponent<Transform>().myPosition.Y < GameEngine::GetInstance()->GameWindowHeight() - 64)
			movement.Y += 1;
			down = true;
	}
	if ((KeyboardKeystate["Left"] || GamepadButtonstate["Joystick_XAxis_Left"]) && !left)
	{
		if(GetComponent<Transform>().myPosition.X > 0)
			movement.X -= 1;
			left = true;
	}
	if ((KeyboardKeystate["Right"] || GamepadButtonstate["Joystick_XAxis_Right"]) && !right)
	{
		if(GetComponent<Transform>().myPosition.X < GameEngine::GetInstance()->GameWindowWidht() - 64)
			movement.X += 1;
			right = true;
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
			Bullet* bullet = new Bullet(GetComponent<Transform>().myPosition.X + 24, GetComponent<Transform>().myPosition.Y - 20);
			bulletDeltaTime = 0;
		}
	}
}

void Spaceship::CheckKeyState()
{
	Move();
	Attack();
	//ControllerMove();
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
