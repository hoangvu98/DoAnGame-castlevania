#include "Fishman.h"

CFishman::CFishman()
{
	CMonster::CMonster();
	health = 1;
	damage = 1;
	AddAnimation(18000);
	AddAnimation(18001);
	AddAnimation(18002);
	AddAnimation(18003);
	AddAnimation(18004);
	AddAnimation(18005);
	bullet = new CBullet();
	i = 0;
	j = 0;
	fire = false;
	int random;
	//srand(time(NULL));
	random = rand() % 10;
	if (random <= 1)
		items = new CHeart(HEART_BIG);
	else if (random <= 3)
		items = new CHeart(HEART_SMALL);
	else
		items = NULL;
}

void CFishman::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	if (state == FISHMAN_STATE_FIRE)
	{
		right = x + FISHMAN_BBOX_FIRE_WIDTH;
		bottom = y + FISHMAN_BBOX_FIRE_HEIGHT;
	}
	else
	{
		right = x + FISHMAN_BBOX_WIDTH;
		bottom = y + FISHMAN_BBOX_HEIGHT;
	}
}

void CFishman::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CMonster::Update(dt, coObjects);
	//CGameObject::Update(dt, coObjects);
	vy += FISHMAN_GRAVITY * dt;
	if (state != FISHMAN_STATE_DISAPEAR && state != MONSTER_STATE_DELETE)
	{		
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;
		coEventsResult.clear();
		CalcPotentialCollisions(coObjects, coEvents);

		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
			x += dx;
			x += min_tx * dx + nx * 0.4f;
			if (ny < 0)
			{
				y += min_ty * dy + ny * 0.4f;
				if (fire == false)
				{
					if (this->nx < 0 && this->x >= FISHMAN_TURN) SetState(FISHMAN_STATE_WALKING_LEFT);
					else SetState(FISHMAN_STATE_WALKING_RIGHT);
					SetPosition(this->x, this->y - OFFSET);
				}
				if (i >= 25 && fire == false)
				{
					SetState(FISHMAN_STATE_FIRE);
					
					bullet->SetPosition(x, y);
					bullet->Setnx(this->nx);
					if (this->nx > 0) bullet->SetState(BULLET_STATE_RIGHT);
					else bullet->SetState(BULLET_STATE_LEFT);
					i = 0;
				}
				else if (fire == false) i++;
				if (fire == true)
				{
					if (j >= 50)
					{
						fire = false;
						
						j = 0;
					}
					else
					{
						j++;
						bullet->Update(dt, coObjects);
					}
				}
			}
			else
				y += dy;
		}
	}
	DebugOut(L"state %d\n", state);
}

void CFishman::Render()
{
	int ani;
	//if (state != MONSTER_STATE_DISAPPEAR)
	//{
	//	if (vx == 0)
	//	{
	//		if (nx < 0) ani = FISHMAN_ANI_FIRE_LEFT;
	//		else ani = FISHMAN_ANI_FIRE_RIGHT;
	//		Time_Fishman_HitEffect = GetTickCount();
	//		animations[ani]->Render(x, y);
	//		bullet->Render();
	//	}
	//	else
	//	{
	//		if (nx < 0) ani = FISHMAN_ANI_WALKING_LEFT;
	//		else ani = FISHMAN_ANI_WALKING_RIGHT;
	//		animations[ani]->Render(x, y);
	//		Time_Fishman_HitEffect = GetTickCount();
	//	}

	//	if (vy < 0)
	//	{
	//		if (nx < 0) ani = FISHMAN_ANI_JUMP_LEFT;
	//		else ani = FISHMAN_ANI_JUMP_RIGHT;
	//		animations[ani]->Render(x, y);
	//		Time_Fishman_HitEffect = GetTickCount();
	//	}
	//}
	//else /*if (state == MONSTER_STATE_DISAPPEAR)*/
	//{
	//	int now = GetTickCount();
	//	hiteffect->SetPosition(x, y);
	//	if (items != NULL)
	//		items->SetPosition(x + 5, y + 10);
	//	hiteffect->Render();
	//	if (now - Time_Fishman_HitEffect >= FRAMETIME)
	//		SetState(MONSTER_STATE_DELETE);
	//}
	if (state == FISHMAN_STATE_FIRE)
	{
		if (nx < 0) ani = FISHMAN_ANI_FIRE_LEFT;
		else ani = FISHMAN_ANI_FIRE_RIGHT;
		Time_Fishman_HitEffect = GetTickCount();
		animations[ani]->Render(x, y);
		bullet->Render();
	}
	else if (state == FISHMAN_STATE_WALKING_LEFT)
	{
		ani = FISHMAN_ANI_WALKING_LEFT;
		animations[ani]->Render(x, y);
		Time_Fishman_HitEffect = GetTickCount();
	}
	else if (state == FISHMAN_STATE_WALKING_RIGHT)
	{
		ani = FISHMAN_ANI_WALKING_RIGHT;
		animations[ani]->Render(x, y);
		Time_Fishman_HitEffect = GetTickCount();
	}
	else if (state == FISHMAN_STATE_JUMP)
	{
		if (nx < 0) ani = FISHMAN_ANI_JUMP_LEFT;
		else ani = FISHMAN_ANI_JUMP_RIGHT;
		Time_Fishman_HitEffect = GetTickCount();
		animations[ani]->Render(x, y);
		bullet->Render();
	}
	else if (state == MONSTER_STATE_DISAPPEAR)
	{
		int now = GetTickCount();
		hiteffect->SetPosition(x, y);
		if (items != NULL)
		items->SetPosition(x + 5, y + 10);
		hiteffect->Render();
		if (now - Time_Fishman_HitEffect >= FRAMETIME)
			SetState(MONSTER_STATE_DELETE);
	}
}

void CFishman::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FISHMAN_STATE_WALKING_RIGHT:
		vx = FISHMAN_WALKING_SPEED;
		nx = 1;
		break;
	case FISHMAN_STATE_WALKING_LEFT:
		
		vx = -FISHMAN_WALKING_SPEED;
		nx = -1;
		break;
	case FISHMAN_STATE_JUMP:
		vy = -FISHMAN_JUMP_SPEED_Y;
		break;
	case FISHMAN_STATE_FIRE:
		vx = 0;
		fire = true;
		break;
	}
}
