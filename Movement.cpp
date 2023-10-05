#include "Movement.h"

#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

#include <numbers>

Movement::Movement(glm::dvec2 direction, double speed)
{
	m_direction = direction;
	m_speed = speed;
}

void Movement::Init(GameObject* parent)
{
	m_parent = parent;
}

void Movement::ProcessInput(SDL_Event& event)
{
}

void Movement::Update(glm::dvec2& position, double& rotation)
{
	position += m_direction * m_speed;
}

void Movement::Render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder)
{
	return;
}

void Movement::LateUpdate()
{

}