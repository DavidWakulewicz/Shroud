#ifndef POINT_H
#define POINT_H

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
		os << p.x << ", " << p.y << ">";
		return os;
	}
};

#endif // POINT_H
