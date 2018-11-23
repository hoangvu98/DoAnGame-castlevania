#include "Candle.h"



void CCandle::Render()
{
	if (state == CANDLE_STATE_NORMAL)
	{
		animations[0]->Render(x, y);
	}
	else if (state == CANDLE_STATE_DISAPPEAR)
	{
		int now = GetTickCount();
		hiteffect->SetPosition(x, y);
		//item->SetPosition(x+5, y+10);
		items->SetPosition(x + 5, y + 10);
		hiteffect->Render();
		if (now - Time >= FrameTime)
			SetState(CANDLE_STATE_DELETE);
	}
}

void CCandle::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + CANDLE_BBOX_WIDTH;
	bottom = y + CANDLE_BBOX_HEIGHT;
}

void CCandle::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case CANDLE_STATE_DISAPPEAR:
		Time = GetTickCount();
		break;
	}
}

CCandle::CCandle()
{
	
		AddAnimation(100);
		hiteffect = new Chiteffect();
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

CCandle::CCandle(int item)
{
	AddAnimation(100);
	hiteffect = new Chiteffect();
	int random = rand() % 2;
	switch (item)
	{

	case DAGGER:
		items = new CDagger();
		break;
	case HEART:
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
	case WHIP_UPDATE:
		items = new CWhipUpdate();
		break;
	}
}


