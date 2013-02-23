// This file is part of Ant_Simulation by Guillaume Martinet and Lucas Tittmann
// Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation
#include "Position.h"

Position::Position(void)
{
}

Position::Position(double x, double y, double z, std::array<double,2> direction) 
{
	_x = x;
	_y = y;
	_z = z;
	_direction = direction;
}

Position::~Position(void) 
{
}

std::shared_ptr<Position> Position::clone()
{
	return clone_impl();
}

std::shared_ptr<Position> Position::clone_impl()
{
	return(std::shared_ptr<Position>(new Position(*this)));
}