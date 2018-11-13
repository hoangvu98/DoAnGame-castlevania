#pragma once
#include "GameObject.h"
#define DOOR_WIDTH	18
#define DOOR_HEIGHT	34

class CDoor :
	public CGameObject
{
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render();
};

