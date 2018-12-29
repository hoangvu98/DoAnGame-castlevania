#pragma once
#include "GameObject.h"
#include "Monster.h"
#include "Bullet.h"
#define BAT_SMALL_FLYING_SPEED_X 0.05f
#define BAT_SMALL_FLYING_SPEED_Y 0.1f

#define BAT_BIG_SPEEDING_X 0.15f
#define BAT_BIG_SPEEDING_Y 0.075f

#define BAT_DISTANCE_FLY 20

#define BAT_SMALL_BBOX_WIDTH 16
#define BAT_SMALL_BBOX_HEIGHT 15

#define BAT_BIG_BBOX_WIDTH_1 47
#define BAT_BIG_BBOX_WIDTH_2 31
#define BAT_BIG_BBOX_HEIGHT 21

#define BAT_SMALL_ANI_LEFT	0
#define BAT_SMALL_ANI_RIGHT	1
#define BAT_BIG_ANI_FLY     2

#define BAT_STATE_FLY_LEFT	0
#define BAT_STATE_FLY_RIGHT	1
#define BAT_STATE_FLY       2
#define BAT_STATE_FIRE      3
#define BAT_STATE_SLEEPING  4

#define BAT_SIZE_SMALL 0
#define BAT_SIZE_BIG 1

#define BAT_BIG_LIMIT_X 100
#define BAT_BIG_LIMIT_Y 100

#define TIME_ROUTE 4000
class CBat : public CMonster
{
	float Height_Fly;
	int size;
	float weight, height;
	float appear_x, appear_y;
	int appear_state;
public:
	CBat(int size);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual void SetState(int state);
	void SetHeightFly(float height_fly);
	void SetSize(int size) { this->size = size; }
	int GetSize() { return size; }
	void SetSize(float weight, float height) { this->weight = weight; this->height = height; }
	void SetPosstionAppear(float appear_x, float appear_y) { this->appear_x = appear_x; this->appear_y = appear_y; }
	void GetPositionAppear(float &appear_x, float &appear_y) { appear_x = this->appear_x; appear_y = this->appear_y; }
	int GetStateAppear() { return appear_state; }
	void SetStateAppear(int appear_state) { this->appear_state = appear_state; }
};
