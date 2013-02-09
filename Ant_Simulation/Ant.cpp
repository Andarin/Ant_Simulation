#include "Ant.h"

Ant::Ant(Ant_birth_info ant_birth_info)
{
	const int _ANT_TYPE = ant_birth_info._ant_type;
	const double _SPEED = ant_birth_info._speed;
	const int _ATTACK_POINTS = ant_birth_info._attack_points;
	const int _ARMOR = ant_birth_info._armor;
	const int _TRANSPORT_CAPABILITY = ant_birth_info._transport_capability;
	const int _COLOR = ant_birth_info._color;
}

Ant::~Ant(void)
{
}