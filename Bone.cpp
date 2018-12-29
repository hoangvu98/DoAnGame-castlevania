#include "Bone.h"



CBone::CBone()
{
	AddAnimation(220001);//left
	AddAnimation(220002);//right
	fall = false;
	nx = 1;
	damage = 4;
}

void CBone::InitHeight()
{
	height = y - HEIGHT;
}

void CBone::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (y >= height && fall == false)
		vy = -BONE_SPEED_Y;
	else
	{
		vy += BONE_GRAVITY * dt;
		fall = true;
	}
	if (nx > 0)
		vx = BONE_SPEED_X;
	else vx = -BONE_SPEED_X;
	CGameObject::Update(dt);
	this->x += dx;
	this->y += dy;
}

void CBone::Render()
{
	if (nx < 0)
		animations[BONE_ANI_FLY_LEFT]->Render(x, y);
	else if (nx > 0)
		animations[BONE_ANI_FLY_RIGHT]->Render(x, y);
}


void CBone::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BONE_BBOX_WIDTH;
	bottom = y + BONE_BBOX_HEIGHT;
}

CBone::~CBone()
{
}
