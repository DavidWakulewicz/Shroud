#ifndef CAMERA_H
#define CAMERA_H

#include <cstdint>
#include <ostream>

template <typename T>
struct Point
{
public:
	T x;
	T y;

	void Set(T x, T y)
	{
		this->x = x;
		this->y = y;
	}

	friend std::ostream& operator<<(std::ostream& os, const Point& p)
	{
		os << "<" << p.x << ", " << p.y << ">";
		return os;
	}
};

class Camera
{
public:
	Camera();
	Camera(int64_t, int64_t);

	Point<int64_t> Pos;
	Point<float> Scale;
	Point<int64_t> Bounds;
	Point<int64_t> Size;

	void Update();
	void ZoomIn();
	void ZoomOut();
private:
};

#endif // CAMERA_H
