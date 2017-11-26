#ifndef STATE_H
#define STATE_H

#include <memory>
#include <iostream>

class Game;

class State
{
public:
	State(std::shared_ptr<Game> game) : game(game) {};

	//virtual ~State() = 0;

	virtual void Initialize() = 0;
	virtual void Destroy() = 0;

	virtual void Suspend() = 0;
	virtual void Resume() = 0;

	virtual void Update(float) = 0;
	virtual void Render() = 0;

protected:
	std::shared_ptr<Game> game;
};

//inline State::~State() {}

#endif //STATE_H
