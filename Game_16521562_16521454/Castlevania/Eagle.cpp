#include "Eagle.h"
#include "Simon.h"
#include "Game.h"
CEagle::CEagle()
{
	damage = 4;
	health = 1;
	score = 300;
	AddAnimation(220003);
	AddAnimation(220004);
	AddAnimation(220005);
	AddAnimation(220006);
}

void CEagle::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if(state==EAGLE_STATE_SLEEPING)
	{ 
		left = x;
		top = y;
		right = x + weight;
		bottom = y + height;
	}
	else
	{
		left = x;
		top = y;
		right = x + EAGLE_BBOX_WIDTH;
		bottom = y + EAGLE_BBOX_HEIGHT;
	}
}

void CEagle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMonster::Update(dt,coObjects);
	x += dx;
	DWORD now = GetTickCount();
	CSimon* simon = CSimon::GetInstance();
	CGame *game = CGame::GetInstance();
	float cx, cy;
	game->GetCamera(cx, cy);
	if (state != EAGLE_STATE_SLEEPING)
	{
		if (now - time_stop > 1500)
		{
			if (nx > 0)
				SetState(EAGLE_STATE_FLY_RIGHT);
			else
				SetState(EAGLE_STATE_FLY_LEFT);
		}
		else if (now - time_stop > 1000)
		{
			if (nx > 0)
				SetState(EAGLE_STATE_IDLE_RIGHT);
			else
				SetState(EAGLE_STATE_IDLE_LEFT);
		}
		if (x > cx + 256.0f || x < cx)
		{
			float cx, cy, tx, ty;
			GetPositionAppear(cx, cy);
			GetPosition(tx, ty);
			SetPosstionAppear(tx, ty);
			SetPosition(cx, cy);
			SetState(EAGLE_STATE_SLEEPING);
		}
	}
}

void CEagle::Render()
{
	if(state!= EAGLE_STATE_SLEEPING)
		animations[state]->Render(x,y);
	RenderBoundingBox(200);
}

void CEagle::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case EAGLE_STATE_FLY_LEFT:
		vx = -EAGLE_FLYING_SPEED;
		time_stop = GetTickCount();
		nx = -1;
		break;
	case EAGLE_STATE_FLY_RIGHT:
		vx = EAGLE_FLYING_SPEED;
		time_stop = GetTickCount();
		nx = 1;
		break;
	case EAGLE_STATE_IDLE_LEFT:
		vx = 0;
		break;
	case EAGLE_STATE_IDLE_RIGHT:
		vx = 0;
		break;
	case EAGLE_STATE_SLEEPING:
		vx = 0;
	}
}
