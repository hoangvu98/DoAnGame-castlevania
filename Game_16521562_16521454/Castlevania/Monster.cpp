#include "Monster.h"
#include "Simon.h"
void CMonster::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
}

void CMonster::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	if (state != MONSTER_STATE_DISAPPEAR && state != MONSTER_STATE_DELETE)
	{
		if (GetHealth() <= 0)
		{
			CSimon* simon = CSimon::GetInstance();
			SetState(MONSTER_STATE_DISAPPEAR);
			int points = simon->GetScore();
			simon->SetScore(points + score);
			Time_HitEffect = GetTickCount();
		}
	}
}

void CMonster::Render()
{
	if (state == MONSTER_STATE_DISAPPEAR)
	{
		int now = GetTickCount();
		hiteffect->SetPosition(x, y);
		if (items != NULL)
			items->SetPosition(x + 5, y + 10);
		hiteffect->Render();
		if (now - Time_HitEffect >= FrameTime)
			SetState(MONSTER_STATE_DELETE);
	}
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
