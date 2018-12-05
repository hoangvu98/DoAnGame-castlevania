#pragma once
#include "GameObject.h"
#include "Monster.h"
#define BOSS_BAT_STATE_SLEEP 0
#define BOSS_BAT_STATE_fLY   1

#define BOSS_BAT_BBOX_WIDTH_1 47
#define BOSS_BAT_BBOX_WIDTH_2 31
#define BOSS_BAT_BBOX_HEIGHT 21

#define BOSS_BAT_SPEEDING_X 0.1f
#define BOSS_BAT_SPEEDING_Y 0.075f

#define BOSSBAT_LIMIT_X 120
#define BOSSBAT_LIMIT_Y 105
class CBossBat : public CMonster
{
	static CBossBat *__instance;
	int nx = 0,ny=0;
public:
	 void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	 void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	 void Render();
	 void SetState(int state);

	 static CBossBat * GetInstance();
	 CBossBat();
};