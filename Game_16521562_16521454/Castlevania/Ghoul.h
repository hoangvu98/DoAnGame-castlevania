#pragma once
#include "Monster.h"
using namespace std;
#define GHOUL_WALKING_SPEED 0.01;

#define GHOUL_BBOX_WIDTH 15
#define GHOUL_BBOX_HEIGHT 31

#define GHOUL_ANI_LEFT  0
#define GHOUL_ANI_RIGHT 1

#define GHOUL_STATE_LEFT  0
#define GHOUL_STATE_RIGHT 1
#define FrameTime 200


class CGhoul : public CMonster
{
	float min, max;
	DWORD Time_HitEffect;
	DWORD Time_Reset;
	bool reset;
public:
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual void SetState(int state);
	void SetLimit(float min, float max) { this->min = min; this->max = max; }
	void Reset();
	CGhoul();
};