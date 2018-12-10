#include "Eagle.h"
CEagle::CEagle()
{
	damage = 4;
	health = 1;
	score = 300;
	AddAnimation(220003);
	AddAnimation(220004);
}

void CEagle::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + EAGLE_BBOX_WIDTH;
	bottom = y + EAGLE_BBOX_HEIGHT;
}

void CEagle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMonster::Update(dt,coObjects);
	x += dx;
}

void CEagle::Render()
{
	animations[state]->Render(x,y);
}

void CEagle::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case EAGLE_STATE_FLY_LEFT:
		vx = -EAGLE_FLYING_SPEED;
		break;
	case EAGLE_STATE_FLY_RIGHT:
		vx = EAGLE_FLYING_SPEED;
		break;
	}
}
