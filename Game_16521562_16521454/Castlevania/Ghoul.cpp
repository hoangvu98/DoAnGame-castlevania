#include "Ghoul.h"
#include "InputImage.h"
#include "debug.h"
#include "Simon.h"
#include "Game.h"
DWORD Time_Reset_Ghoul;
void CGhoul::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + GHOUL_BBOX_WIDTH;
	bottom = y + GHOUL_BBOX_HEIGHT;
}

void CGhoul::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CMonster::Update(dt, coObjects);
	DWORD now = GetTickCount();
	CSimon* simon = CSimon::GetInstance();
	CGame *game = CGame::GetInstance();
	float cx, cy;
	game->GetCamera(cx, cy);
	if (state == MONSTER_STATE_DELETE)
		if (now - Time_Reset_Ghoul > FrameTime)
			if (now - Time_Reset > FrameTimeReset)
			{
				Reset();
				Time_Reset = GetTickCount();
				Time_Reset_Ghoul = GetTickCount();
			}
	if (state == GHOUL_STATE_LEFT || state == GHOUL_STATE_RIGHT)
	{
		x += dx;
		y += dy;
		if (x > cx + 256.0f || x < cx)
		{
			x -= dx;
			SetState(MONSTER_STATE_DELETE);
		}
	}
	else if (state == MONSTER_STATE_DELETE)
	{
		x = simon->x;
	}
}

void CGhoul::Render()
{
	CMonster::Render();
	int ani;
	if (state == GHOUL_STATE_LEFT)
	{
		ani = GHOUL_ANI_LEFT;
		animations[ani]->Render(x, y);
	}
	else if (state == GHOUL_STATE_RIGHT)
	{
		ani = GHOUL_ANI_RIGHT;
		animations[ani]->Render(x, y);
	}
	//RenderBoundingBox(200);
}

void CGhoul::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GHOUL_STATE_LEFT:
		vx = -GHOUL_WALKING_SPEED;
		nx = -1;
		break;
	case GHOUL_STATE_RIGHT:
		vx = GHOUL_WALKING_SPEED;
		nx = 1;
		break;
	case MONSTER_STATE_DISAPPEAR:
		Time_Reset = GetTickCount();
		break;
	}
}
void CGhoul::Reset()
{
	CSimon* simon = CSimon::GetInstance();
	CGame *game = CGame::GetInstance();
	if (area_max == 0 && area_min == 0)
	{
		float cx, cy;
		game->GetCamera(cx, cy);
		if (simon->nx > 0)
		{
			SetState(GHOUL_STATE_LEFT);
			SetPosition(cx + 256.0f, y);
		}
		else
		{
			SetState(GHOUL_STATE_RIGHT);
			SetPosition(cx, y);
		}
		health = 1;
		int random;
		random = rand() % 10;
		if (random <= 1)
			items = new CHeart(HEART_BIG);
		else if (random <= 3)
			items = new CHeart(HEART_SMALL);
		else
			items = NULL;
	}
	else
	{
		if (simon->x >= area_min && simon->x <= area_max)
		{
			float cx, cy;
			game->GetCamera(cx, cy);
			if (simon->nx > 0)
			{
				SetState(GHOUL_STATE_LEFT);
				SetPosition(cx + 256.0f, y);
			}
			else
			{
				SetState(GHOUL_STATE_RIGHT);
				SetPosition(cx, y);
			}
			health = 1;
			int random;
			random = rand() % 10;
			if (random <= 1)
				items = new CHeart(HEART_BIG);
			else if (random <= 3)
				items = new CHeart(HEART_SMALL);
			else
				items = NULL;
		}
	}
}
CGhoul::CGhoul()
{
	CMonster::CMonster();
	health = 1;
	score = 100;
	damage = 1;
	area_max = 0;
	area_min = 0;
	AddAnimation(10000);
	AddAnimation(10001);
	int random;
	//srand(time(NULL));
	random = rand() % 10;
	if (random <= 1)
		items = new CHeart(HEART_BIG);
	else if (random <= 3)
		items = new CHeart(HEART_SMALL);
	else
		items = NULL;
}
