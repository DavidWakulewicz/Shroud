#ifndef TILE_H
#define TILE_H

#include <string>
#include <memory>

#include <SDL2/SDL.h>

#include "Camera.h"

class Tile: public Entity
{
public:
	const static uint8_t WIDTH;
	const static uint8_t HEIGHT;

	Tile(std::string);

	bool Solid;
	bool Portal;
private:
	void Update(){
		return;
	};
};
#endif // TILE_H
