#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <unordered_map>
#include <typeindex>
#include <memory>
#include <iostream>

#include "State.h"

#define NOSTATE std::type_index(typeid(void))

class Game;

class StateManager
{
public:
	StateManager() : currentState(NOSTATE) {};

	template <class T>
	void Add(std::shared_ptr<Game> game);

	template <class T>
	void Change();

	void Update(float);
	void Render();

	template <class T>
	bool Is();

private:
	std::type_index currentState;
	std::unordered_map<std::type_index, std::unique_ptr<State>> states;
};

template <class T>
void StateManager::Add(std::shared_ptr<Game> game)
{
	auto index = std::type_index(typeid(T));
	auto state = std::make_unique<T>(game);
	state->Initialize();
	states[index] = std::move(state);
}

template <class T>
void StateManager::Change()
{
	auto index = std::type_index(typeid(T));

	if (states.find(index) == states.end()) { return; }
	if (currentState != NOSTATE) { states[currentState]->Suspend(); }

	currentState = index;
	states[currentState]->Resume();
}

template <class T>
bool StateManager::Is()
{
	auto index = std::type_index(typeid(T));

	return currentState == index;
}

#endif //STATE_MANAGER_H
