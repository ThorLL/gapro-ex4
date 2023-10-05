#include <iostream>
#include <chrono>
#include <random>

#include "GameObject.h"
#include "Component.h"
#include "Component.h"
#include "Movement.h"
#include "Splitter.h"

GameObject::GameObject(glm::dvec2 position, float radius, std::vector<Component*> components){
	mPosition = position;
	mRadius = radius;
	mComponents = components;
	for (Component* component : mComponents) component->Init(this);
}

GameObject::GameObject(glm::dvec2 position, std::vector<Component*> components) {
	mPosition = position;
	mComponents = components;
	for (Component* component : mComponents) component->Init(this);
}

void GameObject::AddComponent(Component* component)
{
	mComponents.push_back(component);
}


void GameObject::Render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder)
{
	for (Component* component : mComponents)
		component->Render(spriteBatchBuilder);

	for (GameObject* gameObject : mChildren)
		gameObject->Render(spriteBatchBuilder);
}

glm::dvec2 GameObject::GetPosition()
{
	return mPosition;
}

void GameObject::Update()
{
	for (Component* component : mComponents)
		component->Update(mPosition, mRotation);
	
}

void GameObject::ProcessEvent(SDL_Event& event)
{
	for (Component* component : mComponents)
		component->ProcessInput(event);
	
}

void GameObject::AddChildGameObject(GameObject* gameObject)
{
	mChildren.push_back(gameObject);
}

GameObject* GameObject::GetChild(int index)
{
	if (index >= mChildren.size()) return nullptr;
	return mChildren[index];
}

void GameObject::SetDirection(glm::dvec2 direction)
{
	mDirection = direction;
}

bool GameObject::GetDestroy()
{
	return mDestroy;
}

void GameObject::SetDestroy()
{
	mDestroy = true;
}

void GameObject::LateUpdate()
{
	for (Component* component : mComponents)
		component->LateUpdate();
}

double GameObject::GetRadius()
{
	return mRadius;
}

void GameObject::SetRotation(float rotation)
{
	mRotation = rotation;
}

float GameObject::GetRotation()
{
	return mRotation;
}