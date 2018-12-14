#include "Dracula.h"



void CDracula::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	head->Update(dt, coObjects);
	if (head->GetState() != HEAD_STATE_FLY)
	{
		SetState(DRACULA_STATE_IDLE);
		if (GetTickCount() - untouchable_start > DRACULA_UNTOUCHABLE_TIME && untouchable == true)
		{
			untouchable = false;
			untouchable_start = 0;
			wait = GetTickCount();
		}

		if (GetTickCount() - wait > DRACULA_WAIT_TIME)
		{
			attack = true;
			wait = 0;
		}

		if (attack == true)
		{
			StartAttacking(); 
			SetState(DRACULA_STATE_FIRE);
		}
		
		if (GetTickCount() - start_attack > DRACULA_ATTACKING_TIME)
		{
			SetState(DRACULA_STATE_INVISIBLE);
			attack = false;
			start_attack = 0;
		}
		if (start == true)
			StartUntouchable();
	}
}

void CDracula::Render()
{	
	if (state != DRACULA_STATE_INVISIBLE)
	{
		int ani;
		if (state == DRACULA_STATE_IDLE)
		{
			if (nx > 0) ani = DRACULA_ANI_IDLE_RIGHT;
			else ani = DRACULA_ANI_IDLE_LEFT;
		}
		else if (state == DRACULA_STATE_FIRE)
		{
			if (nx > 0) ani = DRACULA_ANI_FIRE_RIGHT;
			else ani = DRACULA_ANI_FIRE_LEFT;
			/*for (int i = 0; i < 3; i++)
				bullet[i]->Render();*/
		}
		if (untouchable == true)
		{
			if (alpha == 128) alpha = 100;
			else alpha = 128;
		}
		else alpha = 255;
		animations[ani]->Render(x, y, alpha);
	}
	head->Render();
}

void CDracula::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	
}

void CDracula::StartUntouchable()
{
	untouchable = true;
	untouchable_start = GetTickCount();
	start = false;
}

void CDracula::StartAttacking()
{
	start_attack = GetTickCount();
	//attack = false;
}

void CDracula::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case DRACULA_STATE_INVISIBLE:
		attack = false;
		break;
	}
}

CDracula::CDracula()
{
	health = 16;
	damage = 4;

	alpha = 255;

	start = true;
	
	head = new CHeadDracula();
	head->SetPosition(211.0f, 146.0f);
	head->SetState(HEAD_STATE_FLY);
	head->Setnx(-1);

	AddAnimation(240001);
	AddAnimation(240002);
	AddAnimation(240003);
	AddAnimation(240004);

	untouchable = 0;
}

CDracula::~CDracula()
{
}
