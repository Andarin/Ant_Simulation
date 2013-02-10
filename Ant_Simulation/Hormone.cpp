#include "Hormone.h"

Hormone::Hormone(Hormone_birth_info hormone_birth_info)
{
	_hormone_type = hormone_birth_info._hormone_type;
	_energy = hormone_birth_info._energy;
	_energy_consumption = hormone_birth_info._energy_consumption;
	_size = hormone_birth_info._size;
	_pos = hormone_birth_info._pos;
	_obj_type = OBJECT_TYPE_NR_OF_HORMONE;
}

Hormone::~Hormone(void)
{
}

void Hormone::update()
{
	_energy = std::min(0, _energy - _energy_consumption);

	if (_energy == 0)
	{
		destroy();
	}


}

void Hormone::destroy()
{
}