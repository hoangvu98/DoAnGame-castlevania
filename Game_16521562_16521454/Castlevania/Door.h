#pragma once
#include "GameObject.h"
#define DOOR_WIDTH	18
#define DOOR_HEIGHT	34

#define DOOR_STATE_CLOSE	0
#define DOOR_STATE_OPEN		100

#define DOOR_ANI_CLOSE		0
#define DOOR_ANI_OPEN_1		1
#define DOOR_ANI_OPEN_2		2

class CDoor :
	public CGameObject
{
	bool IsHiden;
	bool stop;
	int i;
public:
	bool IsGo = true;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render();
	void SetStop(bool stop) { this->stop = stop; }
	void SetIsHiDen(bool IsHiden) {this->IsHiden= IsHiden;}
	bool GetIsHiden() { return IsHiden; }
	CDoor();
};

