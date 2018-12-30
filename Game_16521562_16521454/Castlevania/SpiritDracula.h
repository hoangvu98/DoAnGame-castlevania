#pragma once
#include "Monster.h"
#include "Bullet.h"
#include "HidenObject.h"

#define SPIRITDRACULA_GRAVITY		0.002f
#define SPIRITDRACULA_JUMP_SPEED_X	0.09f
#define SPIRITDRACULA_JUMP_SPEED_Y	0.15f

#define SPIRITDRACULA_STATE_IDLE			0
#define SPIRITDRACULA_STATE_JUMP			300
#define SPIRITDRACULA_STATE_FALL			400
#define SPIRITDRACULA_STATE_FIRE			500
#define SPIRITDRACULA_STATE_DIE				600

#define SPIRITDRACULA_ANI_IDLE_LEFT				0
#define SPIRITDRACULA_ANI_PRE_JUMP_LEFT			1
#define SPIRITDRACULA_ANI_JUMP_LEFT				2
#define SPIRITDRACULA_ANI_LANDING_AND_FLY_LEFT	3

#define SPIRITDRACULA_ANI_IDLE_RIGHT			4
#define SPIRITDRACULA_ANI_PRE_JUMP_RIGHT		5
#define SPIRITDRACULA_ANI_JUMP_RIGHT			6
#define SPIRITDRACULA_ANI_LANDING_AND_FLY_RIGHT	7

#define SPIRITDRACULA_ANI_FIRE_LEFT				8
#define SPIRITDRACULA_ANI_FIRE_RIGHT			9


#define SPIRITDRACULA_JUMP_HEIGHT				5.0f

#define SPIRITDRACULA_WAIT_TIME				1000
#define SPIRITDRACULA_PRE_JUMP_TIME			200
#define SPIRITDRACULA_JUMP_TIME				350
#define SPIRITDRACULA_LANDING_TIME			150
#define SPIRITDRACULA_FIRE_TIME				2000


#define SPIRITDRACULA_BBOX_WIDTH	50
#define SPIRITDRACULA_BBOX_HEIGHT	68

#define SPIRITDRACULA_FIRE_BBOX_WIDTH 50
#define SPIRITDRACULA_FIRE_BBOX_HEIGHT 83


#define SPIRITDRACULA_OFFSET 19.0f
#define DISTANCE1		40.0f
#define DISTANCE2		50.0f

#define BULLET_POSITION_X	17
#define BULLET_POSITION_Y	26

#define BULLET_POSITION_X1	34

#define HEAD_POSITION_X		10.0f
#define HEAD_POSITION_X1	27.0f
#define HEAD_WIDTH			17
#define HEAD_HEIGHT			25

class CSpiritDracula :
	public CMonster
{
	static CSpiritDracula *__instance;
	vector<CBullet *> bullets;
	CHidenObject *head;
	float height;
	bool resetpos;
	bool Bullet;
	bool startwait1;
	bool startwait2;
	bool startwait3;
	bool startwait4;
	bool startwait5;
	bool startwait6;
	bool startwait7;

	bool wait;

	bool jump;

	bool reset;

	bool fire;
	bool isAddBulletToCell;
	bool isAddHeadToCell;

	DWORD wait_start1;
	DWORD wait_start2;
	DWORD wait_start3;
	DWORD wait_start4;
	DWORD wait_start5;
	DWORD wait_start6;
	DWORD wait_start7;
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void StartWait(bool &startwait, DWORD &wait_start);
	void SetState(int state);
	void Reset();
	static CSpiritDracula *GetInstance();
	CHidenObject *GetHead() { return this->head; }
	CSpiritDracula();
	CSpiritDracula(float x, float y);
	~CSpiritDracula();
};

