#include "StateManager.h"

#include "State.h"

void StateManager::Update()
{
	if (currentState == NOSTATE) { return; }

	states[currentState]->Update();
}

void StateManager::Render()
{
	if (currentState == NOSTATE) { return; }

	states[currentState]->Render();
}
