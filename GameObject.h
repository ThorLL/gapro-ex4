#pragma once

#include "Component.h"

#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

class GameObject
{
public:
	bool IsAsteroid = false;
	int ID; 

	GameObject(glm::dvec2 position, float radius, std::vector<Component*> components);
	GameObject(glm::dvec2 position, std::vector<Component*> components);

	void SetDirection(glm::dvec2 direction);

	double GetRadius();
	glm::dvec2 GetPosition();
	GameObject* GetChild(int index);

	bool GetDestroy();
	void SetDestroy();

	
	void SetRotation(float rotation);
	float GetRotation();
	
	void AddComponent(Component* component);
	void AddChildGameObject(GameObject* gameObject);

	void ProcessEvent(SDL_Event& event);
	void Update();
	void Render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder);
	void LateUpdate();

private:
	std::vector<Component*> m_components;
	std::vector<GameObject*> m_children;

	bool m_destroy = false;

	glm::dvec2 m_direction;
	double m_rotation = 0.0f;
	glm::dvec2 m_position;
	double m_radius = 1;
};