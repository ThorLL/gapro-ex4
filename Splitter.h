#pragma once

#include "Component.h"
#include "GameObject.h"
#include <chrono>

class Splitter : public Component
{
public:
	Splitter(int level);
	void Init(GameObject* parent);
	void LateUpdate();
	void Render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder);
	void ProcessInput(SDL_Event& event);
	void Update(glm::dvec2& position, double& rotation);

protected:
	int m_splitLevel = 3;
};