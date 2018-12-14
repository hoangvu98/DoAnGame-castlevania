#pragma once
#include "Monster.h"
#include "HeadDracula.h"
#include "Bullet.h"
#define DRACULA_STATE_INVISIBLE	0
#define DRACULA_STATE_FIRE		300
#define DRACULA_STATE_DIE		400
#define DRACULA_STATE_IDLE		500

#define DRACULA_ANI_IDLE_LEFT	0
#define DRACULA_ANI_FIRE_LEFT	1
#define DRACULA_ANI_IDLE_RIGHT	2
#define DRACULA_ANI_FIRE_RIGHT	3

#define DRACULA_BBOX_WIDTH		26
#define DRACULA_BBOX_HEIGHT		49

#define DRACULA_UNTOUCHABLE_TIME	2000
#define DRACULA_WAIT_TIME			1000
#define DRACULA_ATTACKING_TIME		3000

#define DRACULA_ALPHA_TIME		200

class CDracula :
	public CMonster
{
	CHeadDracula *head;
	vector<CBullet *> bullets;

	int alpha;

	bool start;
	bool untouchable;
	bool attack;

	DWORD start_attack;
	DWORD wait;
	DWORD untouchable_start;
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void StartUntouchable();
	void StartAttacking();
	void SetState(int state);
	CDracula();
	~CDracula();
};

