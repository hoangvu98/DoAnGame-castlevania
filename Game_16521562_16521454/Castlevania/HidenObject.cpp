#include "HidenObject.h"

void CHidenObject::SetState(int state)
{
	CGameObject::SetState(state);
}

void CHidenObject::Render()
{
	if (state == HIDENOBJECT_STATE_NORMAL)
	{
		RenderBoundingBox(200);
	}
	else if (state == HIDENOBJECT_STATE_STAIR_UP)
	{
		RenderBoundingBox(200);
	}
	else if (state == HIDENOBJECT_STATE_STAIR_DOWN)
	{
		RenderBoundingBox(200);
	}
	else if (state == HIDENOBJECT_STATE_STAIR_UP_DOWN)
	{
		RenderBoundingBox(200);
	}
	else if (state == HIDENOBJECT_STATE_JUMP)
	{
		RenderBoundingBox(200);
	}
	else if (state == HIDENOBJECT_STATE_DOOR)
	{
		//RenderBoundingBox(200);
	}
	else if (state == HIDENOBJECT_STATE_CASTLE_GATE)
	{
		animations[0]->Render(x, y);
	}
	else if (state == HIDENOBJECT_STATE_HEAD)
	{
		RenderBoundingBox(200);
	}
}

void CHidenObject::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

CHidenObject::CHidenObject()
{
	AddAnimation(21001);
}

CHidenObject::CHidenObject(float width, float height)
{
	SetSize(width, height);
	AddAnimation(21001);
}

CHidenObject::CHidenObject(float width, float height, float stair_x, float stair_y)
{
	SetSize(width, height);
	AddAnimation(21001);
	SetStair_XY(stair_x, stair_y);
}
