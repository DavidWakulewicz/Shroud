#include "Tile.h"

const uint8_t Tile::WIDTH = 64;
const uint8_t Tile::HEIGHT = 64;

Tile::Tile(std::string texture) :
	Pos({0, 0}),
	Bounds({Tile::WIDTH, Tile::HEIGHT}),
	Texture(texture),
	Solid(false),
	Portal(false)
{
}
