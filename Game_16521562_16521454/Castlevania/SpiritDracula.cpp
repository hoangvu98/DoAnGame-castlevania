#include "SpiritDracula.h"
#include "Simon.h"
#include "debug.h"
#include "Candle.h"
#include "HidenObject.h"
#include <math.h>

CSpiritDracula * CSpiritDracula::__instance = NULL;
void CSpiritDracula::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CSimon *simon = CSimon::GetInstance();
	int i;
	//CGameObject::Update(dt);
	CMonster::Update(dt, coObjects);
	//vy += SPIRITDRACULA_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	CalcPotentialCollisions(coObjects, coEvents);
	
	///tham khao ban
	/*if (state == SPIRITDRACULA_STATE_FIRE)
	{
		if (Bullet)
		{
			CBullet* bullet = new CBullet();
			bullet->SetPosition(x, y);
			bullet->SetSpeed(x, y, simon->x, simon->y, 800);
			bullet->SetState(x, simon->x);
			CCells* cell = simon->map->GetCell();
			cell->InitCells(bullet);
			simon->map->SetCell(cell);
			Bullet = false;
		}
	}*/
	/*else*/
	/*{
		Bullet = true;
	}*/

	if (simon->x < this->x + SPIRITDRACULA_OFFSET) this->nx = -1;
	else this->nx = 1;

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT e = coEvents[i];
		if (dynamic_cast<CCandle *> (e->obj))
		{
			coEvents.erase(coEvents.begin() + i);
			i--;
		}
		
	}

	if (isAddHeadToCell == false)
	{
		CCells *cells = simon->map->GetCell();
		cells->InitCells(head);
		simon->map->SetCell(cells);
		isAddHeadToCell = true;

	}
	if (state == SPIRITDRACULA_STATE_IDLE)
	{
		if (abs(simon->x - this->x + SPIRITDRACULA_OFFSET) > DISTANCE1 && abs(simon->x - this->x + SPIRITDRACULA_OFFSET) < DISTANCE2 &&
			fire == false /*&& state == SPIRITDRACULA_STATE_IDLE*/)
		{
			fire = true;
			resetpos = true;
			
		}

		if (fire == false)
		{
			if (startwait1 == true)
				StartWait(startwait1, wait_start1);

			if (GetTickCount() - wait_start1 > SPIRITDRACULA_WAIT_TIME)
			{
				SetState(SPIRITDRACULA_STATE_JUMP);
				wait_start1 = 0;
			}
		}
		else
		{
			isAddBulletToCell = true;
			if (this->nx < 0)
			{
				for (i = 0; i < 3; i++)
				{
					bullets[i]->SetPosition(x + BULLET_POSITION_X, y /*+ BULLET_POSITION_Y*/);
					bullets[i]->Setnx(-1);
				}

				bullets[0]->SetSpeed(x + BULLET_POSITION_X, y /*+ BULLET_POSITION_Y*/,
					simon->x + 5.0f, simon->y, 800);
				bullets[1]->SetSpeed(x + BULLET_POSITION_X, y /*+ BULLET_POSITION_Y*/,
					simon->x + 5.0f, simon->y - 8.0f, 800);
				bullets[2]->SetSpeed(x + BULLET_POSITION_X, y /*+ BULLET_POSITION_Y*/,
					simon->x + 5.0f, simon->y + 8.0f, 800);
			}
			else if (this->nx > 0)
			{
				for (i = 0; i < 3; i++)
				{
					bullets[i]->SetPosition(x + BULLET_POSITION_X1, y /*+ BULLET_POSITION_Y*/);
					bullets[i]->Setnx(1);
				}

				bullets[0]->SetSpeed(x + BULLET_POSITION_X1, y /*+ BULLET_POSITION_Y*/,
					simon->x + 5.0f, simon->y, 800);
				bullets[1]->SetSpeed(x + BULLET_POSITION_X1, y/* + BULLET_POSITION_Y*/,
					simon->x + 5.0f, simon->y - 8.0f, 800);
				bullets[2]->SetSpeed(x + BULLET_POSITION_X1, y /*+ BULLET_POSITION_Y*/,
					simon->x + 5.0f, simon->y + 8.0f, 800);
			}

			if (startwait6 == true)
				StartWait(startwait6, wait_start6);

			if (GetTickCount() - wait_start6 > SPIRITDRACULA_WAIT_TIME)
			{
				SetState(SPIRITDRACULA_STATE_FIRE);
				if (isAddBulletToCell)
				{
					CCells* cell = simon->map->GetCell();
					for (int i = 0; i < 3; i++)
						cell->InitCells(bullets[i]);
					simon->map->SetCell(cell);
					isAddBulletToCell = false;
				}
				wait_start6 = 0;
			}
		}
	}

	if (this->y < height)
	{
		SetState(SPIRITDRACULA_STATE_FALL);
		vy += SPIRITDRACULA_GRAVITY * dt;
		reset = true;
	}

	if (fire == true)
	{
		if (startwait7 == true)
			StartWait(startwait7, wait_start7);

		/*for (int i = 0; i < 3; i++)
			bullets[i]->Update(dt, coObjects);*/

		if (GetTickCount() - wait_start7 > SPIRITDRACULA_FIRE_TIME)
		{
			SetState(SPIRITDRACULA_STATE_IDLE);
			vy += SPIRITDRACULA_GRAVITY * dt;
			reset = true;
			wait_start7 = 0;
		}
		
	}

	if (nx < 0)
	{
		head->SetPosition(x + HEAD_POSITION_X, y);
		head->SetSize(HEAD_WIDTH, HEAD_HEIGHT);
		//head->SetState(HIDENOBJECT_STATE_HEAD);
	}
	else
	{
		head->SetPosition(x + HEAD_POSITION_X1, y);
		head->SetSize(HEAD_WIDTH, HEAD_HEIGHT);
		//head->SetState(HIDENOBJECT_STATE_HEAD);
	}

	bool test = true;
	if (coEvents.size() != 0)
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		//if (ny != 0) vy = 0;
		if (nx != 0) vx = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CHidenObject *>(e->obj))
			{
				CHidenObject *hobj = dynamic_cast<CHidenObject *>(e->obj);
				if (hobj->GetState() == HIDENOBJECT_STATE_NORMAL)
				{
					this->x += min_tx * dx + nx * 0.4f;
					this->y += min_ty * dy + ny * 0.4f;
					test = false;				
				}
			}
		}
	}
	
	if (test == true)
	{
		x += dx;
		y += dy;
	}
	
	if (reset == true)
		Reset();
	/*DebugOut(L"state %d\n", state);
	DebugOut(L"fire %d\n", fire);*/
}

