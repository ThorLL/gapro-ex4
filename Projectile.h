#pragma once

#include "Player.h"
#include "SpriteRender.h"
#include "GameObject.h"
#include "Movement.h"

#include "ScreenExitDestructor.h"
#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

#include "Component.h"
#include "GameObject.h"
#include <chrono>

class ShootingComponent : public Component
{
public:
	ShootingComponent();
	void LateUpdate();
	void Init(GameObject* parent);
	void Render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder);
	void ProcessInput(SDL_Event& event);
	void Update(glm::dvec2& position, double& rotation);

protected:
	const double m_refracturePeriod = 0.2;
	std::chrono::time_point<std::chrono::steady_clock> m_lastShot;

	bool m_shoot = false;
	glm::dvec2 m_position;
	glm::dvec2 m_direction = glm::dvec2(1.0, 0.0);
	float m_rotation = 0;
	
	void Shoot();
};