#include "World.h"

#include <iostream>
#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Tile.h"
#include "Renderer.h"
#include "Player.h"

World::World(std::shared_ptr<Renderer> renderer, std::shared_ptr<Player> player) : renderer(renderer),  player(player)
{
	LoadWorld("world");
}

void World::LoadWorld(std::string world)
{
	uint32_t format = renderer->GetWindowFormat();
	SDL_PixelFormat* mappingFormat = SDL_AllocFormat(format);

	uint32_t wall = SDL_MapRGB(mappingFormat, 0x00, 0x00, 0x00);
	uint32_t floor = SDL_MapRGB(mappingFormat, 0x00, 0xA9, 0xFF);
	uint32_t steps = SDL_MapRGB(mappingFormat, 0x00, 0x6E, 0xA5);
	uint32_t portal = SDL_MapRGB(mappingFormat, 0xFF, 0x00, 0xFF);

	std::string path = "res/levels/" + world + ".png";

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image " << path
			<< "! SDL_image Error: " << IMG_GetError() << std::endl;

		return;
	}

	SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, format, static_cast<uint32_t>(NULL));
	if (formattedSurface == NULL)
	{
		std::cout << "Unable to convert loaded surface to display format! SDL Error: " << SDL_GetError() << std::endl;
		return;
	}

	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);

	Width = formattedSurface->w;
	Height = formattedSurface->h;

	Tiles.clear();

	for (int x = 0; x < Width; x++) {
		for (int y = 0; y < Height; y++) {
			int i = (x % Width) + (y * Height);

			std::string path;
			bool isSolid = false;
			bool isPortal = false;
			if (static_cast<uint32_t*>(formattedSurface->pixels)[i] == wall)
			{
				path = "res/tiles/SpawnTileWall.png";
				isSolid = true;
			}
			else if (static_cast<uint32_t*>(formattedSurface->pixels)[i] == floor)
			{
				path = "res/tiles/SpawnTile.png";
			}
			else if (static_cast<uint32_t*>(formattedSurface->pixels)[i] == steps)
			{
				path = "res/tiles/FootStepNorth.png";
			}
			else if (static_cast<uint32_t*>(formattedSurface->pixels)[i] == portal)
			{
				path = "res/tiles/FootStepNorth.png";
				isPortal = true;
			}

			std::shared_ptr<Tile> tile = std::make_shared<Tile>(path);
			tile->Pos.x = x * Tile::WIDTH;
			tile->Pos.y = y * Tile::HEIGHT;
			tile->Solid = isSolid;
			tile->Portal = isPortal;
			Tiles.push_back(tile);
		}
	}

	currentWorld = world;

	SDL_FreeSurface(formattedSurface);
}

void World::Collisions() {
	for (std::vector<std::shared_ptr<Entity>>::iterator it = Tiles.begin(); it != Tiles.end(); ++it)
	{
    		//Tile tile = dynamic_cast<Tile>(*it);
		std::shared_ptr<Tile> tile = std::dynamic_pointer_cast<Tile>(*it);

		// Don't check tiles that are not solid
		if (!tile->Solid && !tile->Portal)
		{
			continue;
		}

		// Get how much overlap there is on the player in each direction
		float overlapLeft = 0.0f;
		float overlapRight = 0.0f;
		float overlapTop = 0.0f;
		float overlapBottom = 0.0f;
		if (player->Pos.x <= tile->Pos.x + tile->Bounds.x &&
			player->Pos.x >= tile->Pos.x)
		{
			overlapLeft = (tile->Pos.x + tile->Bounds.x) - player->Pos.x;
		}

		if (player->Pos.x + player->Bounds.x >= tile->Pos.x &&
			player->Pos.x + player->Bounds.x <= tile->Pos.x + tile->Bounds.x)
		{
			overlapRight = (player->Pos.x + player->Bounds.x) - tile->Pos.x;
		}

		if (player->Pos.y <= tile->Pos.y + tile->Bounds.y &&
			player->Pos.y >= tile->Pos.y)
		{
			overlapTop = (tile->Pos.y + tile->Bounds.y) - player->Pos.y;
		}

		if (player->Pos.y + player->Bounds.y >= tile->Pos.y &&
			player->Pos.y + player->Bounds.y <= tile->Pos.y + tile->Bounds.y)
		{
			overlapBottom = (player->Pos.y + player->Bounds.y) - tile->Pos.y;
		}

		// There is no collision skip this tile
		if ((!overlapLeft && !overlapRight) || (!overlapTop && !overlapBottom))
		{
			continue;
		}

		// Should check overlap but will continue so it does not
		// treat it as solid
		if (tile->Portal)
		{
			// Overlap of both sides is greater than 0 means it
			// is completely in inside the tile
			// Assumption the tile is larger size than player, if
			// the player is larger than it can not be completly
			// inside
			if ((overlapLeft > tile->WIDTH / 2 &&
				overlapRight > tile->WIDTH / 2) &&
				(overlapTop > tile->HEIGHT / 2 &&
				 overlapBottom > tile->HEIGHT / 2))
			{
				if (currentWorld == "world")
				{
					LoadWorld("world2");
					player->Pos.y = 29 * Tile::HEIGHT - player->Bounds.y;
				}
				else if (currentWorld == "world2")
				{
					LoadWorld("world");
					player->Pos.y = 1 * Tile::HEIGHT;
				}
			}
			continue;
		}

		// Assumption: The direction the player is moving will result
		// in a smaller overlap than other directions
		// This actually adds a bit of a cool feature so the player does
		// not get caught on a corner, it will push the player out if
		// he is moving faster than the amount he is caught on the
		// corner
		// Check that the tile it's moving into is not a solid tile
		if (std::max(overlapLeft, overlapRight) <= std::max(overlapTop, overlapBottom))
		{
			// Collision on right or left side

			auto newIterator = it-Height;
			std::shared_ptr<Tile> rightTile;

			if (tile->Pos.x == 0) {
				player->Pos.x = tile->Pos.x + tile->Bounds.x;
			}
			else {
		
				rightTile = std::dynamic_pointer_cast<Tile>(*newIterator);
	
				newIterator = it+Height;
				auto leftTile = std::dynamic_pointer_cast<Tile>(*newIterator);
	
				if (overlapLeft <= overlapRight && !rightTile->Solid)
				{
					player->Pos.x = tile->Pos.x - player->Bounds.x;
				}
				else if (overlapRight < overlapLeft && !leftTile->Solid)
				{
					player->Pos.x = tile->Pos.x + tile->Bounds.x;
				}
			}
		}
		else if (std::max(overlapTop, overlapBottom) < std::max(overlapLeft, overlapRight))
		{
			// Collision on bottom or top side
			auto newIterator = it-1;
			auto bottomTile = std::dynamic_pointer_cast<Tile>(*newIterator);

			newIterator = it+1;
			auto topTile = std::dynamic_pointer_cast<Tile>(*newIterator);

			if (overlapTop <= overlapBottom && !bottomTile->Solid)
			{
				player->Pos.y = tile->Pos.y - player->Bounds.y;
			}
			else if (overlapBottom < overlapTop && !topTile->Solid)
			{
				player->Pos.y = tile->Pos.y + tile->Bounds.y;
			}
		}
	}
}

// Multiple maps? Potentially split into smaller 'Map' classes
// Have something to track the 'active map' then the for loop for the tiles would just be 'for tile : activeMap.Tiles) {...'
void World::Render() {
	for (auto tile : Tiles) {
		renderer->AddToFrame(tile);
	}
}
