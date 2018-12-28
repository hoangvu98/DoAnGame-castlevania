#pragma once
#include "GameObject.h"
#define HIDENOBJECT_STATE_NORMAL        0
#define HIDENOBJECT_STATE_STAIR_UP      1
#define HIDENOBJECT_STATE_STAIR_DOWN    2
#define HIDENOBJECT_STATE_JUMP		    3
#define HIDENOBJECT_STATE_DOOR		    4
#define HIDENOBJECT_STATE_CASTLE_GATE   5
#define HIDENOBJECT_STATE_STAIR_UP_DOWN 6
#define HIDENOBJECT_STATE_HEAD			7

class CHidenObject :
	public CGameObject
{
protected:
	float width;
	float height;
	float stair_x,stair_y;
public:
	void GetSize(float &width, float &height) { width = this->width; height = this->height; }
	void SetSize(float width, float height) { this->width = width; this->height = height; }
	void SetState(int state);
	void SetStair_XY(float stair_x, float stair_y=0) { this->stair_x = stair_x; this->stair_y = stair_y; }
	void GetStair_XY(float &stair_x, float &stair_y) { stair_x=this->stair_x  ; stair_y= this->stair_y;}
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	CHidenObject();
	CHidenObject(float width, float height);
	CHidenObject(float width, float height, float stair_x, float stair_y, int nx);
};

