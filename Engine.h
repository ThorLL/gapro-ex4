#pragma once

#include <chrono>

#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

#include "GameObject.h"

using namespace std;

struct TimeManager
{
	std::chrono::time_point<std::chrono::steady_clock>	TimeStart;
	std::chrono::time_point<std::chrono::steady_clock>	TimeEnd;
	std::chrono::duration<double>						TimeElapsed;
	std::chrono::duration<double>						ComputationTime;
};

class Engine
{
public:
	Engine(const Engine&) = delete;
	Engine operator=(const Engine) = delete;

	static Engine* GetInstance();

	void Init(int, int, int);

	glm::vec2 GetWindowSize();
	std::shared_ptr<sre::SpriteAtlas> GetSpriteAtlas();

	void AddGameObject(GameObject* gameObject);
	
	static glm::vec2 RotationToDirection(float rotation);

	void SpawnAsteroid();

private:

	static Engine* mInstance;

	Engine() {};
	~Engine() {};

	sre::SDLRenderer mRenderer;
	std::shared_ptr<sre::SpriteAtlas> mAtlas;
	sre::Camera mCamera;

	int mFrameCount = 0;
	int mIDcounter = 0;

	std::vector<int> mToBeDestroyed;

	glm::vec2 mWindowSize;

	std::vector<GameObject*> mGameObjects;

	float mTargetFrameTime;

	TimeManager mTimeManager;

	void TimeComputation();
	void ProcessEvents(SDL_Event& event);
	void Update();
	void Render();
	void DestroyGameObjects();
	void SpawnPlayer();
	void Collisions();
};