#include "Projectile.h"

#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

#include "GameObject.h"

#include "Engine.h"

Projectile::Projectile(){}

void Projectile::Render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder){}

void Projectile::Init(GameObject* parent){
	m_parent = parent;
}

void Projectile::LateUpdate(){}

void Projectile::ProcessInput(SDL_Event& event)
{
	m_shoot = event.key.keysym.sym == SDLK_SPACE && event.type == SDL_KEYDOWN;
}

void Projectile::Update(glm::dvec2& position, double& rotation)
{
	m_position = position;
	m_rotation = rotation;

	Projectile::Shoot();
}

void Projectile::Shoot()
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
			new SpriteRender(Engine::GetInstance()->GetSpriteAtlas()->get("Lasers/laserGreen04.png")),
			new Movement(Engine::RotationToDirection(m_rotation), 8),
			
		}
	);

	destructorComponent->Init(laser);

	laser->AddComponent(destructorComponent);

	laser->SetRotation(m_parent->GetRotation());
	laser->SetDirection(m_direction);

	Engine::GetInstance()->AddGameObject(laser);
}