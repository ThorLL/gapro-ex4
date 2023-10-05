#pragma once

#include "sre/SDLRenderer.hpp"

class GameObject;

class Component
{
protected:
	GameObject* m_parent;

public:
	virtual void Init(GameObject* parent) = 0;
	virtual void ProcessInput(SDL_Event& event) = 0;
	virtual void Update(glm::dvec2& position, double& rotation) = 0;
	virtual void LateUpdate() = 0;
	virtual void Render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder) = 0;
};