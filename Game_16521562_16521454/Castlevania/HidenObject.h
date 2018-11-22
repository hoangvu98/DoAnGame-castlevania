#pragma once
#include "GameObject.h"
#define HIDENOBJECT_STATE_NORMAL 0
#define HIDENOBJECT_STATE_STAIR 1
#define HIDENOBJECT_STATE_STAIR_UP 1
#define HIDENOBJECT_STATE_STAIR_DOWN 2
class CHidenObject :
	public CGameObject
{
protected:
	float width;
	float height;

public:
	void GetSize(float &width, float &heigth) { width = this->width; height = this->height; }
	void SetSize(float width, float height) { this->width = width; this->height = height; }
	void SetState(int state);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

