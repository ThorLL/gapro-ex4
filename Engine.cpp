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

void Engine::Init(int width, int height)
{
	m_windowSize = glm::vec2(800, 1000);

	m_renderer.setWindowSize(m_windowSize);
	m_renderer.init();
	m_camera.setWindowCoordinates();

	m_renderer.frameUpdate = [this](float delta_time) {
		Update();
	};
	m_renderer.keyEvent = [this](SDL_Event& event) {
		ProcessEvents(event);
	};
	m_renderer.frameRender = [this]() {
		Render();
	};

	std::srand(std::time(nullptr));

	m_atlas = sre::SpriteAtlas::create("data/AsteroidSpriteSheet.json", "data/AsteroidSpriteSheet.png");

	Engine::SpawnPlayer();

	for (int i = 0; i < m_asteroidAmount; i++) Engine::SpawnAsteroid();

	m_renderer.startEventLoop();
}

void Engine::ProcessEvents(SDL_Event& event)
{
	for (GameObject* gameObject : m_gameObjects) gameObject->ProcessEvent(event);
}

void Engine::Update()
{
	m_timeManager.TimeStart = std::chrono::steady_clock::now();

	m_frameCount++;

	for (int i = 0; i < m_gameObjects.size(); i++) m_gameObjects[i]->Update();
	
	Engine::Collisions();

	for (int i = 0; i < m_gameObjects.size(); i++) m_gameObjects[i]->LateUpdate();
	
	Engine::DestroyGameObjects();
}

void Engine::Render()
{
	sre::SpriteBatch::SpriteBatchBuilder spriteBatchBuilder = sre::SpriteBatch::create();

	for (GameObject* gameObject : m_gameObjects) gameObject->Render(spriteBatchBuilder);
	

	auto spriteBatch = spriteBatchBuilder.build();

	sre::RenderPass renderPass = sre::RenderPass::create()
		.withCamera(m_camera)
		.withClearColor(true, { .3f, .3f, 1, 1 })
		.build();

	renderPass.draw(spriteBatch);

	Engine::TimeComputation();
}


void Engine::TimeComputation()
{
	m_timeManager.ComputationTime = std::chrono::steady_clock::now() - m_timeManager.TimeStart;

	if (m_timeManager.ComputationTime.count() < m_targetFrameTime)
	{
		std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
		while (std::chrono::steady_clock::now() - start < std::chrono::duration<double>(m_targetFrameTime - (m_timeManager.ComputationTime.count())));
	}

	m_timeManager.TimeEnd = std::chrono::steady_clock::now();
	m_timeManager.TimeElapsed = m_timeManager.TimeEnd - m_timeManager.TimeStart;
}


void Engine::AddGameObject(GameObject* gameObject)
{
	gameObject->ID = m_gameObjects.size();
	m_gameObjects.push_back(gameObject);
}

glm::vec2 Engine::GetWindowSize()
{
	return m_windowSize;
}

std::shared_ptr<sre::SpriteAtlas> Engine::GetSpriteAtlas()
{
	return m_atlas;
}

void Engine::DestroyGameObjects()
{
	int destroyed = 0; 

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		if (m_gameObjects[i]->GetDestroy())
		{
			m_gameObjects.erase(m_gameObjects.begin() + m_gameObjects[i]->ID - destroyed);
			destroyed++;
		}
	}

	int index = 0;
	for (GameObject* gameObject : m_gameObjects)
	{
		gameObject->ID = index;
		index++;
	}
}

void Engine::Collisions()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		if (m_gameObjects[i]->IsAsteroid)
		{
			for (int j = 0; j < m_gameObjects.size(); j++)
			{
				if (!m_gameObjects[j]->IsAsteroid)
				{
					glm::dvec2 pos1 = m_gameObjects[i]->GetPosition();
					glm::dvec2 pos2 = m_gameObjects[j]->GetPosition();
					double distance = pow((pos1.x - pos2.x), 2) + pow((pos1.y - pos2.y), 2);
					double radi = pow(m_gameObjects[i]->GetRadius(), 2) + pow(m_gameObjects[j]->GetRadius(), 2);

					if (distance < radi)
					{
						m_gameObjects[i]->SetDestroy();
						m_gameObjects[j]->SetDestroy();
					}
				}
			}
		}
	}
}

void Engine::SpawnPlayer()
{
	sre::Sprite spaceShip;
	spaceShip = m_atlas->get("playerShip2_blue.png");

	GameObject* player = new GameObject(
		glm::dvec2(100.0, 100.0),
		48,
		vector<Component*>{
			new PlayerComponent(),
			new RenderComponent(spaceShip),
			new ShootingComponent(),
			new WrapAroundComponent()
		}
	);

	Engine::AddGameObject(player);
}

void Engine::SpawnAsteroid()
{
	sre::Sprite asteroidSprite;

	asteroidSprite = m_atlas->get("Meteors/meteorBrown_big4.png");
	

	double speed = rand() % 100 / 90.0f;
	float rotation = rand() % 360;

	GameObject* asteroid = new GameObject(
		glm::dvec2(rand() % (int)(m_windowSize[0]), rand() % (int)(m_windowSize[1])),
		37,
		vector<Component*>{
			new WrapAroundComponent(),
			new RenderComponent(asteroidSprite),
			new MovingComponent(Engine::RotationToDirection(rotation), speed),
			new SplitterComponent(3)
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