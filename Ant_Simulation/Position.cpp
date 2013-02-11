#include "Position.h"

Position::Position(void)
{
}

Position::Position(double x, double y, double z, double direction) 
{
	_x = x;
	_y = y;
	_z = z;
	_direction = direction;
}

Position::~Position(void) 
{
}