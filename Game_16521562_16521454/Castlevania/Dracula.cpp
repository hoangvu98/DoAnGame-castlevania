#include "Dracula.h"
#include <cstdlib>
#include "Simon.h"

CDracula *CDracula::__instance = NULL;

void CDracula::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CSimon *simon = CSimon::GetInstance();
	int i;
	if (state != DRACULA_STATE_DIE)
	{
		head->Update(dt, coObjects);
		if (head->GetState() != HEAD_STATE_FLY)
		{
			SetState(DRACULA_STATE_IDLE);
			if (start == true)
				StartUntouchable();
			if (GetTickCount() - untouchable_start > DRACULA_UNTOUCHABLE_TIME)
			{
				untouchable_start = 0;
				untouchable = false;

				if (startwait1 == true)
					StartWait(startwait1, wait_start1);
				if (nx > 0)
				{
					bullets[0]->SetSpeed(x + BULLET_POSITION_X, y + BULLET_POSITION_Y, simon->x, simon->y + 10.0f, 800);
					bullets[1]->SetSpeed(x + BULLET_POSITION_X, y + BULLET_POSITION_Y, simon->x, simon->y - 30.0f, 800);
					bullets[2]->SetSpeed(x + BULLET_POSITION_X, y + BULLET_POSITION_Y, simon->x, simon->y + 60.0f, 800);
				}
				else
				{
					bullets[0]->SetSpeed(x, y + BULLET_POSITION_Y, simon->x, simon->y + 10.0f, 800);
					bullets[1]->SetSpeed(x, y + BULLET_POSITION_Y, simon->x, simon->y - 30.0f, 800);
					bullets[2]->SetSpeed(x, y + BULLET_POSITION_Y, simon->x, simon->y + 60.0f, 800);
				}
				if (GetTickCount() - wait_start1 > DRACULA_WAIT_TIME)
				{
					SetState(DRACULA_STATE_FIRE);

					for (int i = 0; i < 3; i++)
						bullets[i]->Update(dt, coObjects);

					wait_start1 = 0;

					if (startwait2 == true)
						StartWait(startwait2, wait_start2);

					if (GetTickCount() - wait_start2 > DRACULA_ATTACKING_TIME)
					{
						SetState(DRACULA_STATE_INVISIBLE);
						head->SetState(HEAD_STATE_INVISIBLE);
						wait_start2 = 0;

						if (startwait3)
							StartWait(startwait3, wait_start3);

						if (GetTickCount() - wait_start3 > DRACULA_TIME_TO_RESET)
						{
							reset = true;
							wait_start3 = 0;
						}
					}
				}
			}

			if (reset == true)
			{
				int random;
				random = rand() % 218 + 11;
				SetPosition((float)random, y);

				float sx, sy;
				CSimon *simon = CSimon::GetInstance();
				simon->GetPosition(sx, sy);
				if (sx < this->x)
				{
					this->nx = -1;
					head->Setnx(-1);
					head->SetPosition(this->x + HEAD_OFFSET_X, this->y - HEAD_OFFSET_Y);
				}
				else
				{
					this->nx = 1;
					head->Setnx(1);
					head->SetPosition(this->x + HEAD_OFFSET_X1, this->y - HEAD_OFFSET_Y);
				}

				Reset();
			}
		}
	}
	else
	{
		if (isSpirit == true)
			LoadSpirit();

		spirit_dracula->Update(dt, coObjects);
	}
}

void CDracula::Render()
{	
	if (state != DRACULA_STATE_DIE)
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
				if (nx > 0)
				{
					ani = DRACULA_ANI_FIRE_RIGHT;
					animations[DRACULA_ANI_FIRE_RIGHT1]->Render(this->x - OFFSET, y);
				}
				else ani = DRACULA_ANI_FIRE_LEFT;

				for (int i = 0; i < 3; i++)
					bullets[i]->Render();
			}
			if (untouchable == true)
			{
				if (alpha == 128) alpha = 200;
				else alpha = 128;
			}
			else alpha = 255;
			animations[ani]->Render(x, y, alpha);
		}
		head->Render();
	}
	else
		spirit_dracula->Render();
}

void CDracula::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + DRACULA_BBOX_WIDTH;
	bottom = y + DRACULA_BBOX_HEIGHT;
}

void CDracula::LoadSpirit()
{
	spirit_dracula = new CSpiritDracula(this->x, this->y - 19.0f);
	spirit_dracula->SetState(SPIRITDRACULA_STATE_IDLE);
	spirit_dracula->Setnx(this->nx);
	isSpirit = false;
}

void CDracula::StartUntouchable()
{
	untouchable = true;
	untouchable_start = GetTickCount();
	start = false;
}

void CDracula::StartWait(bool &startwait, DWORD &wait_start)
{
	wait = true;
	wait_start = GetTickCount();
	startwait = false;
}

