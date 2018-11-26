#pragma once
#include "GameObject.h"
#include "Simon.h"

#define BAT_FLYING_SPEED_X 0.05f
#define BAT_FLYING_SPEED_Y 0.1f

#define BAT_GRAVITY		 0.002f
#define BAT_DISTANCE_FLY 10

#define BAT_BBOX_WIDTH 16
#define BAT_BBOX_HEIGHT 15

#define BAT_ANI_HANGING	0
#define BAT_ANI_LEFT	1
#define BAT_ANI_RIGHT	2

#define BAT_STATE_FLY_LEFT	100
#define BAT_STATE_FLY_RIGHT	200
#define BAT_STATE_HANGING	300
#define BAT_STATE_INVISIBLE	400

#define MOVING_AREA_WIDTH	100;
#define MOVING_AREA_HEIGHT	100;

#define DISTANCE			160


class CBat : public CGameObject
{
	int left, top, right, bottom;
	float Height_Fly;
public:
	CBat();

	void InitMovingArea();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual void SetState(int state);
	void SetHeightFly(float height_fly);
};
