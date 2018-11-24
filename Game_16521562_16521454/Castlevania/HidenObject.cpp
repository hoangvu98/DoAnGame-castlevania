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
	else if (state == HIDENOBJECT_STATE_JUMP)
	{

	}
}

void CHidenObject::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}