void CSpiritDracula::Render()
{
	int ani;
	if (state != MONSTER_STATE_DISAPPEAR && state != MONSTER_STATE_DELETE)
	{
		if (state == SPIRITDRACULA_STATE_IDLE)
		{
			if (nx > 0) ani = SPIRITDRACULA_ANI_IDLE_RIGHT;
			else ani = SPIRITDRACULA_ANI_IDLE_LEFT;

		}
		else if (state == SPIRITDRACULA_STATE_JUMP)
		{
			if (nx > 0) ani = SPIRITDRACULA_ANI_PRE_JUMP_RIGHT;
			else ani = SPIRITDRACULA_ANI_PRE_JUMP_LEFT;

			if (startwait2 == true)
				StartWait(startwait2, wait_start2);
			if (GetTickCount() - wait_start2 > SPIRITDRACULA_PRE_JUMP_TIME)
			{
				if (nx > 0) ani = SPIRITDRACULA_ANI_JUMP_RIGHT;
				else ani = SPIRITDRACULA_ANI_JUMP_LEFT;

				wait_start2 = 0;

				if (startwait3 == true)
					StartWait(startwait3, wait_start3);

				if (GetTickCount() - wait_start3 > SPIRITDRACULA_JUMP_TIME)
				{
					if (nx > 0) ani = SPIRITDRACULA_ANI_LANDING_AND_FLY_RIGHT;
					else ani = SPIRITDRACULA_ANI_LANDING_AND_FLY_LEFT;

					wait_start3 = 0;
				}
			}
		}
		else if (state == SPIRITDRACULA_STATE_FALL)
		{
			if (nx > 0) ani = SPIRITDRACULA_ANI_JUMP_RIGHT;
			else ani = SPIRITDRACULA_ANI_JUMP_LEFT;

			if (startwait4 == true)
				StartWait(startwait4, wait_start4);

			if (GetTickCount() - wait_start4 > SPIRITDRACULA_JUMP_TIME)
			{
				if (nx > 0) ani = SPIRITDRACULA_ANI_LANDING_AND_FLY_RIGHT;
				else ani = SPIRITDRACULA_ANI_LANDING_AND_FLY_LEFT;

				wait_start4 = 0;

				if (startwait5 == true)
					StartWait(startwait5, wait_start5);

				if (GetTickCount() - wait_start5 > SPIRITDRACULA_LANDING_TIME)
				{
					wait_start5 = 0;
					SetState(SPIRITDRACULA_STATE_IDLE);
					jump = false;
				}
			}
		}
		else if (state == SPIRITDRACULA_STATE_FIRE)
		{
			if (nx > 0) ani = SPIRITDRACULA_ANI_FIRE_RIGHT;
			else ani = SPIRITDRACULA_ANI_FIRE_LEFT;

			/*for (int i = 0; i < 3; i++)
				bullets[i]->Render();*/
		}
		animations[ani]->Render(x, y);
		RenderBoundingBox(100);
	}
}

