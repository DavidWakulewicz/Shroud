#ifndef CAMERA_H
#define CAMERA_H

#include <cstdint>
#include <ostream>
#include <memory>

#include "Point.h"
#include "Player.h"

class Camera
{
public:
	Camera(std::shared_ptr<Player>);
	Camera(std::shared_ptr<Player>, int64_t, int64_t);

	Point<int64_t> Pos;
	Point<float> Scale;
	Point<int64_t> Bounds;
	Point<int64_t> Size;

	void Update();
	void ZoomIn();
	void ZoomOut();
private:
	std::shared_ptr<Player> player;
};

#endif // CAMERA_H
