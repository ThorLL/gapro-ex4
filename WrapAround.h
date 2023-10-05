#pragma once

#include "Component.h"
#include "Engine.h"
#include "GameObject.h"

class WrapAroundComponent : public Component
{
public:
	void Init(GameObject* parent);
	void Render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder);
	void ProcessInput(SDL_Event& event);
	void Update(glm::dvec2& position, double& rotation);
	void LateUpdate();

protected:
	Borders m_borders;
};