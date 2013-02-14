#pragma once
#include <memory>

class Position
{
public:
	Position(void);
	Position(double, double, double, double);
	~Position(void);	

	std::shared_ptr<Position> clone(void);

	double _x;
	double _y;
	double _z;
	double _direction; // degree in which object is rotated

private:
	std::shared_ptr<Position> clone_impl(void);
};