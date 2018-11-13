#include "HidenObject.h"

void CHidenObject::SetState(int state)
{
	CGameObject::SetState(state);
}

void CHidenObject::Render()
{
	if (state == HIDENOBJECT_STATE_NORMAL)
	{////RenderBoundingBox(100);
	//animations[0]->Render(x, y);
	}
	else
	{
		RenderBoundingBox(200);
		//animations[0]->Render(x, y);
	}
}

void CHidenObject::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}
