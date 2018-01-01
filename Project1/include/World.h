#ifndef WORLD_H
#define WORLD_H

#include <cstdint>
#include <string>
#include <vector>

class Tile;
class Renderer;
class Player;

class World
{
public:
	World(std::shared_ptr<Renderer>, std::shared_ptr<Player>);

	int64_t Width;
	int64_t Height;

	std::vector<Tile> Tiles;

	void Collisions();
	void Render();
	void LoadWorld(std::string);
private:
	std::shared_ptr<Renderer> renderer;
	std::shared_ptr<Player> player;

	std::string currentWorld;
};

#endif //WORLD_H
