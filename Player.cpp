#include "Player.h"
#include "GameObject.h"
#include "SpriteRender.h"

#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

#include "Engine.h"

#include <numbers>

void PlayerComponent::Init(GameObject* parent)
{
	m_parent = parent;

	m_up = false;
	m_right = false;
	m_left = false;
	return;
}

void PlayerComponent::ProcessInput(SDL_Event& event)
{
	m_left = false;
	m_right = false;

	if (event.key.keysym.sym == SDLK_w)
	{
		m_up = event.type == SDL_KEYDOWN;
	}

	m_right = event.key.keysym.sym == SDLK_a && event.type == SDL_KEYDOWN;
	m_left = event.key.keysym.sym == SDLK_d && event.type == SDL_KEYDOWN;

}

void PlayerComponent::Update(glm::dvec2& position, double& rotation)
{
	m_speed -= 0.05;

	if (m_up) m_speed = max(int(floor(++m_speed)), 3);

	m_speed = max(int(floor(m_speed)), 0);


	if (m_right)rotation += m_rotationSpeed;
	else if (m_left) rotation -= m_rotationSpeed;

	m_direction = Engine::RotationToDirection(rotation);

	position += m_direction * m_speed;
	m_position = position;
}

void PlayerComponent::Render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder)
{
	return;
}

void PlayerComponent::LateUpdate()
{
	if (!m_parent->GetDestroy()) return;
	
	GameObject* bang = new GameObject(
		m_parent->GetPosition(),
		vector<Component*>{
			new SpriteRender(Engine::GetInstance()->GetSpriteAtlas()->get("bang.png"))
		}
	);

	Engine::GetInstance()->AddGameObject(bang);
}