#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include "Monster.h"
#define FISHMAN_WALKING_SPEED 0.01f

#define FISHMAN_JUMP_SPEED_Y  0.7f
#define FISHMAN_GRAVITY       0.002f

#define FISHMAN_BBOX_FIRE_WIDTH		16
#define FISHMAN_BBOX_FIRE_HEIGHT	30

#define FISHMAN_BBOX_WIDTH 16
#define FISHMAN_BBOX_HEIGHT 30

#define FISHMAN_STATE_WALKING_RIGHT 0
#define FISHMAN_STATE_WALKING_LEFT  300
#define FISHMAN_STATE_JUMP          400
#define FISHMAN_STATE_FIRE          500

#define FISHMAN_ANI_FIRE_LEFT     0
#define FISHMAN_ANI_JUMP_LEFT     1
#define FISHMAN_ANI_WALKING_LEFT  2
#define FISHMAN_ANI_FIRE_RIGHT    3
#define FISHMAN_ANI_JUMP_RIGHT    4
#define FISHMAN_ANI_WALKING_RIGHT 5

#define FISHMAN_TURN			30.0f
#define FRAMETIME				200
class CFishman : public CMonster
{
	bool fire;
	CBullet *bullet;
	DWORD Time_Fishman_HitEffect;
	int i;
	int j;
	float appear_x, appear_y;
	int appear_state;
	float weight, height;

	bool wait1;
	bool wait2;
	bool isAddBulletToCell;

	DWORD start_wait1;
	DWORD start_wait2;

public:
	CFishman();
	CFishman(float width, float height, float a_x, float a_y);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual void SetState(int state);
	void SetPostionAppear(float appear_x, float appear_y) { this->appear_x = appear_x; this->appear_y = appear_y; }
	void GetPositionAppear(float &appear_x, float &appear_y) { appear_x = this->appear_x; appear_y = this->appear_y; }
	int GetStateAppear() { return appear_state; }
	void SetStateAppear(int appear_state) { this->appear_state = appear_state; }
	void SetSize(float weight, float height) { this->weight = weight; this->height = height; }

	void StartWait(bool &wait, DWORD &start_wait) { wait = false; start_wait = GetTickCount(); }
};