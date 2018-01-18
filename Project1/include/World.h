#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <memory>
#include <vector>

#include "Entity.h"

class Tile;
class Renderer;
class Player;

class World
{
public:
	World(std::shared_ptr<Renderer>, std::shared_ptr<Player>);

	int64_t Width;
	int64_t Height;

	std::vector<std::shared_ptr<Entity>> Tiles;

	void Collisions();
	void Render();
	void LoadWorld(std::string);
private:
	std::shared_ptr<Renderer> renderer;
	std::shared_ptr<Player> player;

	std::string currentWorld;
};

#endif //WORLD_H
