#ifndef PLAYER_H
#define PLAYER_H

#include <ostream>
#include <memory>

#include "Keyboard.h"
#include "Entity.h"

class Player: public Entity
{
public:
	Player(std::string texture, std::shared_ptr<Keyboard>);
	Player(std::string texture, std::shared_ptr<Keyboard>, int64_t, int64_t);


	void Update();
private:
	std::shared_ptr<Keyboard> keyboard;

	void updatePosition();
};

#endif // PLAYER_H
