#include "Bat.h"

CBat::CBat()
{
	AddAnimation(12000);
	AddAnimation(12001);
	AddAnimation(12002);
	Height_Fly = 5;
	nx = -1;
}

void CBat::InitMovingArea()
{
	if (nx > 0)
		left = x + DISTANCE;
	else if (nx < 0)
		left = x - DISTANCE;
	top = y;
	right = left + MOVING_AREA_WIDTH;
	bottom = right + MOVING_AREA_HEIGHT;
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
	CGameObject::Update(dt);
	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 
	CSimon *simon = CSimon::GetInstance();
	float sx, sy;
	simon->GetPosition(sx, sy);
	if (sx >= left && nx < 0)
		SetState(BAT_STATE_FLY_LEFT);
	else if (sx >= left && nx > 0)
		SetState(BAT_STATE_FLY_RIGHT);

	if (state != BAT_STATE_INVISIBLE || state != BAT_STATE_HANGING)
	{
		x += dx;
		y += dy;

		if (y > Height_Fly + BAT_DISTANCE_FLY)
		{
			y = Height_Fly + BAT_DISTANCE_FLY;
			vy = -vy;
		}
		if (y > Height_Fly - BAT_DISTANCE_FLY)
		{
			y = Height_Fly - BAT_DISTANCE_FLY;
			vy = -vy;
		}
	}


}

void CBat::Render()
{
	if (state != BAT_STATE_INVISIBLE)
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
		//vy = -BAT_FLYING_SPEED_Y;
		//nx = -1;
		break;
	case BAT_STATE_FLY_RIGHT:
		vx = BAT_FLYING_SPEED_X;
		//vy = -BAT_FLYING_SPEED_Y;
		//nx = -1;
		break;
	}
}

void CBat::SetHeightFly(float height_fly)
{
	Height_Fly = height_fly;
}
