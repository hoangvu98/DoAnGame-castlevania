#include "Door.h"

void CDoor::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + DOOR_WIDTH;
	bottom = y + DOOR_HEIGHT;
}

void CDoor::Render()
{
	if (IsHiden == false)
	{
		if (state == DOOR_STATE_CLOSE)
			animations[DOOR_ANI_CLOSE]->Render(x, y);
		else if (state == DOOR_STATE_OPEN)
		{
			if (stop == false)
				animations[DOOR_ANI_OPEN_1]->Render(x, y);
			else
				animations[DOOR_ANI_OPEN_2]->Render(x, y);
		}
	}
		RenderBoundingBox(200);
}

CDoor::CDoor()
{
	AddAnimation(11000);
	AddAnimation(11001);
	AddAnimation(11002);
	stop = false;
	i = 0;
	nx = 1;
}
