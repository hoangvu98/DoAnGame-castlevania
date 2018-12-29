#pragma once
#include "GameObject.h"
#include "Monster.h"

#define EAGLE_FLYING_SPEED 0.1f
#define EAGLE_BBOX_WIDTH 31
#define EAGLE_BBOX_HEIGHT 22

#define EAGLE_STATE_FLY_LEFT	0
#define EAGLE_STATE_FLY_RIGHT	1
#define EAGLE_STATE_IDLE_LEFT	2
#define EAGLE_STATE_IDLE_RIGHT	3
#define EAGLE_STATE_SLEEPING	4

class CEagle : public CMonster
{
	DWORD time_stop;
	float appear_x, appear_y;
	int appear_state;
	float weight, height;
public:
	CEagle();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual void SetState(int state);
	void SetPosstionAppear(float appear_x, float appear_y) { this->appear_x = appear_x; this->appear_y = appear_y; }
	void GetPositionAppear(float &appear_x, float &appear_y) { appear_x = this->appear_x; appear_y = this->appear_y; }
	int GetStateAppear() { return appear_state; }
	void SetStateAppear(int appear_state) { this->appear_state = appear_state; }
	void SetSize(float weight, float height) { this->weight = weight; this->height = height; }
};
