#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <memory>
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

<<<<<<< 90ebe828a0772823e519abcddb363b5473a2dd6e
	std::vector<Tile> Tiles;

	void Collisions();
=======
	std::vector<std::shared_ptr<Entity>> Tiles;
>>>>>>> Tiles and player inherit from Entity class
	void Render();
	void LoadWorld(std::string);
private:
	std::shared_ptr<Renderer> renderer;
	std::shared_ptr<Player> player;

	std::string currentWorld;
};

#endif //WORLD_H
