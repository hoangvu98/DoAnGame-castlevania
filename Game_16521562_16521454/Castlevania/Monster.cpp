#include "Monster.h"

void CMonster::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
}

void CMonster::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
}

void CMonster::Render()
{
}

void CMonster::SetState(int state)
{
}

CMonster::CMonster()
{
	hiteffect = new Chiteffect();
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
