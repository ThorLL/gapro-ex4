#include "Movement.h"

#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

#include <numbers>

MovingComponent::MovingComponent(glm::dvec2 direction, double speed)
{
	m_direction = direction;
	m_speed = speed;
}

void MovingComponent::Init(GameObject* parent)
{
	m_parent = parent;
}

void MovingComponent::ProcessInput(SDL_Event& event)
{
}

void MovingComponent::Update(glm::dvec2& position, double& rotation)
{
	position += m_direction * m_speed;
}

void MovingComponent::Render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder)
{
	return;
}

void MovingComponent::LateUpdate()
{

}