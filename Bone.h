#pragma once
#include "GameObject.h"
#define BONE_SPEED_X		0.08f
#define BONE_SPEED_Y		0.1f
#define BONE_GRAVITY		0.002f
#define BONE_BBOX_WIDTH		15
#define BONE_BBOX_HEIGHT	15

#define BONE_ANI_FLY_LEFT	0
#define BONE_ANI_FLY_RIGHT	1

#define HEIGHT				50
class CBone :
	public CGameObject
{
	float height;
	bool fall;
	int damage;
public:
	CBone();
	void InitHeight();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void SetFall(bool fall) { this->fall = fall; }
	void SetHeight(float height) { this->height = height; }
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	int GetDamage() { return damage; }
	~CBone();
};

