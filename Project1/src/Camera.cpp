#include "Camera.h"

Camera::Camera()
	: position({0, 0}), scale({1.0f, 1.0f}), bounds({640, 480})
{
}

Camera::Camera(int64_t x, int64_t y)
	: position({x, y}), scale({1.0f, 1.0f}), bounds({640, 480})
{
}

void Camera::Update()
{
	if (position.x < 0)
	{
		position.x = 0;
	}
	else if (position.x > bounds.x - (size.x / scale.x))
	{
		position.x = bounds.x - (size.x / scale.x);
	}

	if (position.y < 0)
	{
		position.y = 0;
	}
	else if (position.y > (bounds.y * scale.y) - size.y)
	{
		position.y = (bounds.y * scale.y) - size.y;
	}
}

void Camera::ZoomIn()
{
	if (scale.x > 0.5f)
	{
		scale.x -= 0.05f;
	}
	if (scale.y > 0.5f)
	{
		scale.y -= 0.05f;
	}
}

void Camera::ZoomOut()
{
	if (scale.x < 3.0f)
	{
		scale.x += 0.05f;
	}
	if (scale.y < 3.0f)
	{
		scale.y += 0.05f;
	}
}
