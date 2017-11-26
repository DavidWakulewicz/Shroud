#include "StateManager.h"

#include "State.h"

void StateManager::Update(float delta)
{
	if (currentState == NOSTATE) { return; }

	states[currentState]->Update(delta);
}

void StateManager::Render()
{
	if (currentState == NOSTATE) { return; }

	states[currentState]->Render();
}
