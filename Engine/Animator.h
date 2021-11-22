#pragma once
#include "Component.h"
#include "Transform.h"
#include <string>
#include <vector>


class Animator : public Component
{
public:
	Animator(std::string textureID, std::string filePath, int rowNumber, int columnNumber, int rowEnd, int columnEnd, int rowStart = 1, int colunmStart = 1, int framesPerSeconds = 2, bool horFlip = false, int layer = 0, bool shouldLoop = true, bool playfoward = true, bool playOnStart = true);
	~Animator() 
	{
		delete texture;
	};

	bool Init() override final;
	void Draw() override final;
	void Update() override final;

	void SetProperties(std::string textureID, std::string filePath, int rowNumber, int columnNumber, int rowEnd, int columnEnd, int rowStart = 1, int colunmStart = 1, int framesPerSeconds = 2, bool horFlip = false, int layer = 0, bool shouldLoop = true, bool playfoward = true, bool playOnStart = true);
	void SetupAnimation();
	
	void PlayFromStart(bool loopAnim, bool playFoward = true);
	

	inline int GetLayer()
	{
		return myLayer;
	}

private:

	void PlayFoward(bool goingFoward);

	Transform* transform {nullptr};
	std::string myTextureID{};
	class Texture* texture{ nullptr };
	std::string myFilePath{};
	std::pair<int, int> currentFrame{1,1};
	int frameNumber{};
	int myLayer{};

	int myRowStart{}, myColunmStart{};
	int myRowEnd{}, myColunmEnd{};
	int currentColumn, currentRow;
	int  myColumnNumber{}, myRowNumber{};
	float myFramesPerSeconds{};

	int textureWidth{}, textureHeight{};
	int frameWidth{}, frameHeight{};

	bool flip{ false };
	bool isActive{ true };
	bool loop{true};
	double time{ 0 };
	int frameIndex{ 0 };
	bool foward{ true };

	std::vector<std::pair<int, int>> frames{};
	
};

