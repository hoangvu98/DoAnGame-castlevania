#pragma once
#include "GameObject.h"
#include "Monster.h"

#define HUNCHBACK_FLYING_SPEED 0.1f
#define HUNCHBACK_GRAVITY	   0.01f
#define HUNCHBACK_JUMP_SPEED   0.22f

#define HUNCHBACK_BBOX_WIDTH 15
#define HUNCHBACK_BBOX_HEIGHT 15

#define HUNCHBACK_STATE_FLY_LEFT	0
#define HUNCHBACK_STATE_FLY_RIGHT	1
#define HUNCHBACK_STATE_IDLE	    2
#define HUNCHBACK_STATE_JUMP	    3

#define HUNCHBACK_ANI_IDLE_LEFT	    0
#define HUNCHBACK_ANI_IDLE_RIGHT	1
#define HUNCHBACK_ANI_JUMP_LEFT	    2
#define HUNCHBACK_ANI_JUMP_RIGHT	3

class CHunchback : public CMonster
{
	DWORD time_stop;
	bool IsJump;
public:
	CHunchback();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual void SetState(int state);
};
