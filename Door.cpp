#include "Door.h"
void CDoor::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	top = y;
	bottom = y + DOOR_HEIGHT;
	if (state == DOOR_STATE_NORMAL)
	{
		right = x + DOOR_WIDTH;
		left = x;
	}
	else
	{
		left = x-10.0f;
		right = x + DOOR_OPEN_WIDTH;
	}
}

void CDoor::Render()
{
	if (IsHiden == false)
	{
		if (state == DOOR_STATE_NORMAL)
			animations[DOOR_ANI_NORMAL]->Render(x, y);
		else if (state == DOOR_STATE_OPEN)
		{
			DWORD now = GetTickCount();
			if(now-time_open<150)
				animations[DOOR_ANI_OPEN_1]->Render(x, y);
			else
				animations[DOOR_ANI_OPEN_2]->Render(x, y);
		}
		else if (state == DOOR_STATE_CLOSE)
		{
			DWORD now = GetTickCount();
			if (now - time_open < 150)
				animations[DOOR_ANI_OPEN_2]->Render(x, y);
			else
				animations[DOOR_ANI_OPEN_1]->Render(x, y);
		}
	}	
	//RenderBoundingBox(200);
}

void CDoor::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case DOOR_STATE_OPEN:
		time_open = GetTickCount();
		break;
	case DOOR_STATE_CLOSE:
		time_open = GetTickCount();
		break;
	}
}

CDoor::CDoor()
{
	AddAnimation(11000);
	AddAnimation(11001);
	AddAnimation(11002);
	IsStair = false;
	IsGo = true;
	stop = false;
	i = 0;
	nx = 1;
	IsAuto = true;
}
