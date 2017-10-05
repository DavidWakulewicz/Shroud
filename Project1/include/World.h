#ifndef WORLD_H
#define WORLD_H

#include <cstdint>
#include <vector>

#include "Tile.h"

class World
{
public:
	World(SDL_Window*);

	int64_t Width;
	int64_t Height;

	std::vector<Tile> Tiles;
};

#endif //WORLD_H
