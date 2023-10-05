#pragma once

#include "GameObject.h"
#include "Component.h"

#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"


class PlayerComponent : public Component
{
public:
	void Init(GameObject* parent);
	void ProcessInput(SDL_Event& event);
	void Update(glm::dvec2& position, double& rotation);
	void LateUpdate();
	void Render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder);

private:

	bool m_up, m_right, m_left, m_down; // input

	glm::dvec2 m_direction = glm::dvec2(1.0, 0.0);
	double m_speed = 0.0;
	float m_rotationSpeed = 5;

	glm::dvec2 m_position;
};