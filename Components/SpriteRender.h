#pragma once

#include "Component.h"
#include "GameObject.h"

#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

class RenderComponent : public Component
{
public:
	RenderComponent(sre::Sprite sprite);
	void Init(GameObject* parent);
	void Render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder);
	void ProcessInput(SDL_Event& event);
	void Update(glm::dvec2& position, double& rotation);
	void LateUpdate();

protected:
	char m_character;
	const float m_rotSpeed = 50;
	glm::dvec2 m_position;
	sre::Sprite m_sprite;
};