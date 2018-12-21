#include "Hunchback.h"
#include "HidenObject.h"
#include "Simon.h"
#include "debug.h"
CHunchback::CHunchback()
{
	damage = 4;
	health = 1;
	score = 500;
	AddAnimation(230001);
	AddAnimation(230002);
	AddAnimation(230003);
	AddAnimation(230004);
	IsJump = false;
}

void CHunchback::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + HUNCHBACK_BBOX_WIDTH;
	bottom = y + HUNCHBACK_BBOX_HEIGHT;
}

void CHunchback::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMonster::Update(dt, coObjects);
	if (state != HUNCHBACK_STATE_FLY_RIGHT && state != HUNCHBACK_STATE_FLY_LEFT)
		vy += HUNCHBACK_GRAVITY;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	bool test = true;
	DWORD now = GetTickCount();
	CalcPotentialCollisions(coObjects, coEvents);
	FilterCollisionImmediately(coEvents, coEventsResult);
	if (state == HUNCHBACK_STATE_IDLE)
	{
		if (now - time_stop > 300 && IsJump)
		{
			CSimon* simon = CSimon::GetInstance();
			if (simon->nx > 0)
			{
				if (simon->x < x)
				{
					nx = -1;
					vy = -HUNCHBACK_JUMP_SPEED / 4;
					vx = -HUNCHBACK_FLYING_SPEED * 2;
				}
				else
				{
					nx = 1;//nhay lon
					vy = -HUNCHBACK_JUMP_SPEED;
					vx = HUNCHBACK_FLYING_SPEED;
				}
			}
			else
			{
				if (simon->x > x)
				{
					nx = 1;
					vy = -HUNCHBACK_JUMP_SPEED / 4;
					vx = HUNCHBACK_FLYING_SPEED * 2;
				}
				else
				{
					nx = -1; // nhay lon
					vy = -HUNCHBACK_JUMP_SPEED;
					vx = -HUNCHBACK_FLYING_SPEED;
				}
			}
			SetState(HUNCHBACK_STATE_JUMP);
			IsJump = false;
		}
	}
	CGameObject::Update(dt, coObjects);
	if (state == HUNCHBACK_STATE_IDLE || state == HUNCHBACK_STATE_JUMP)
	{
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CHidenObject *> (e->obj))
			{
				CHidenObject *hidenobject = dynamic_cast<CHidenObject *>(e->obj);
				if (hidenobject->state == HIDENOBJECT_STATE_NORMAL)
				{
					if (state == HUNCHBACK_STATE_IDLE)
					{
						vy = -HUNCHBACK_GRAVITY * 2;
						y += vy * dt;
						test = false;
					}
					else if (state == HUNCHBACK_STATE_JUMP)
					{
						if (nx < 0)
							if (x <= hidenobject->x - 10)
								SetState(HUNCHBACK_STATE_IDLE);
					}
				}
			}
		}
	}
	if (state == HUNCHBACK_STATE_IDLE || state == HUNCHBACK_STATE_JUMP)
	{
		coEventsResult.clear();
		if (coEvents.size() != 0)
		{
			coEventsResult.clear();
			float min_tx, min_ty, nx = 0, ny;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<CHidenObject *> (e->obj))
				{
					CHidenObject *hidenobject = dynamic_cast<CHidenObject *>(e->obj);
					if (hidenobject->state == HIDENOBJECT_STATE_NORMAL)
					{
						if (now - time_stop > 350 && state == HUNCHBACK_STATE_JUMP)
						{
							if (ny != 0)
								SetState(HUNCHBACK_STATE_IDLE);
						}

						if (state == HUNCHBACK_STATE_IDLE)
						{
							if (test == true)
							{
								y += min_ty * dy + ny * 0.4f;
								test = false;
							}
							if (!IsJump)
							{
								time_stop = GetTickCount();
								IsJump = true;
							}
						}
					}
				}
			}
		}
	}
	if (test)
	{
		y += dy;
		test = true;
	}
	x += dx;
	DebugOut(L"vx=%f\n", vx);


	//if (state != HUNCHBACK_STATE_IDLE && now - time_stop > 1500)
/*	{
		if (nx > 0)
			SetState(HUNCHBACK_STATE_FLY_RIGHT);
		else
			SetState(HUNCHBACK_STATE_FLY_LEFT);
	}
	else*/
	if (now - time_stop > 1000 &&
		(state == HUNCHBACK_STATE_FLY_RIGHT || state == HUNCHBACK_STATE_FLY_LEFT))
		SetState(HUNCHBACK_STATE_IDLE);
}

void CHunchback::Render()
{
	int ani;
	if (state != MONSTER_STATE_DISAPPEAR && state != MONSTER_STATE_DELETE)
	{
		if (state == HUNCHBACK_STATE_JUMP)
		{
			if (nx > 0)
				ani = HUNCHBACK_ANI_JUMP_RIGHT;
			else
				ani = HUNCHBACK_ANI_JUMP_LEFT;
		}
		else
		{
			if (nx > 0)
				ani = HUNCHBACK_ANI_IDLE_RIGHT;
			else
				ani = HUNCHBACK_ANI_IDLE_LEFT;
		}
		animations[ani]->Render(x, y);
	}
	//RenderBoundingBox(200);
}

void CHunchback::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case HUNCHBACK_STATE_FLY_LEFT:
		vx = -HUNCHBACK_FLYING_SPEED;
		vy = 0;
		time_stop = GetTickCount();
		break;
	case HUNCHBACK_STATE_FLY_RIGHT:
		vx = HUNCHBACK_FLYING_SPEED;
		vy = 0;
		time_stop = GetTickCount();
		break;
	case HUNCHBACK_STATE_IDLE:
		vx = 0;
		break;
	}
}