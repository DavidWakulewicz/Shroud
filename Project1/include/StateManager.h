#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <unordered_map>
#include <typeindex>
#include <memory>
#include <iostream>

#include "State.h"

#define NOSTATE std::type_index(typeid(void))

class StateManager
{
public:
	StateManager() : currentState(NOSTATE) {};

	template <class T>
	void Add();

	template <class T>
	void Change();

	void Update();
	void Render();

	template <class T>
	bool Is();

private:
	std::type_index currentState;
	std::unordered_map<std::type_index, std::unique_ptr<State>> states;
};

template <class T>
void StateManager::Add()
{
	auto index = std::type_index(typeid(T));
	auto state = std::make_unique<T>();
	states[index] = std::move(state);
}

template <class T>
void StateManager::Change()
{
	auto index = std::type_index(typeid(T));

	if (states.find(index) == states.end()) { return; }
	if (currentState != NOSTATE) { states[currentState]->Destroy(); }

	currentState = index;
	states[currentState]->Initialize();
}

template <class T>
bool StateManager::Is()
{
	auto index = std::type_index(typeid(T));

	return currentState == index;
}

#endif //STATE_MANAGER_H


/*
 * game.AddState(new MenuState)
 * game.AddState(new GameState)
 *
 * game.ChangeState(State::Game)
 *
 *
 */
