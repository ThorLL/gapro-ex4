#include "Splitter.h"
#include "SpriteRender.h"
#include "Movement.h"
#include "WrapAround.h"

#include "Engine.h"

Splitter::Splitter(int level)
{
	m_splitLevel = level;
}

void Splitter::Render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder){}

void Splitter::Init(GameObject* parent)
{
	m_parent = parent;
}

void Splitter::ProcessInput(SDL_Event& event){}

void Splitter::Update(glm::dvec2& position, double& rotation){}

void Splitter::LateUpdate()
{
	if (!m_parent->GetDestroy() || m_splitLevel == 1) return;

	for (int i = 0; i < 2; i++)
	{
		double speed = rand() % 100 / 90.0f;
		float rotation = rand() % 360;

		sre::Sprite sprite;
		double radius;

		if (m_splitLevel == 3)
		{
			sprite = Engine::GetInstance()->GetSpriteAtlas()->get("Meteors/meteorBrown_med1.png");
			radius = 21;
		}
		else if (m_splitLevel == 2)
		{
			radius = 13;
			sprite = Engine::GetInstance()->GetSpriteAtlas()->get("Meteors/meteorBrown_small2.png");
		}

		GameObject* asteroid = new GameObject(
			m_parent->GetPosition(),
			radius,
			vector<Component*>{
			new Movement(Engine::RotationToDirection(rotation), speed),
				new Splitter(m_splitLevel - 1),
				new SpriteRender(sprite),
				new WrapAround()
		}
		);

		asteroid->IsAsteroid = true;

		Engine::GetInstance()->AddGameObject(asteroid);
	}
}
