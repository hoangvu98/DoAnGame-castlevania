#pragma once
#include "GameObject.h"

#define BREAKINGWALL_GRAVITY	0.5f
#define BREAKINGWALL_SPEED_X	0.01f
#define BREAKINGWALL_SPEED_Y	0.02f

#define BREAKINGWALL_STATE_FLY_LEFT		0
#define BREAKINGWALL_STATE_FLY_RIGHT	1
#define BREAKINGWALL_STATE_FALL			2

#define BREAKINGWALL_ANI	0

class CBreakingWall :
	public CGameObject
{
	float height;
	bool fall;
public:
	CBreakingWall();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void SetState(int state);
	void SetHeight(float height) { this->height = height; }
	void SetFall(bool fall) { this->fall = fall; }
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};
