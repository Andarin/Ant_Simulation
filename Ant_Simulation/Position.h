// This file is part of Ant_Simulation by Guillaume Martinet and Lucas Tittmann
// Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation

// class to store all the information concerning the positions of objects in 
// the simulation
// it should be noticed that in our simulation x and z are the plane (ground)
// coordinates and y is the height coord
// _direction is therefore a normalized vector in the x-z-plane
#pragma once
#include <memory>
#include <array>

class Position
{
public:
	Position(void);
	Position(double, double, double, std::array<double,2>);
	~Position(void);	

	// method to clone the object and return a pointer to the new object
	std::shared_ptr<Position> clone(void);

	double _x;
	double _y;
	double _z;
	std::array<double,2> _direction ; //is a vector of norm equals one

private:
	// method to clone the object
	std::shared_ptr<Position> clone_impl(void);
};