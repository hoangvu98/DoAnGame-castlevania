#include "BossBat.h"
#include "Simon.h"
#include "EntranceLevel.h"
#include "debug.h"

CBossBat *CBossBat::__instance = NULL;

DWORD time_route=GetTickCount();
bool test=true;
float min_x, min_y, max_x, max_y;
void CBossBat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (state == BOSS_BAT_STATE_fLY)
	{
		if (animations[state]->GetCureentFrame() == 0)
			left = x - 18;
		else
			left = x - 12;
		top = y;
		bottom = top + BOSS_BAT_BBOX_HEIGHT;
		if (animations[state]->GetCureentFrame() == 0)
			right = left + BOSS_BAT_BBOX_WIDTH_1;
		else
			right = left + BOSS_BAT_BBOX_WIDTH_2;
	}
}

void CBossBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMonster::Update(dt, coObjects);
	//DebugOut(L"health=%d\n", health);
	if (state == BOSS_BAT_STATE_fLY)
	{
		CEntranceLevel *level1 = CEntranceLevel::GetInstance();
		float min, max;
		DWORD now = GetTickCount();
		CGameObject::Update(dt);
		CSimon* simon = CSimon::GetInstance();
		level1->GetSizeMap(min, max);
		min = 2576.0f;
		if (test == true)
		{
			test = false;
			float dx = simon->x-x;
			float v = dx / 1200;
			float v1;
			if (v < 0)
				v1 = -v;
			else
				v1 = v;
			if (v1 < BOSS_BAT_SPEEDING_X)
				vx = v;

			float dy = simon->y-y;
			v = dy / 800;
			float v2;
			if (v < 0)
				v2 = -v;
			else
				v2 = v;
			if (v2 < BOSS_BAT_SPEEDING_Y)
				vy = v;
			if (x + BOSSBAT_LIMIT_X > max)
				max_x = max;
			else
				max_x = x + BOSSBAT_LIMIT_X;
			if (x - BOSSBAT_LIMIT_X < min)
				min_x = min;
			else
				min_x = x - BOSSBAT_LIMIT_X;
			if (y + BOSSBAT_LIMIT_Y > 140)
				max_y = 140;
			else
				max_y = y + BOSSBAT_LIMIT_Y;
			if (y - BOSSBAT_LIMIT_Y < 0)
				min_y = 0;
			else
				min_y = y - BOSSBAT_LIMIT_Y;
		}
		
		if (x > max_x)
		{
			vx = -BOSS_BAT_SPEEDING_X;
		}
		if (x < min_x)
		{
			vx = BOSS_BAT_SPEEDING_X;
		}
		if (y > max_y)
		{
			vy = -BOSS_BAT_SPEEDING_Y;
		}
		if (y < min_y)
		{
			vy = BOSS_BAT_SPEEDING_Y;
		}
		
		if (now - time_route > 2000)
		{
			vx = 0; vy = 0;
		}
		if (now - time_route > 3000)
		{
			if(simon->x-x>0)
				vx = BOSS_BAT_SPEEDING_X;
			else
				vx = -BOSS_BAT_SPEEDING_X;
			if (simon->y - y > 0)
				vy = BOSS_BAT_SPEEDING_Y;
			else
				vy = BOSS_BAT_SPEEDING_Y;
			time_route = GetTickCount();
			test = true;
		}
		x +=dx;
		y +=dy;
		//DebugOut(L"vx=%f\nvy=%f\n", vx, vy);
	}
}

void CBossBat::Render()
{
	if (state != MONSTER_STATE_DISAPPEAR && state != MONSTER_STATE_DELETE)
	{
		if (state == BOSS_BAT_STATE_SLEEP)
			animations[0]->Render(x, y, 255);
		else
		{
			if (animations[state]->GetCureentFrame() == 0)
				animations[1]->Render(x - 18, y, 255);
			else
				animations[1]->Render(x - 12, y, 255);
		}
	}
}

void CBossBat::SetState(int state)
{
	CGameObject::SetState(state);
}

CBossBat * CBossBat::GetInstance()
{
	if (__instance == NULL) __instance = new CBossBat();
	return __instance;
}

CBossBat::CBossBat()
{
	score = 1000;
	health = 16;
	damage = 2;
	AddAnimation(20000);
	AddAnimation(20001);
	SetState(BOSS_BAT_STATE_SLEEP);
}
