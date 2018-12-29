#include "BreakingWall.h"



CBreakingWall::CBreakingWall()
{
	AddAnimation(21000);
}

void CBreakingWall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (y <= height)
	{
		SetState(BREAKINGWALL_STATE_FALL);
		fall = true;
	}
	else if (fall == false)
		if (nx > 0) SetState(BREAKINGWALL_STATE_FLY_RIGHT);
		else SetState(BREAKINGWALL_STATE_FLY_LEFT);
	CGameObject::Update(dt);
	x += dx;
	y += dy;
}

void CBreakingWall::Render()
{
	animations[BREAKINGWALL_ANI]->Render(x, y);
}

void CBreakingWall::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BREAKINGWALL_STATE_FLY_LEFT:
		vx = -vx;
		vy = -BREAKINGWALL_SPEED_Y;
		break;
	case BREAKINGWALL_STATE_FLY_RIGHT:
		vx = vx;
		vy = -BREAKINGWALL_SPEED_Y;
		break;
	case BREAKINGWALL_STATE_FALL:
		vx = vx;
		vy = BREAKINGWALL_GRAVITY;
		break;
	}
}

void CBreakingWall::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + 10;
	bottom = y + 10;
}

