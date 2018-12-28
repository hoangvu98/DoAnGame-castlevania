#pragma once
#include "Monster.h"
#include "HeadDracula.h"
#include "Bullet.h"
#include "SpiritDracula.h"

#define DRACULA_STATE_INVISIBLE	0
#define DRACULA_STATE_FIRE		300
#define DRACULA_STATE_DIE		400
#define DRACULA_STATE_IDLE		500
//#define DRACULA_STATE_DIE		600
#define DRACULA_STATE_SLEEPING	700

#define DRACULA_ANI_IDLE_LEFT	0
#define DRACULA_ANI_FIRE_LEFT	1
#define DRACULA_ANI_IDLE_RIGHT	2
#define DRACULA_ANI_FIRE_RIGHT	3
#define DRACULA_ANI_FIRE_RIGHT1	4

#define DRACULA_BBOX_WIDTH		26
#define DRACULA_BBOX_HEIGHT		49

#define DRACULA_UNTOUCHABLE_TIME	1000
#define DRACULA_WAIT_TIME			1000
#define DRACULA_ATTACKING_TIME		1500
#define DRACULA_TIME_TO_RESET		3000

#define DRACULA_BBOX_WIDTH			26
#define DRACULA_BBOX_HEIGHT			50

#define OFFSET						7	

#define BULLET_POSITION_X			17.0f
#define BULLET_POSITION_Y			22.0f

#define DEFAULT_POSITION_X			204.0f
#define DEFAULT_POSITION_Y			95.0f
class CDracula :
	public CMonster
{
	static CDracula *__instance;
	CHeadDracula *head;
	CSpiritDracula *spirit_dracula;

	vector<CBullet *> bullets;

	int alpha;

	
	bool startwait1;
	bool startwait2;
	bool startwait3;

	bool wait;

	bool start;
	bool untouchable;

	bool reset;
	bool isSpirit;
	bool isfire;
	bool isAddBulletToCell;
	bool isAddHeadToCell;

	DWORD wait_start1;
	DWORD wait_start2;
	DWORD wait_start3;

	DWORD untouchable_start;

public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void LoadSpirit();
	void StartUntouchable();
	void StartWait(bool &startwait, DWORD &wait_start);
	void Reset();
	void SetState(int state);
	bool GetIsSpirit() { return isSpirit; }
	CHeadDracula *GetHead() { return this->head; }
	CSpiritDracula *GetSpiritDracula() { return this->spirit_dracula; }
	CDracula();
	CDracula(float x, float y);
	~CDracula();

	static CDracula *GetInstance();
};

