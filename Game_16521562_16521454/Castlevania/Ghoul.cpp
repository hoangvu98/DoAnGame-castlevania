#include "Ghoul.h"
#include "InputImage.h"
#include "debug.h"

void CGhoul::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + GHOUL_BBOX_WIDTH;
	bottom = y + GHOUL_BBOX_HEIGHT;
}

void CGhoul::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (state == GHOUL_STATE_LEFT || state == GHOUL_STATE_RIGHT)
	{
		x += dx;
		y += dy;
	}
	
}

void CGhoul::Render()
{
	int ani;
	if (state == GHOUL_STATE_LEFT)
	{
		ani = GHOUL_ANI_LEFT;
		animations[ani]->Render(x, y);
	}
	else if (state == GHOUL_STATE_RIGHT)
	{
		ani = GHOUL_ANI_RIGHT;
		animations[ani]->Render(x, y);
	}
	else if (state == GHOUL_STATE_DISAPPEAR)
	{
	int now = GetTickCount();
	hiteffect->SetPosition(x, y);
	items->SetPosition(x + 5, y + 10);
	hiteffect->Render();
	if (now - Time >= FrameTime)
		SetState(GHOUL_STATE_DELETE);
	}
	//RenderBoundingBox(200);
}

void CGhoul::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GHOUL_STATE_LEFT:
		vx = -GHOUL_WALKING_SPEED;
		nx = -1;
		break;
	case GHOUL_STATE_RIGHT:
		vx = GHOUL_WALKING_SPEED;
		nx = 1;
		break;
	case GHOUL_STATE_DISAPPEAR:
		Time = GetTickCount();
		break;
	}
}
CGhoul::CGhoul()
{
	hiteffect = new Chiteffect();
	AddAnimation(10000);
	AddAnimation(10001);
	int random;
	srand(time(NULL));
	random = rand() % 2;
	switch (random)
	{
	case 0:
		items = new CDagger();
		break;
	case 1:
		random = rand() % 2;
		switch (random)
		{
		case 0:
			items = new CHeart(HEART_BIG);
			break;
		case 1:
			items = new CHeart(HEART_SMALL);
			break;
		}
		break;
	}
}
