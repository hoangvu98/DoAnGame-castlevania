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
	int damage;
public:
	CBullet();
	~CBullet();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void SetState(int state);
	void SetSpeed(float x1, float y1, float x2, float y2, int time);
	void SetState(float x1, float x2);
	int GetDamage() { return damage; }
	void SetDamage(int damage) { this->damage= damage; }
};

