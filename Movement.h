#pragma once

#include "Component.h"
#include "GameObject.h"

#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"


class Movement : public Component
{
public:
	Movement(glm::dvec2 direction, double speed);
	void Init(GameObject* parent);
	void ProcessInput(SDL_Event& event);
	void Update(glm::dvec2& position, double& rotation);
	void LateUpdate();
	void Render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder);

private:
	glm::dvec2 m_direction = glm::dvec2(1.0, 0.0);
	double m_speed = 0.0;
	float m_rotationSpeed = 1;
	void Move(glm::dvec2& position, double& rotation);
};