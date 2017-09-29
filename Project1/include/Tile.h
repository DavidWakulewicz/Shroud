#ifndef TILE_H
#define TILE_H

#include <string>
#include <memory>

#include <SDL2/SDL.h>

#include "Camera.h"

class Tile
{
public:
	const static uint8_t WIDTH;
	const static uint8_t HEIGHT;

	Tile(std::string);

	Point<uint64_t> Pos;
	Point<uint16_t> Bounds;

	std::string Texture;
private:
};
#endif // TILE_H
