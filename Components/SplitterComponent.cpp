#include "SplitterComponent.h"
#include "RenderComponent.h"
#include "MovingComponent.h"
#include "WrapAroundComponent.h"

#include "Engine.h"

SplitterComponent::SplitterComponent(int level)
{
	m_splitLevel = level;
}

void SplitterComponent::Render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder){}

void SplitterComponent::Init(GameObject* parent)
{
	m_parent = parent;
}

void SplitterComponent::ProcessInput(SDL_Event& event){}

void SplitterComponent::Update(glm::dvec2& position, double& rotation){}

void SplitterComponent::LateUpdate()
{
	SplitterComponent::Splitter();
}

void SplitterComponent::Splitter()
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
				new MovingComponent(Engine::RotationToDirection(rotation), speed),
				new SplitterComponent(m_splitLevel - 1),
				new RenderComponent(sprite),
				new WrapAroundComponent()
			}
		);

		asteroid->IsAsteroid = true;

		Engine::GetInstance()->AddGameObject(asteroid);
	}
}