#pragma once

#include "Component.h"
#include "GameObject.h"
#include <chrono>

class SplitterComponent : public Component
{
public:
	SplitterComponent(int level);
	void Init(GameObject* parent);
	void LateUpdate();
	void Render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder);
	void ProcessInput(SDL_Event& event);
	void Update(glm::dvec2& position, double& rotation);
	void Splitter(); // LateUpdate

protected:
	int m_splitLevel = 3;
};