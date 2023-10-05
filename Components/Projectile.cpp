#include "Projectile.h"

#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

#include "GameObject.h"

#include "Engine.h"

ShootingComponent::ShootingComponent(){}

void ShootingComponent::Render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder)
{
}

void ShootingComponent::Init(GameObject* parent)
{
	m_parent = parent;

	glm::vec2 windowSize = Engine::GetInstance()->GetWindowSize();

	float bufferPercentage = 20.0f / 100.0f;

	m_destructionBorder.Min_x = -windowSize[0] * bufferPercentage;
	m_destructionBorder.Max_x = windowSize[0] + (windowSize[0] * bufferPercentage);

	m_destructionBorder.Min_y = -windowSize[1] * bufferPercentage;
	m_destructionBorder.Max_y = windowSize[1] + (windowSize[1] * bufferPercentage);
}

void ShootingComponent::LateUpdate(){}

void ShootingComponent::ProcessInput(SDL_Event& event)
{
	m_shoot = event.key.keysym.sym == SDLK_SPACE && event.type == SDL_KEYDOWN;
}

void ShootingComponent::Update(glm::dvec2& position, double& rotation)
{
	m_position = position;
	m_rotation = rotation;

	ShootingComponent::Shoot();

	if (m_destructionBorder.Max_x < position[0] || m_destructionBorder.Min_x > position[0]) m_parent->SetDestroy();

	if (m_destructionBorder.Max_y < position[1] || m_destructionBorder.Min_y > position[1]) m_parent->SetDestroy();
}

void ShootingComponent::Shoot()
{
	if (!m_shoot) return;
	

	std::chrono::duration<double> timeSinceLastShot = std::chrono::steady_clock::now() - m_lastShot;

	if (timeSinceLastShot.count() < m_refracturePeriod) return;

	m_lastShot = std::chrono::steady_clock::now();

	m_shoot = false;
	
	ScreenExitDestructor* destructorComponent = new ScreenExitDestructor();
	

	GameObject* laser = new GameObject(
		m_position,
		6,
		vector<Component*>{
			new RenderComponent(Engine::GetInstance()->GetSpriteAtlas()->get("Lasers/laserGreen04.png")),
			new MovingComponent(Engine::RotationToDirection(m_rotation), 8),
			
		}
	);

	destructorComponent->Init(laser);

	laser->AddComponent(destructorComponent);

	laser->SetRotation(m_parent->GetRotation());
	laser->SetDirection(m_direction);

	Engine::GetInstance()->AddGameObject(laser);
}