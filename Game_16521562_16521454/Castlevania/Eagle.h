#pragma once
#include "GameObject.h"
#include "Monster.h"

#define EAGLE_FLYING_SPEED 0.05f
#define EAGLE_BBOX_WIDTH 31
#define EAGLE_BBOX_HEIGHT 22

#define EAGLE_STATE_FLY_LEFT	0
#define EAGLE_STATE_FLY_RIGHT	1
class CEagle : public CMonster
{
public:
	CEagle();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual void SetState(int state);
};
