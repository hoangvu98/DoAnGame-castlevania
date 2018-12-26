#include "Candle.h"
#include "Map.h"
#include "Simon.h"


void CCandle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	if (state == CANDLE_STATE_DISAPPEAR)
	{
		Chiteffect *hiteffect = new Chiteffect();
		hiteffect->SetPosition(x, y);
		hiteffect->SetState(HITEFFECT_STATE_NORMAL);
		items->SetPosition(x + 5, y + 10);
		CSimon* simon = CSimon::GetInstance();
		CCells* cell = simon->map->GetCell();
		cell->InitCells(hiteffect);
		cell->InitCells(items);
		simon->map->SetCell(cell);
		SetState(CANDLE_STATE_DELETE);
	}
}

void CCandle::Render()
{
	if (state == CANDLE_STATE_NORMAL)
	{
		if (size == BIG_CANDLE)
			animations[0]->Render(x, y);
		else if (size == SMALL_CANDLE)
			animations[1]->Render(x, y);
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
}

CCandle::CCandle(int size)
{

	this->size = size;
	AddAnimation(11111);
	AddAnimation(11112);
	int random;
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


