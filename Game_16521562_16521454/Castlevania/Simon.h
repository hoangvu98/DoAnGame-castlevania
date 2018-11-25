#pragma once
#include "GameObject.h"
#include "Whip.h"
#include "InputImage.h"
#include <vector>
#include "Items.h"
using namespace std;
#define WHIP_TEXTURE_PATH L"castlevania_texture\\Weapon\\Whip.png"

#define SIMON_WALKING_SPEED		0.1f
#define SIMON_JUMP_SPEED		0.2f
#define SIMON_GRAVITY			0.01f
#define SIMON_DEFLECT_SPEED		0.1f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_LEFT	1
#define SIMON_STATE_WALKING_RIGHT	2
#define SIMON_STATE_JUMP			3
#define SIMON_STATE_KNEE			4
#define SIMON_STATE_DIE				5
#define SIMON_STATE_UPDATE          6
#define SIMON_STATE_STAIR_UP_IDLE   7
#define SIMON_STATE_STAIR_DOWN_IDLE	8
#define SIMON_STATE_STAIR_UP        9
#define SIMON_STATE_STAIR_DOWN      10
#define SIMON_STATE_COLLUSION       11

#define SIMON_ANI_WALKING_LEFT		    0
#define SIMON_ANI_WALKING_RIGHT		    1
#define SIMON_ANI_IDLE_LEFT			    2
#define SIMON_ANI_IDLE_RIGHT		    3
#define SIMON_ANI_JUMP_LEFT			    4
#define SIMON_ANI_JUMP_RIGHT		    5
#define SIMON_ANI_FIGHT_LEFT		    6
#define SIMON_ANI_FIGHT_RIGHT		    7
#define SIMON_ANI_KNEE_FIGHT_LEFT	    8
#define SIMON_ANI_KNEE_FIGHT_RIGHT      9
#define SIMON_ANI_STAIR_UP_LEFT		    10
#define SIMON_ANI_STAIR_UP_RIGHT		11
#define SIMON_ANI_STAIR_DOWN_LEFT		12
#define SIMON_ANI_STAIR_DOWN_RIGHT		13
#define SIMON_ANI_STAIR_IDLE_UP_LEFT	14
#define SIMON_ANI_STAIR_IDLE_UP_RIGHT	15
#define SIMON_ANI_STAIR_IDLE_DOWN_LEFT	16
#define SIMON_ANI_STAIR_IDLE_DOWN_RIGHT	17
#define SIMON_ANI_STAIR_FIGHT_LEFT	    18
#define SIMON_ANI_STAIR_FIGHT_RIGHT    	19
#define SIMON_ANI_COLLUSION_LEFT        20
#define SIMON_ANI_COLLUSION_RIGHT       21

//#define SIMON_ANI_DIE_LEFT			10
//#define SIMON_ANI_DIE_RIGHT			11

#define SIMON_BBOX_IDLE_WIDTH		15
#define SIMON_BBOX_IDLE_HEIGHT		30

#define SIMON_BBOX_KNEE_WIDTH		18
#define SIMON_BBOX_KNEE_HEIGHT		25

#define SIMON_BBOX_KNEE_FIGHT_WIDTH		18
#define SIMON_BBOX_KNEE_FIGHT_HEIGHT	25

#define TIME_STAIR 400
class CSimon :public CGameObject
{
	static CSimon *__instance;
	int heart = 0;
	int mx;
	int previousstate;
	int state_update;
	CWhip *whip;
	DWORD FrameUpdate;
	DWORD FrameWeapon;
	bool OnSkill = false;
	bool skill = false;
	bool jump = true;
	bool fight = false;
	int alpha = 255;
	int stair = 0; //0 b?nh thư?ng 1 g?p c?c 2 đang lên
	CItems* weapon;
	DWORD FrameStair = 0;
	int test = 0;
	int collusion = 0;//0 co the đụng 1 đã đụng -đứng 2 đã đụng - có thể di chuyển 
	int collusion_nx = 0;
public:
	DWORD test_stair = 0;
	float simon_x;
	float simon_y;
	int IsUp = 0;
	int IsDown = 0;
	int state_auto = 0;
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObject = NULL);
	void Render();
	void GetBoundingBox(float & left, float & top, float & right, float & bottom);
	int GetPreviousState();
	void SetState(int state);
	bool GetSkill() { return skill; }
	void SetSkill(bool skill) { this->skill = skill; }
	bool GetJump() { return jump; }
	void SetJump(bool jump) { this->jump = jump; }
	bool GetFight() { return fight; }
	void SetFight(bool fight) { this->fight = fight; }
	void SetFrameWeapon() { FrameWeapon = GetTickCount(); }
	DWORD GetFrameWeapon() { return FrameWeapon; }
	bool GetOnSkill() { return OnSkill; }
	CItems* GetWeapon() { return weapon; }
	CWhip* GetWhip() { return whip; }
	int GetStair() { return stair; }
	void SetStair(int stair) { this->stair = stair; }
	void SetFrameStair() { FrameStair = GetTickCount(); }
	int GetCollusion() { return collusion; }
	DWORD GetFrameStair() { return FrameStair; }
	DWORD GetFrameUpdate()
	{
		return FrameUpdate;
	}
	CSimon() :CGameObject()
	{
		AddAnimation(101);
		AddAnimation(102);
		AddAnimation(201);
		AddAnimation(202);
		AddAnimation(301);
		AddAnimation(302);
		AddAnimation(401);
		AddAnimation(402);
		AddAnimation(501);
		AddAnimation(502);
		AddAnimation(601);
		AddAnimation(602);
		AddAnimation(603);
		AddAnimation(604);
		AddAnimation(701);
		AddAnimation(702);
		AddAnimation(703);
		AddAnimation(704);
		AddAnimation(801);
		AddAnimation(802);
		AddAnimation(901);
		AddAnimation(902);

		mx = 0;
		previousstate = state;
		whip = new CWhip();
		whip->SetState(WHITE_WHIP);
	

	}
	static CSimon *GetInstance();
};

