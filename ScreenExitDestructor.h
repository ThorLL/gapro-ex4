#pragma once

#include "Component.h"
#include "GameObject.h"

struct Borders
{
	float Min_x;
	float Min_y;
	float Max_x;
	float Max_y;
};

class ScreenExitDestructor : public Component
{
protected:
	Borders m_destructionBorder;

public:
	ScreenExitDestructor();
	void Init(GameObject* parent);
	void LateUpdate();
	void Render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder);
	void ProcessInput(SDL_Event& event);
	void Update(glm::dvec2& position, double& rotation);
};