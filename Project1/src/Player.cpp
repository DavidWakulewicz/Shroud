#include "Player.h"

#include <SDL2/SDL_image.h>
#include <iostream>

Player::Player(std::shared_ptr<Keyboard> keyboard)
	: Pos({100, 100}), Scale({1.0f, 1.0f}), Bounds({50, 50}), keyboard(keyboard)
{
}

Player::Player(std::shared_ptr<Keyboard> keyboard, int64_t x, int64_t y)
	: Pos({x, y}), Scale({1.0f, 1.0f}), Bounds({50, 50}), keyboard(keyboard)
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
