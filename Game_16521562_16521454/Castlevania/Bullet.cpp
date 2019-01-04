#include "Bullet.h"



CBullet::CBullet()
{
	AddAnimation(19000);
	AddAnimation(19001);
	damage = 4;
}


CBullet::~CBullet()
{
}

void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	x += dx;
	y += dy;

	DebugOut(L"vx=%f\nvy=%f\n", vx, vy);
}

void CBullet::Render()
{
	if (state != BULLET_STATE_REFLECT)
	{
		if (nx < 0)
			animations[BULLET_ANI_LEFT]->Render(x, y);
		else animations[BULLET_ANI_RIGHT]->Render(x, y);
	}
}

void CBullet::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BULLET_BBOX_WIDTH;
	bottom = y + BULLET_BBOX_HEIGHT;
}

void CBullet::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BULLET_STATE_LEFT:
		vx = -BULLET_SPEED;
		nx = -1;
		break;
	case BULLET_STATE_RIGHT:
		vx = BULLET_SPEED;
		nx = 1;
		break;
	}
}

void CBullet::SetSpeed(float x1, float y1, float x2, float y2, int time)
{
	float v_x=(x2 - x1)/time;
	float v_y = (y2 - y1) / time;
	if (v_x <= 0)
		vx = -BULLET_SPEED;
	else
		vx = BULLET_SPEED;
	vy = vx * v_y / v_x;

}

void CBullet::SetState(float x1, float x2)
{
	if (x1 < x2)
		SetState(BULLET_STATE_RIGHT);
	else
		SetState(BULLET_STATE_LEFT);
}
