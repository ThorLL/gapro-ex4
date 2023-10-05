#include "SpriteRender.h"

#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

#include "Engine.h"

SpriteRender::SpriteRender(sre::Sprite sprite)
{
	m_sprite = sprite;
}

void SpriteRender::Render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder)
{	
	spriteBatchBuilder.addSprite(m_sprite);
}

void SpriteRender::Init(GameObject* parent)
{
	m_parent = parent;
}

void SpriteRender::ProcessInput(SDL_Event& event){}

void SpriteRender::Update(glm::dvec2& position, double& rotation)
{
	m_sprite.setPosition(position);
	m_sprite.setRotation(rotation - 90.0);
	return;
}

void SpriteRender::LateUpdate(){}