#include "Collision_detector.h"

Collision_detector::Collision_detector(double solf, double sview, double stouch)
{
	_sub_size_olf = solf;	
	_sub_size_view = sview;	
	_sub_size_touch = stouch;
}


Collision_detector::~Collision_detector(void)
{
}
