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
	if (state == DOOR_STATE_CLOSE)
		animations[DOOR_ANI_CLOSE]->Render(x, y);
	else if (state == DOOR_STATE_OPEN)
	{
		if (stop == false)
		{
			if (i < 8)
			{
				animations[DOOR_ANI_OPEN_1]->Render(x, y);
				//DebugOut(L"current frame: %d\n", animations[DOOR_ANI_OPEN_1]->GetCureentFrame());
				i++;
				//DebugOut(L"i = %d\n", i);
			}
			else
			{
				i = 0;
				stop = true;
			}
		}
		else
			animations[DOOR_ANI_OPEN_2]->Render(x, y);
	}
}

CDoor::CDoor()
{
	AddAnimation(11000);
	AddAnimation(11001);
	AddAnimation(11002);
	stop = false;
	i = 0;
}
