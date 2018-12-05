#include "Bat.h"

CBat::CBat()
{
	damage = 1;
	health = 1;
	score = 100;
	AddAnimation(12000);
	AddAnimation(12001);
	AddAnimation(12002);
	nx = -1;
	vy = BAT_FLYING_SPEED_Y;
}

void CBat::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + BAT_BBOX_WIDTH;
	bottom = y + BAT_BBOX_HEIGHT;
}

void CBat::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CMonster::Update(dt, coObjects);
	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 
	CSimon *simon = CSimon::GetInstance();
	if (state != MONSTER_STATE_DISAPPEAR && state != MONSTER_STATE_DELETE)
	{
		x += dx;
		y += dy;

		if (y > Height_Fly + BAT_DISTANCE_FLY)
		{
			y = Height_Fly + BAT_DISTANCE_FLY;
			vy = -vy;
		}
		if (y < Height_Fly - BAT_DISTANCE_FLY)
		{
			y = Height_Fly - BAT_DISTANCE_FLY;
			vy = -vy;
		}
	}
}

void CBat::Render()
{
	if (state != MONSTER_STATE_DISAPPEAR && state != MONSTER_STATE_DELETE)
	{
		int ani;
		if (nx > 0)
			ani = BAT_ANI_RIGHT;
		else
			ani = BAT_ANI_LEFT;
		animations[ani]->Render(x, y);
	}
}

void CBat::SetState(int state)
{
	CGameObject::SetState(state);
	CGameObject::SetState(state);
	switch (state)
	{
	case BAT_STATE_FLY_LEFT:
		vx = -BAT_FLYING_SPEED_X;
		//nx = -1;
		break;
	case BAT_STATE_FLY_RIGHT:
		vx = BAT_FLYING_SPEED_X;
		//nx = -1;
		break;
	}
}

void CBat::SetHeightFly(float height_fly)
{
	Height_Fly = height_fly;
}
