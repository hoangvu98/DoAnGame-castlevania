#include "Items.h"
#include <fstream>
#include "InputImage.h"
using namespace std;


CItems::CItems()
{

}


CItems::~CItems()
{
}

void CItems::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy += ITEM_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0)
		y += dy;
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
	}
}

void CDagger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == ITEM_STATE_ITEM)
		CItems::Update(dt, coObjects);
	else
	{
		CGameObject::Update(dt);
		//vy += ITEM_GRAVITY * dt;
		x += dx;
		y += dy;
	}
}


void CDagger::Render()
{
	if (state == ITEM_STATE_WEAPON_LEFT)
	{
		animations[1]->Render(x, y);
	}
	else if (state != ITEM_STATE_DELETE)
	{
		animations[0]->Render(x, y);
	}
}

void CDagger::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + DAGGER_BBOX_WIDTH;
	bottom = y + DAGGER_BBOX_HEIGHT;
}
void CDagger::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ITEM_STATE_WEAPON_LEFT:
		vx = -SPEED_DAGGER;
		//vy = -0.1f;
		break;
	case ITEM_STATE_WEAPON_RIGHT:
		vx = SPEED_DAGGER;
		//vy = -0.1f;
	}
}
void CHeart::Render()
{
	if (state != ITEM_STATE_DELETE)
	{
		switch (size)
		{
		case HEART_BIG:
			animations[1]->Render(x, y);
			break;
		case HEART_SMALL:
			animations[0]->Render(x, y);
			break;
		}
	}
}

void CHeart::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	switch (size)
	{
	case HEART_BIG:
		right = x + HEART_BBOX_BIG_WIDTH;
		bottom = y + HEART_BBOX_BIG_HEIGHT;
		break;
	case HEART_SMALL:
		right = x + HEART_BBOX_SMALL_WIDTH;
		bottom = y + HEART_BBOX_SMALL_HEIGHT;
		break;
	}
}
void CWhipUpdate::Render()
{
	if (state != ITEM_STATE_DELETE)
	{
		animations[0]->Render(x, y);
	}
}

void CWhipUpdate::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + WHIP_UPDATE_BBOX_WIDTH;
	bottom = y + WHIP_UPDATE_BBOX_HEIGHT;
}

CMoneyBag::CMoneyBag(int size, int state)
{
	this->state = state; 
	this->size = size;
	AddAnimation(13001); 
	AddAnimation(13002); 
	AddAnimation(13003);
}

void CMoneyBag::Render()
{
	if (state != ITEM_STATE_DELETE)
	{
		animations[state]->Render(x, y);
	}
}

void CMoneyBag::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + MONEY_BAG_BBOX_WIDTH;
	bottom = y + MONEY_BAG_BBOX_HEIGHT;
}

void CAxe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == ITEM_STATE_ITEM)
		CItems::Update(dt, coObjects);
	else
	{
		CGameObject::Update(dt);
		vy += AXE_GRAVITY * dt;
		x += dx;
		y += dy;
	}
}

void CAxe::Render()
{
	if (state == ITEM_STATE_ITEM)
	{
		animations[0]->Render(x, y);
	}
	else if (state != ITEM_STATE_DELETE)
	{
		animations[1]->Render(x, y);
	}
}

void CAxe::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + AXE_BBOX_WIDTH;
	bottom = y + AXE_BBOX_HEIGHT;
}

void CAxe::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ITEM_STATE_WEAPON_LEFT:
		vx = -SPEED_AXE_X;
		vy = -SPEED_AXE_Y;
		break;
	case ITEM_STATE_WEAPON_RIGHT:
		vx = SPEED_AXE_X;
		vy = -SPEED_AXE_Y;
	}
}
