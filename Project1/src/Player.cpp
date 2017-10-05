#include "Player.h"

#include <SDL2/SDL_image.h>

Player::Player(std::shared_ptr<Keyboard> keyboard)
	: Pos({0, 0}), Scale({1.0f, 1.0f}), Bounds({640, 480}), keyboard(keyboard)
{
}

Player::Player(std::shared_ptr<Keyboard> keyboard, int64_t x, int64_t y)
	: Pos({x, y}), Scale({1.0f, 1.0f}), Bounds({640, 480}), keyboard(keyboard)
{
}

void Player::Update()
{
	updatePosition();
}

void Player::updatePosition() {
	if (keyboard->Up)    Pos.y -= 10;
	if (keyboard->Down)  Pos.y += 10; 
	if (keyboard->Left)  Pos.x -= 10; 
	if (keyboard->Right) Pos.x += 10;
}
