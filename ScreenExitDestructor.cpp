#include "ScreenExitDestructor.h"

#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

#include "GameObject.h"

#include "Engine.h"

ScreenExitDestructor::ScreenExitDestructor()
{
	return;
}

void ScreenExitDestructor::Render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder)
{
}

void ScreenExitDestructor::Init(GameObject* parent)
{
	m_parent = parent;

	glm::vec2 windowSize = Engine::GetInstance()->GetWindowSize();

	float bufferPercentage = 20.0f / 100.0f;

	m_destructionBorder.Min_x = -windowSize[0] * bufferPercentage;
	m_destructionBorder.Max_x = windowSize[0] + (windowSize[0] * bufferPercentage);

	m_destructionBorder.Min_y = -windowSize[1] * bufferPercentage;
	m_destructionBorder.Max_y = windowSize[1] + (windowSize[1] * bufferPercentage);
}

void ScreenExitDestructor::ProcessInput(SDL_Event& event)
{
	return;
}

void ScreenExitDestructor::Update(glm::dvec2& position, double& rotation)
{
  if (m_destructionBorder.Max_x < position[0] || m_destructionBorder.Min_x > position[0]) m_parent->SetDestroy();

  if (m_destructionBorder.Max_y < position[1] || m_destructionBorder.Min_y > position[1]) m_parent->SetDestroy();
}

void ScreenExitDestructor::LateUpdate()
{

}
