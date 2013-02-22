// This file is part of Ant_Simulation by Guillaume Martinet and Lucas Tittmann
// Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation
#pragma once
#include <memory>
#include <array>

class Position
{
public:
	Position(void);
	Position(double, double, double, std::array<double,2>);
	~Position(void);	

	std::shared_ptr<Position> clone(void);

	double _x;
	double _y;
	double _z;
	std::array<double,2> _direction ; //is a vector of norm equals one

private:
	std::shared_ptr<Position> clone_impl(void);
};