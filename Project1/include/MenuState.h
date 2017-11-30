#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "State.h"
#include "Game.h"

class GameState;
class Renderer;

class MenuState : public State
{
public:
	using State::State;

	//~MenuState() {};

	void Initialize()
	{
		renderer = std::make_shared<Renderer>();
	};
	void Destroy() {};

	void Suspend() {};
	void Resume() {};

	void Update(float delta)
	{
		if (game->Key->Escape)
		{
			game->Stop();
		}
		else if (game->Key->Enter)
		{
			game->SetState<GameState>();
		}
	};
	void Render()
	{
		renderer->Clear();
	};

private:
	std::shared_ptr<Renderer> renderer;
};

#endif // MENU_STATE_H
