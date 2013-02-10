#pragma once
class Position
{
public:
	Position(void);
	Position(double, double, double, double);
	~Position(void);	

	double _x;
	double _y;
	double _z;
	double _direction; // degree in which object is rotated
};

