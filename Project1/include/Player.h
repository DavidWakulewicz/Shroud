#ifndef PLAYER_H
#define PLAYER_H

#include <ostream>
#include <memory>

#include "Point.h"
#include "Keyboard.h"

class Player
{
public:
	Player(std::shared_ptr<Keyboard>);
	Player(std::shared_ptr<Keyboard>, int64_t, int64_t);

	Point<int64_t> Pos;
	Point<int64_t> Size;
	Point<float>   Scale;
	Point<int64_t> Bounds;

	int64_t Health;
	float   Speed;

	void Update();
private:
	std::shared_ptr<Keyboard> keyboard;

	void updatePosition();
};

#endif // PLAYER_H
