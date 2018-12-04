#include "Ghoul.h"
#include "InputImage.h"
#include "debug.h"
#include "Simon.h"
#include "Game.h"
bool reset;
DWORD Time_HitEffect = GetTickCount();
DWORD Time_Rest = GetTickCount();
void CGhoul::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + GHOUL_BBOX_WIDTH;
	bottom = y + GHOUL_BBOX_HEIGHT;
}

void CGhoul::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
	DWORD now = GetTickCount();
	CSimon* simon = CSimon::GetInstance();
	CGame *game = CGame::GetInstance();
	float cx, cy;
	game->GetCamera(cx, cy);
	if (state == GHOUL_STATE_DELETE && reset == true)
	{
		reset = false;
		Time_Rest = GetTickCount();
	}
	if (state == GHOUL_STATE_DELETE)
		if (now - Time_Rest > 2000)
		{
			Reset();
		}
	if (state == GHOUL_STATE_LEFT || state == GHOUL_STATE_RIGHT)
	{
		x += dx;
		y += dy;
	}
	else if (state == GHOUL_STATE_DELETE)
	{
		if (cx >= min && cx + 256.0f <= max)
			x = simon->x;
	}
}

void CGhoul::Render()
{
	int ani;
	if (state == GHOUL_STATE_LEFT)
	{
		ani = GHOUL_ANI_LEFT;
		animations[ani]->Render(x, y);
		Time_HitEffect = GetTickCount();
	}
	else if (state == GHOUL_STATE_RIGHT)
	{
		ani = GHOUL_ANI_RIGHT;
		animations[ani]->Render(x, y);
		Time_HitEffect = GetTickCount();
	}
	else if (state == GHOUL_STATE_DISAPPEAR)
	{
		int now = GetTickCount();
		hiteffect->SetPosition(x, y);
		items->SetPosition(x + 5, y + 10);
		hiteffect->Render();
		if (now - Time_HitEffect >= FrameTime)
			SetState(GHOUL_STATE_DELETE);
	}
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
	case GHOUL_STATE_DISAPPEAR:
		Time_Rest = GetTickCount();
		break;
	}
}
void CGhoul::Reset()
{
	CSimon* simon = CSimon::GetInstance();
	CGame *game = CGame::GetInstance();
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
	srand(time(NULL));
	random = rand() % 2;
	switch (random)
	{
	case 0:
		items = new CDagger();
		break;
	case 1:
		random = rand() % 2;
		switch (random)
		{
		case 0:
			items = new CHeart(HEART_BIG);
			break;
		case 1:
			items = new CHeart(HEART_SMALL);
			break;
		}
		break;
	}
}
CGhoul::CGhoul()
{
	health = 1;
	score = 100;
	damage = 1;
	AddAnimation(10000);
	AddAnimation(10001);
	int random;
	srand(time(NULL));
	random = rand() % 2;
	switch (random)
	{
	case 0:
		items = new CDagger();
		break;
	case 1:
		random = rand() % 2;
		switch (random)
		{
		case 0:
			items = new CHeart(HEART_BIG);
			break;
		case 1:
			items = new CHeart(HEART_SMALL);
			break;
		}
		break;
	}
}
