#include "Bone.h"
#include "debug.h"


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
	CGameObject::Update(dt);
	if (state == BONE_STATE_NORMAL)
	{
		vy += BONE_GRAVITY;
		this->x += dx;
		this->y += dy;
	}
	if (y >= 190.0f)
		SetState(BONE_STATE_DELETE);
	DebugOut(L"x=%f\ny=%f\n",x,y);
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
