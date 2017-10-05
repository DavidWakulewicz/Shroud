#include "Camera.h"

Camera::Camera(std::shared_ptr<Player> player)
	: Pos({0, 0}), Scale({1.0f, 1.0f}), Bounds({640, 480}), player(player)
{
}

Camera::Camera(std::shared_ptr<Player> player, int64_t x, int64_t y)
	: Pos({x, y}), Scale({1.0f, 1.0f}), Bounds({640, 480}), player(player)
{
}

void Camera::Update()
{
	this->Pos = player->Pos;

	if (Pos.x < 0)
	{
		Pos.x = 0;
	}
	else if (Pos.x > Bounds.x - (Size.x / Scale.x))
	{
		Pos.x = Bounds.x - (Size.x / Scale.x);
	}

	if (Pos.y < 0)
	{
		Pos.y = 0;
	}
	else if (Pos.y > Bounds.y - (Size.y / Scale.y))
	{
		Pos.y = Bounds.y - (Size.y / Scale.y);
	}
}

void Camera::ZoomIn()
{
	if (Scale.x > 0.5f)
	{
		Scale.x -= 0.05f;
	}
	if (Scale.y > 0.5f)
	{
		Scale.y -= 0.05f;
	}
}

void Camera::ZoomOut()
{
	if (Scale.x < 3.0f)
	{
		Scale.x += 0.05f;
	}
	if (Scale.y < 3.0f)
	{
		Scale.y += 0.05f;
	}
}
