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

	void Init(int,int);

	glm::vec2 GetWindowSize();
	std::shared_ptr<sre::SpriteAtlas> GetSpriteAtlas();

	void AddGameObject(GameObject* gameObject);
	
	static glm::vec2 RotationToDirection(float rotation);

	void SpawnAsteroid();

private:

	static Engine* m_instance;

	Engine() {};
	~Engine() {};

	sre::SDLRenderer m_renderer;
	std::shared_ptr<sre::SpriteAtlas> m_atlas;
	sre::Camera m_camera;

	int m_frameCount = 0;

	int m_IDcounter = 0;
	std::vector<int> m_toBeDestroyed;

	glm::vec2 m_windowSize;
	int m_fieldSize;
	int m_asteroidAmount = 5;

	std::vector<GameObject*> m_gameObjects;

	const double m_targetFrameTime = 1/60;

	TimeManager m_timeManager;

	void TimeComputation();
	void ProcessEvents(SDL_Event& event);
	void Update();
	void Render();
	void DestroyGameObjects();
	void SpawnPlayer();
	void Collisions();
};