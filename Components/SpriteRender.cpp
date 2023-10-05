#include "SpriteRender.h"

#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

#include "Engine.h"

RenderComponent::RenderComponent(sre::Sprite sprite)
{
	m_sprite = sprite;
}

void RenderComponent::Render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder)
{	
	spriteBatchBuilder.addSprite(m_sprite);
}

void RenderComponent::Init(GameObject* parent)
{
	m_parent = parent;
}

void RenderComponent::ProcessInput(SDL_Event& event){}

void RenderComponent::Update(glm::dvec2& position, double& rotation)
{
	m_sprite.setPosition(position);
	m_sprite.setRotation(rotation - 90.0);
	return;
}

void RenderComponent::LateUpdate(){}