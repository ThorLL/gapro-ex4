#include "WrapAround.h"

void WrapAroundComponent::Init(GameObject* parent)
{
	m_parent = parent;

	glm::vec2 windowSize = Engine::GetInstance()->GetWindowSize();

	m_borders.Min_x = 0;
	m_borders.Max_x = windowSize[0];

	m_borders.Min_y = 0;
	m_borders.Max_y = windowSize[1];
}

void WrapAroundComponent::Render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder){}

void LateUpdate(){}

void WrapAroundComponent::ProcessInput(SDL_Event& event){}

void WrapAroundComponent::Update(glm::dvec2& position, double& rotation)
{
	if (m_borders.Max_x < position[0])
		position[0] = m_borders.Min_x;
	else if (m_borders.Min_x > position[0])
		position[0] = m_borders.Max_x;

	if (m_borders.Max_y < position[1])
		position[1] = m_borders.Min_x;
	else if (m_borders.Min_y > position[1])
		position[1] = m_borders.Max_x;
}

void WrapAroundComponent::LateUpdate(){}