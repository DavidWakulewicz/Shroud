#include "Tile.h"
#include "Entity.h"

const uint8_t Tile::WIDTH = 64;
const uint8_t Tile::HEIGHT = 64;

Tile::Tile(std::string texture) :
	Entity(texture),
	Solid(false),
	Portal(false)
{
	this->Bounds.x = Tile::WIDTH;
	this->Bounds.y = Tile::HEIGHT;
}
