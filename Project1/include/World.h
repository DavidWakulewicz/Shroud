#ifndef WORLD_H
#define WORLD_H

#include <cstdint>
#include <vector>

#include "Tile.h"
#include "Renderer.h"

class World
{
public:
	World(std::shared_ptr<Renderer>);

	int64_t Width;
	int64_t Height;

	std::vector<Tile> Tiles;
	void Render();
private:
	std::shared_ptr<Renderer> renderer;
};

#endif //WORLD_H
