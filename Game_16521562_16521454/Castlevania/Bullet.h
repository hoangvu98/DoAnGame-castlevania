#pragma once
#include "GameObject.h"
#include "debug.h"

#define BULLET_SPEED	0.2f

#define BULLET_BBOX_WIDTH	7
#define BULLET_BBOX_HEIGHT	6

#define BULLET_STATE_LEFT	0
#define BULLET_STATE_RIGHT	100

#define BULLET_ANI_LEFT		0
#define BULLET_ANI_RIGHT	1

class CBullet :
	public CGameObject
{
public:
	CBullet();
	~CBullet();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void SetState(int state);
};

