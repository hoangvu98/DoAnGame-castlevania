#include "HeadDracula.h"
#include "debug.h"


void CHeadDracula::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMonster::Update(dt, coObjects);
	if (state != MONSTER_STATE_DELETE && state != MONSTER_STATE_DISAPPEAR)
	{
		x += dx;
		y += dy;
		if (y <= HEAD_FLY_HEIGHT) SetState(HEAD_STATE_IDLE);
	}
}

void CHeadDracula::Render()
{
	int ani;
	if (nx > 0) ani = HEAD_ANI_RIGHT;
	else ani = HEAD_ANI_LEFT;
	animations[ani]->Render(x, y);
}

void CHeadDracula::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + HEAD_BBOX_WIDTH;
	bottom = y + HEAD_BBOX_HEIGHT;
}

void CHeadDracula::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case HEAD_STATE_FLY:
		vy = -HEAD_SPEED_Y;
		break;
	case HEAD_STATE_IDLE:
		vy = 0;
		break;
	}
}

CHeadDracula::CHeadDracula()
{
	health = 16;
	damage = 4;
	AddAnimation(240011);
	AddAnimation(240012);
}


CHeadDracula::~CHeadDracula()
{
}
