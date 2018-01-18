#ifndef ENTITY_H
#define ENTITY_H

#include "Point.h"

class Entity
{
public:
	Entity(std::string texture)
	:Texture(texture), Pos({100, 100}), Scale({1.0f, 1.0f}), Bounds({50, 50}), Health(100), Speed(10)  {};

	Entity(std::string texture, int64_t x, int64_t y)
	:Texture(texture), Pos({x, y}), Scale({1.0f, 1.0f}), Bounds({50, 50}), Health(100), Speed(10) {};

//	~Entity();
	std::string Texture;

	Point<int64_t> Pos;
	Point<int64_t> Size;
	Point<float>   Scale;
	Point<uint64_t> Bounds;

	int64_t Health;
	float   Speed;

	virtual void Update() = 0;

};
#endif //GAME_H
