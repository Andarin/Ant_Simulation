#pragma once
#include "Game_object_birth_info.h"
#include "models.h"
#include "Position.h"

class Game_object
{
public:
	Game_object(void);
	Game_object(Game_object_birth_info);
	~Game_object(void);
	virtual void update();
	int _obj_type;
private:
	Position _pos;
};