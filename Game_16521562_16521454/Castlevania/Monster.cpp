#include "Monster.h"
#include "Simon.h"
void CMonster::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
}

void CMonster::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	if (!IsInjure)
	{
		DWORD now = GetTickCount();
		if (now - time_injure > TIME_INJURE)
			IsInjure = true;
	}
	if (state != MONSTER_STATE_DISAPPEAR && state != MONSTER_STATE_DELETE)
	{
		if (GetHealth() <= 0)
		{
			CSimon* simon = CSimon::GetInstance();
			int points = simon->GetScore();
			simon->SetScore(points + score);
			SetState(MONSTER_STATE_DISAPPEAR);
		}
	}
	else if (state == MONSTER_STATE_DISAPPEAR)
	{
		CSimon* simon = CSimon::GetInstance();
		Chiteffect* hiteffect = new Chiteffect();
		hiteffect->SetPosition(x, y);
		hiteffect->SetState(HITEFFECT_STATE_DIE);
		CCells* cell = simon->map->GetCell();
		cell->InitCells(hiteffect);
		if (items != NULL)
		{
			items->SetPosition(x + 5, y + 10);
			cell->InitCells(items);
		}
		simon->map->SetCell(cell);
		SetState(MONSTER_STATE_DELETE);
	}
}
void CMonster::Render()
{
}
void CMonster::SetState(int state)
{
	CGameObject::SetState(state);
}

CMonster::CMonster()
{
	/*int random;
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
	}*/
}
