#include "Engine.h"

#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

#include <chrono>
#include <random>
#include <cmath>

#include "Splitter.h"
#include "SpriteRender.h"
#include "Player.h"
#include "Projectile.h"
#include "WrapAround.h"

Engine* Engine::GetInstance()
{
	static Engine engine;
	return &engine;
}

void Engine::Init(int width, int height, int framRate)
{
	mWindowSize = glm::vec2(800, 1000);
	mTargetFrameTime = 1.0f / framRate;

	mRenderer.setWindowSize(mWindowSize);
	mRenderer.init();
	mCamera.setWindowCoordinates();

	mRenderer.frameUpdate = [this](float delta_time) {
		Update();
	};
	mRenderer.keyEvent = [this](SDL_Event& event) {
		ProcessEvents(event);
	};
	mRenderer.frameRender = [this]() {
		Render();
	};

	std::srand(std::time(nullptr));

	mAtlas = sre::SpriteAtlas::create("data/AsteroidSpriteSheet.json", "data/AsteroidSpriteSheet.png");

	Engine::SpawnPlayer();

	for (int i = 0; i < 5; i++) Engine::SpawnAsteroid();

	mRenderer.startEventLoop();
}

void Engine::ProcessEvents(SDL_Event& event)
{
	for (GameObject* gameObject : mGameObjects) gameObject->ProcessEvent(event);
}

void Engine::Update()
{
	mTimeManager.TimeStart = std::chrono::steady_clock::now();

	mFrameCount++;

	for (int i = 0; i < mGameObjects.size(); i++) mGameObjects[i]->Update();
	
	Engine::Collisions();

	for (int i = 0; i < mGameObjects.size(); i++) mGameObjects[i]->LateUpdate();
	
	Engine::DestroyGameObjects();
}

void Engine::Render()
{
	sre::SpriteBatch::SpriteBatchBuilder spriteBatchBuilder = sre::SpriteBatch::create();

	for (GameObject* gameObject : mGameObjects) gameObject->Render(spriteBatchBuilder);
	

	auto spriteBatch = spriteBatchBuilder.build();

	sre::RenderPass renderPass = sre::RenderPass::create()
		.withCamera(mCamera)
		.withClearColor(true, { .3f, .3f, 1, 1 })
		.build();

	renderPass.draw(spriteBatch);

	Engine::TimeComputation();
}


void Engine::TimeComputation()
{
	mTimeManager.ComputationTime = std::chrono::steady_clock::now() - m_timeManager.TimeStart;

	if (m_timeManager.ComputationTime.count() < mTargetFrameTime)
	{
		std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
		while (std::chrono::steady_clock::now() - start < std::chrono::duration<double>(mTargetFrameTime - (m_timeManager.ComputationTime.count())));
	}

	m_timeManager.TimeEnd = std::chrono::steady_clock::now();
	m_timeManager.TimeElapsed = m_timeManager.TimeEnd - m_timeManager.TimeStart;
}


void Engine::AddGameObject(GameObject* gameObject)
{
	gameObject->ID = mGameObjects.size();
	mGameObjects.push_back(gameObject);
}

glm::vec2 Engine::GetWindowSize()
{
	return mWindowSize;
}

std::shared_ptr<sre::SpriteAtlas> Engine::GetSpriteAtlas()
{
	return mAtlas;
}

void Engine::DestroyGameObjects()
{
	int destroyed = 0; 

	for (int i = 0; i < mGameObjects.size(); i++)
	{
		if (mGameObjects[i]->GetDestroy())
		{
			mGameObjects.erase(mGameObjects.begin() + mGameObjects[i]->ID - destroyed);
			destroyed++;
		}
	}

	int index = 0;
	for (GameObject* gameObject : mGameObjects)
	{
		gameObject->ID = index;
		index++;
	}
}

void Engine::Collisions()
{
	for (int i = 0; i < mGameObjects.size(); i++)
	{
		if (mGameObjects[i]->IsAsteroid)
		{
			for (int j = 0; j < mGameObjects.size(); j++)
			{
				if (!mGameObjects[j]->IsAsteroid)
				{
					glm::dvec2 pos1 = mGameObjects[i]->GetPosition();
					glm::dvec2 pos2 = mGameObjects[j]->GetPosition();
					double distance = pow((pos1.x - pos2.x), 2) + pow((pos1.y - pos2.y), 2);
					double radi = pow(mGameObjects[i]->GetRadius(), 2) + pow(mGameObjects[j]->GetRadius(), 2);

					if (distance < radi)
					{
						mGameObjects[i]->SetDestroy();
						mGameObjects[j]->SetDestroy();
					}
				}
			}
		}
	}
}

void Engine::SpawnPlayer()
{
	sre::Sprite spaceShip;
	spaceShip = mAtlas->get("playerShip2_blue.png");

	GameObject* player = new GameObject(
		glm::dvec2(100.0, 100.0),
		48,
		vector<Component*>{
			new PlayerComponent(),
			new SpriteRender(spaceShip),
			new Projectile(),
			new WrapAround()
		}
	);

	Engine::AddGameObject(player);
}

void Engine::SpawnAsteroid()
{
	sre::Sprite asteroidSprite;

	asteroidSprite = mAtlas->get("Meteors/meteorBrown_big4.png");
	

	double speed = rand() % 100 / 90.0f;
	float rotation = rand() % 360;

	GameObject* asteroid = new GameObject(
		glm::dvec2(rand() % (int)(mWindowSize[0]), rand() % (int)(mWindowSize[1])),
		37,
		vector<Component*>{
			new WrapAround(),
			new SpriteRender(asteroidSprite),
			new Movement(Engine::RotationToDirection(rotation), speed),
			new Splitter(3)
		}
	);
	asteroid->IsAsteroid = true;

	Engine::AddGameObject(asteroid);
}

glm::vec2 Engine::RotationToDirection(float rotation)
{
	if (rotation < 0) rotation = 360 + rotation;
	
	if (rotation > 360)rotation = rotation - 360;

	double radians = rotation * M_PI / 180.0f;

	double x = cos(radians) * 1 - sin(radians) * 0;
	double y = sin(radians) * 1 + cos(radians) * 0;

	return glm::dvec2(x, y);
}