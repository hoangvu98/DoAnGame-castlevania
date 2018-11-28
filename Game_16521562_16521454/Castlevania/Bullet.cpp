#include "Bullet.h"



CBullet::CBullet()
{
	AddAnimation(19000);
	AddAnimation(19001);
}


CBullet::~CBullet()
{
}

void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (nx < 0) SetState(BULLET_STATE_LEFT);
	else SetState(BULLET_STATE_RIGHT);
	x += dx;
}

void CBullet::Render()
{
	if (nx < 0)
		animations[BULLET_ANI_LEFT]->Render(x, y);
	else animations[BULLET_ANI_RIGHT]->Render(x, y);
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
		break;
	case BULLET_STATE_RIGHT:
		vx = BULLET_SPEED;
		break;
	}
}