void CDracula::Reset()
{
	CSimon *simon = CSimon::GetInstance();
	start = true;
	untouchable = false;

	reset = false;
	wait = false;
	startwait1 = true;
	startwait2 = true;
	startwait3 = true;
	int i;
	if (nx > 0)
	{
		for (i = 0; i < 3; i++)
		{
			bullets[i]->SetPosition(x + BULLET_POSITION_X, y + BULLET_POSITION_Y);
			bullets[i]->Setnx(1);
			/*if (bullets[i]->vx < 0)
				bullets[i]->vx = -bullets[i]->vx;*/
		}
		
		/*bullets[0]->vx = -bullets[0]->vx;
		bullets[1]->vx = -bullets[1]->vx;
		bullets[2]->vx = -bullets[2]->vx;*/
		/*if (simon->state == SIMON_STATE_JUMP)
		{
			bullets[0]->SetSpeed(x + BULLET_POSITION_X, y + BULLET_POSITION_Y, simon->x, simon->y + 10.0f, 800);
			bullets[1]->SetSpeed(x + BULLET_POSITION_X, y + BULLET_POSITION_Y, simon->x, simon->y - 30.0f, 800);
			bullets[2]->SetSpeed(x + BULLET_POSITION_X, y + BULLET_POSITION_Y, simon->x, simon->y + 60.0f, 800);
		}*/
	}
	else
	{
		for (i = 0; i < 3; i++)
		{
			bullets[i]->SetPosition(x, y + BULLET_POSITION_Y);
			bullets[i]->Setnx(-1);
			/*if (bullets[i]->vx > 0) 
				bullets[i]->vx = -bullets[i]->vx;*/
		}

		
		/*bullets[1]->vx = -bullets[1]->vx;
		bullets[2]->vx = -bullets[2]->vx;*/
		/*if (simon->state == SIMON_STATE_JUMP)
		{
			bullets[0]->SetSpeed(x , y + BULLET_POSITION_Y, simon->x, simon->y + 10.0f, 800);
			bullets[1]->SetSpeed(x, y + BULLET_POSITION_Y, simon->x, simon->y - 30.0f, 800);
			bullets[2]->SetSpeed(x, y + BULLET_POSITION_Y, simon->x, simon->y + 60.0f, 800);
		}*/
	}
	
}

void CDracula::SetState(int state)
{
	CGameObject::SetState(state);
}

CDracula::CDracula()
{
	CSimon *simon = CSimon::GetInstance();
	SetPosition(DEFAULT_POSITION_X, DEFAULT_POSITION_Y);
	health = 1;
	damage = 4;

	alpha = 255;

	start = true;
	untouchable = false;

	reset = false;
	wait = false;

	startwait1 = true;
	startwait2 = true;
	startwait3 = true;
	isSpirit = true;

	head = new CHeadDracula();
	head->SetPosition(211.0f, 146.0f);
	head->SetState(HEAD_STATE_FLY);
	head->Setnx(-1);

	int i;
	for (i = 0; i < 3; i++)
		bullets.push_back(new CBullet());
	for (i = 0; i < 3; i++)
	{
		bullets[i]->SetPosition(x + BULLET_POSITION_X, y + BULLET_POSITION_Y);
		bullets[i]->Setnx(-1);
	}

	bullets[0]->SetSpeed(x + BULLET_POSITION_X, y + BULLET_POSITION_Y, simon->x, simon->y + 20.0f, 800);
	bullets[1]->SetSpeed(x + BULLET_POSITION_X, y + BULLET_POSITION_Y, simon->x, simon->y - 30.0f, 800);
	bullets[2]->SetSpeed(x + BULLET_POSITION_X, y + BULLET_POSITION_Y, simon->x, simon->y + 60.0f, 800);

	AddAnimation(240001);
	AddAnimation(240002);
	AddAnimation(240003);
	AddAnimation(240004);
	AddAnimation(240005);
}

CDracula::CDracula(float x, float y)
{
	CSimon *simon = CSimon::GetInstance();
	SetPosition(x, y);
	health = 16;
	damage = 4;

	alpha = 255;

	start = true;
	untouchable = false;

	reset = false;
	wait = false;

	startwait1 = true;
	startwait2 = true;
	startwait3 = true;

	head = new CHeadDracula();
	head->SetPosition(211.0f, 146.0f);
	head->SetState(HEAD_STATE_FLY);
	head->Setnx(-1);

	int i;
	for (i = 0; i < 3; i++)
		bullets.push_back(new CBullet());
	for (i = 0; i < 3; i++)
	{
		bullets[i]->SetPosition(x + BULLET_POSITION_X, y + BULLET_POSITION_Y);
		bullets[i]->Setnx(-1);
	}

	bullets[0]->SetSpeed(x + BULLET_POSITION_X, y + BULLET_POSITION_Y, simon->x, simon->y + 20.0f, 800);
	bullets[1]->SetSpeed(x + BULLET_POSITION_X, y + BULLET_POSITION_Y, simon->x, simon->y - 30.0f, 800);
	bullets[2]->SetSpeed(x + BULLET_POSITION_X, y + BULLET_POSITION_Y, simon->x, simon->y + 60.0f, 800);

	AddAnimation(240001);
	AddAnimation(240002);
	AddAnimation(240003);
	AddAnimation(240004);
	AddAnimation(240005);
}

CDracula::~CDracula()
{
}

CDracula * CDracula::GetInstance()
{
	if (__instance == NULL) __instance = new CDracula();
	return __instance;
}