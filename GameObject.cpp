#include <iostream>
#include <chrono>
#include <random>

#include "GameObject.h"
#include "Component.h"
#include "PlayerComponent.h"
#include "MovingComponent.h"
#include "SplitterComponent.h"

GameObject::GameObject(glm::dvec2 position, float radius, std::vector<Component*> components){
	m_position = position;
	m_radius = radius;
	m_components = components;
	for (Component* component : m_components) component->Init(this);
}

GameObject::GameObject(glm::dvec2 position, std::vector<Component*> components) {
	m_position = position;
	m_components = components;
	for (Component* component : m_components) component->Init(this);
}

void GameObject::AddComponent(Component* component)
{
	m_components.push_back(component);
}


void GameObject::Render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder)
{
	for (Component* component : m_components)
		component->Render(spriteBatchBuilder);

	for (GameObject* gameObject : m_children)
		gameObject->Render(spriteBatchBuilder);
}

glm::dvec2 GameObject::GetPosition()
{
	return m_position;
}

void GameObject::Update()
{
	for (Component* component : m_components)
		component->Update(m_position, m_rotation);
	
}

void GameObject::ProcessEvent(SDL_Event& event)
{
	for (Component* component : m_components)
		component->ProcessInput(event);
	
}

void GameObject::AddChildGameObject(GameObject* gameObject)
{
	m_children.push_back(gameObject);
}

GameObject* GameObject::GetChild(int index)
{
	if (index >= m_children.size()) return nullptr;
	return m_children[index];
}

void GameObject::SetDirection(glm::dvec2 direction)
{
	m_direction = direction;
}

bool GameObject::GetDestroy()
{
	return m_destroy;
}

void GameObject::SetDestroy()
{
	m_destroy = true;
}

void GameObject::LateUpdate()
{
	for (Component* component : m_components)
		component->LateUpdate();
}

double GameObject::GetRadius()
{
	return m_radius;
}

void GameObject::SetRotation(float rotation)
{
	m_rotation = rotation;
}

float GameObject::GetRotation()
{
	return m_rotation;
}