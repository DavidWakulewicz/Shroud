#include "Player.h"

#include <SDL2/SDL_image.h>
#include <iostream>

Player::Player(std::string texture, std::shared_ptr<Keyboard> keyboard)
	: Entity(texture, 100, 100), keyboard(keyboard)
{
}

Player::Player(std::string texture, std::shared_ptr<Keyboard> keyboard, int64_t x, int64_t y)
	: Entity(texture, x, y), keyboard(keyboard)
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