void CSpiritDracula::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	if (state == SPIRITDRACULA_STATE_FIRE)
	{
		right = x + SPIRITDRACULA_FIRE_BBOX_WIDTH;
		bottom = y + SPIRITDRACULA_FIRE_BBOX_HEIGHT;
	}
	else
	{
		right = x + SPIRITDRACULA_BBOX_WIDTH;
		bottom = y + SPIRITDRACULA_BBOX_HEIGHT;
	}
}

void CSpiritDracula::StartWait(bool & startwait, DWORD & wait_start)
{
	wait = true;
	wait_start = GetTickCount();
	startwait = false;
}

void CSpiritDracula::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SPIRITDRACULA_STATE_JUMP:
		if (nx > 0) vx = SPIRITDRACULA_JUMP_SPEED_X;
		else vx = -SPIRITDRACULA_JUMP_SPEED_X;

		vy = -SPIRITDRACULA_JUMP_SPEED_Y;
		jump = true;
		break;
	case SPIRITDRACULA_STATE_IDLE:
		vx = 0;
		break;
	case SPIRITDRACULA_STATE_FIRE:
		if (resetpos == true)
		{
			SetPosition(this->x, this->y - 25.0f);
			resetpos = false;
		}
		vx = 0;
		break;
	}
}

void CSpiritDracula::Reset()
{
	startwait1 = true;
	startwait2 = true;
	startwait3 = true;
	startwait4 = true;
	startwait5 = true;
	startwait6 = true;
	startwait7 = true;

	//jump = false;
	reset = false;
	wait = false;
	fire = false;

	if (nx < 0)
	{
		head->SetPosition(x + HEAD_POSITION_X, y);
		head->SetSize(HEAD_WIDTH, HEAD_HEIGHT);
		//head->SetState(HIDENOBJECT_STATE_HEAD);
	}
	else
	{
		head->SetPosition(x + HEAD_POSITION_X1, y);
		head->SetSize(HEAD_WIDTH, HEAD_HEIGHT);
		//head->SetState(HIDENOBJECT_STATE_HEAD);
	}
}

CSpiritDracula * CSpiritDracula::GetInstance()
{
	if (__instance == NULL) __instance = new CSpiritDracula();
	return __instance;
}


CSpiritDracula::CSpiritDracula()
{
	CSimon *simon = CSimon::GetInstance();
	damage = 4;
	health = 16;
	SetPosition(x, y);
	height =  SPIRITDRACULA_JUMP_HEIGHT;

	startwait1 = true;
	startwait2 = true;
	startwait3 = true;
	startwait4 = true;
	startwait5 = true;
	startwait6 = true;
	startwait7 = true;

	jump = false;
	reset = false;
	wait = false;
	fire = false;
	isAddBulletToCell = false;
	isAddHeadToCell = false;

	int i;
	for (i = 0; i < 3; i++)
		bullets.push_back(new CBullet());
	for (i = 0; i < 3; i++)
	{
		bullets[i]->SetPosition(x + BULLET_POSITION_X, y + BULLET_POSITION_Y);
		bullets[i]->Setnx(-1);
	}

	bullets[0]->SetSpeed(x + BULLET_POSITION_X, y + BULLET_POSITION_Y, 
		simon->x + 5.0f, simon->y, 800);
	bullets[1]->SetSpeed(x + BULLET_POSITION_X, y + BULLET_POSITION_Y, 
		simon->x + 5.0f, simon->y - 6.0f, 800);
	bullets[2]->SetSpeed(x + BULLET_POSITION_X, y + BULLET_POSITION_Y,
		simon->x + 5.0f, simon->y + 6.0f, 800);


	head = new CHidenObject();
	head->SetPosition(x + HEAD_POSITION_X, y);
	head->SetSize(HEAD_WIDTH, HEAD_HEIGHT);
	head->SetState(HIDENOBJECT_STATE_HEAD);

	AddAnimation(250001);
	AddAnimation(250002);
	AddAnimation(250003);
	AddAnimation(250004);
	AddAnimation(250005);
	AddAnimation(250006);
	AddAnimation(250007);
	AddAnimation(250008);
	AddAnimation(250009);
	AddAnimation(250010);
}


CSpiritDracula::~CSpiritDracula()
{
}
