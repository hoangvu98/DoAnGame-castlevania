#include "Candle.h"



void CCandle::Render()
{
	if (state == CANDLE_STATE_NORMAL)
	{
		if (size == BIG_CANDLE)
			animations[0]->Render(x, y);
		else if (size == SMALL_CANDLE)
			animations[1]->Render(x, y);
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
	right = x + BIG_CANDLE_BBOX_WIDTH;
	bottom = y + BIG_CANDLE_BBOX_HEIGHT;
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

CCandle::CCandle(int size)
{
	
	this->size = size;
	AddAnimation(11111);
	AddAnimation(11112);
	hiteffect = new Chiteffect();
	int random;
	//srand(time(NULL));
	random = rand() % 10;
	int size_bag;
	if (random <= 8)
		size_bag = MONEY_BAG_SMALL;
	else
		size_bag = MONEY_BAG_BIG;
	if (random <= 3)
	{
		//srand(time(NULL));
		random = rand() % 10;
		if (random <= 2) items = new CHeart(HEART_SMALL);
		else items = new CHeart(HEART_BIG);
		
	}
	else
	{
		//srand(time(NULL));
		random = rand() % 10;
		if (random <= 2) items = new CMoneyBag(size_bag, MONEY_BAG_RED);
		else if (random <= 3) items = new CMoneyBag(size_bag, MONEY_BAG_BLUE);
		else items = new CMoneyBag(size_bag, MONEY_BAG_WHITE);
		
	}
}

CCandle::CCandle(int size, int item)
{
	this->size = size;
	AddAnimation(11111);
	AddAnimation(11112);
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
	case MONEY_BAG:
		items = new CMoneyBag(MONEY_BAG_SMALL, MONEY_BAG_RED);
	case AXE:
		items = new CAxe();
		break;
	case BOOMERANG:
		items = new CBoomerang();
		break;
	case HOLLYWATER:
		items = new CHollyWater();
		break;
	}
}


