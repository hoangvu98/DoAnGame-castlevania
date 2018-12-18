#include "Bat.h"
#include "Simon.h"
#include "ClockTowerLevel.h"
#include "debug.h"
DWORD bat_time_route;
bool bat_test = true;
float bat_min_x, bat_min_y, bat_max_x, bat_max_y;
int ani_test = 1;
CBat::CBat(int size)
{
	if (size == BAT_SIZE_SMALL)
	{
		damage = 1;
		health = 1;
		score = 100;
		nx = -1;
		vy = BAT_SMALL_FLYING_SPEED_X;
	}
	else
	{
		score = 1000;
		health = 16;
		damage = 4;
		bullet = new CBullet();
	}
	this->size = size;
	AddAnimation(12001);
	AddAnimation(12002);
	AddAnimation(20001);
	SetState(BAT_STATE_SLEEPING);
}

void CBat::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (size == BAT_SIZE_SMALL)
	{
		left = x;
		top = y;
		right = x + BAT_SMALL_BBOX_WIDTH;
		bottom = y + BAT_SMALL_BBOX_HEIGHT;
	}
	else
	{
		if (state == BAT_STATE_SLEEPING)
		{
			left = x;
			top = y;
			right = left + weight;
			bottom = top + height;
		}
		else if (state == BAT_STATE_FLY)
		{
			left = x;
			top = y;
			bottom = top + BAT_BIG_BBOX_HEIGHT;
			if (animations[2]->GetCureentFrame() == 0)
				right = left + BAT_BIG_BBOX_WIDTH_1;
			else
				right = left + BAT_BIG_BBOX_WIDTH_2;
		}
	}
}

void CBat::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CMonster::Update(dt, coObjects);
	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	CSimon *simon = CSimon::GetInstance();
	if (state != BAT_STATE_SLEEPING)
	{
		if (size == BAT_SIZE_SMALL)
		{
			if (state != MONSTER_STATE_DISAPPEAR && state != MONSTER_STATE_DELETE)
			{
				x += dx;
				y += dy;

				if (y > Height_Fly + BAT_DISTANCE_FLY)
				{
					y = Height_Fly + BAT_DISTANCE_FLY;
					vy = -vy;
				}
				if (y < Height_Fly - BAT_DISTANCE_FLY)
				{
					y = Height_Fly - BAT_DISTANCE_FLY;
					vy = -vy;
				}
			}
		}
		else
		{
			if (state == BAT_STATE_FLY)
			{
				if (ani_test == 1 && animations[2]->GetCureentFrame() == 1)
				{
					x += 8;
					y -= 1;
					ani_test = 0;
				}
				else if (ani_test == 0 && animations[2]->GetCureentFrame() == 0)
				{
					x -= 8;
					y += 1;
					ani_test = 1;
				}
				CClockTowerLevel *level1 = CClockTowerLevel::GetInstance();
				CGameObject::Update(dt);
				if (bat_test == true)
				{
					bat_test = false;
					bat_max_x = x + BAT_BIG_LIMIT_X;
					bat_min_x = x - BAT_BIG_LIMIT_X;
					bat_max_y = y + BAT_BIG_LIMIT_Y;
					if (y - BAT_BIG_LIMIT_Y < 0)
						bat_min_y = 0;
					else
						bat_min_y = y - BAT_BIG_LIMIT_Y;
				}
				float v = (simon->x - x) / 300;
				float v1;
				if (v < 0)
					v1 = -v;
				else
					v1 = v;
				if (v1 < BAT_BIG_SPEEDING_X)
					vx = v;
				v = (simon->y - y) / 200;
				float v2;
				if (v < 0)
					v2 = -v;
				else
					v2 = v;
				if (v2 < BAT_BIG_SPEEDING_Y)
					vy = v;

				if (x > bat_max_x)
				{
					vx = -BAT_BIG_SPEEDING_X;
				}
				if (x < bat_min_x)
				{
					vx = BAT_BIG_SPEEDING_X;
				}
				if (y > bat_max_y)
				{
					vy = -BAT_BIG_SPEEDING_Y;
				}
				if (y < bat_min_y)
				{
					vy = BAT_BIG_SPEEDING_Y;
				}

			}
			else if (state == BAT_STATE_FIRE)
			{
				bullet->Update(dt, coObjects);
			}
			x += dx;
			y += dy;
			DWORD now = GetTickCount();
			if (now - bat_time_route > 10000)
			{
				bat_time_route = GetTickCount() - 3000;
			}
			else if (now - bat_time_route > 5000)
			{
				bat_time_route = GetTickCount() - 2000;
			}
			else if (now - bat_time_route > 4000)
			{
				vx = 0;
				vy = 0;
			}
			else if (now - bat_time_route > 3000)
			{
				vx = BAT_BIG_SPEEDING_X / 5;
				vy = BAT_BIG_SPEEDING_Y / 5;
			}
			else if (now - bat_time_route > 2000)
			{
				if ((x + BAT_BIG_LIMIT_X >= simon->x) && (x - BAT_BIG_LIMIT_X <= simon->x)
					&& (y + BAT_BIG_LIMIT_Y >= simon->y) && (y - BAT_BIG_LIMIT_Y <= simon->y))
				{
					if (simon->x - x > 0)
						vx = BAT_BIG_SPEEDING_X;
					else
						vx = -BAT_BIG_SPEEDING_X;
					if (simon->y - y > 0)
						vy = BAT_BIG_SPEEDING_Y;
					else
						vy = -BAT_BIG_SPEEDING_Y;
				}
				else
				{
					SetState(BAT_STATE_FIRE);
					bullet->SetPosition(x, y);
					bullet->SetState(x, simon->x);
				}
				bat_time_route = GetTickCount();
				bat_test = true;
			}
			else if (now - bat_time_route > 1000)
			{
				vx = 0;
				vy = 0;
			}
		}
	}
	else
	{
	bat_time_route = GetTickCount() - 10000;
	}
}

void CBat::Render()
{
	if (state != BAT_STATE_SLEEPING)
	{
		if (state != MONSTER_STATE_DISAPPEAR && state != MONSTER_STATE_DELETE)
		{
			int ani;
			if (size == BAT_SIZE_SMALL)
			{
				if (nx > 0)
					ani = BAT_SMALL_ANI_RIGHT;
				else
					ani = BAT_SMALL_ANI_LEFT;
			}
			else
			{
				ani = BAT_BIG_ANI_FLY;
			}
			animations[ani]->Render(x, y);
			if (state == BAT_STATE_FIRE)
				bullet->Render();
		}
	}
	RenderBoundingBox(200);
}

void CBat::SetState(int state)
{
	CMonster::SetState(state);
	switch (state)
	{
	case BAT_STATE_FLY_LEFT:
		vx = -BAT_SMALL_FLYING_SPEED_X;
		//nx = -1;
		break;
	case BAT_STATE_FLY_RIGHT:
		vx = BAT_SMALL_FLYING_SPEED_X;
		//nx = -1;
		break;
	case BAT_STATE_FIRE:
		vx = 0;
		vy = 0;
		break;
	}
}

void CBat::SetHeightFly(float height_fly)
{
	Height_Fly = height_fly;
}
