#include "Engine.h"

int main()
{
	Engine* engine = Engine::GetInstance();

	engine->Init(800, 1000, 60);
}