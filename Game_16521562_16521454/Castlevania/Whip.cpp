#include "Whip.h"
#include "Candle.h"
#include "InputImage.h"
#include <vector>
#include "Simon.h"
#include "debug.h"
#include "Ghoul.h"
#include "Brick.h"
#include "Panther.h"
#define WHIP_TEXTURE_PATH L"castlevania_texture\\Weapon\\Whip.png"
#define ID_WHIP	6
using namespace std;


CWhip::CWhip()
{
	fight = false;
	AddAnimation(2000);
	AddAnimation(2001);
	AddAnimation(2002);
	AddAnimation(2003);
	AddAnimation(2004);
	AddAnimation(2005);
	AddAnimation(2006);
	AddAnimation(2007);
}

void CWhip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	DWORD t = GetTickCount() - FrameWhip;
	if (t <= FRAME_TIME_WHIP)
	{
		if (size == SHORT_WHIP)
		{
			if (state_whip == WHIP_STATE_RIGHT)
				SetPosition(x - 6, y + 9);//
			else
				SetPosition(x + 24, y + 8);//
		}
		else
		{
			if (state_whip == WHIP_STATE_RIGHT)
				SetPosition(x - 6, y + 9);//
			else
				SetPosition(x + 21, y + 8);
		}
		IsSubHP = true;
	}
	else if (t > FRAME_TIME_WHIP && t <= FRAME_TIME_WHIP*2)
	{

		if (size == SHORT_WHIP)
		{
			if (state_whip == WHIP_STATE_RIGHT)
				SetPosition(x - 11, y + 6);//
			else
				SetPosition(x + 15, y + 6);//
		}
		else
		{
			if (state_whip == WHIP_STATE_RIGHT)
				SetPosition(x - 11, y + 6);//
			else
				SetPosition(x + 14, y + 6);
		}
	}
	else if (t >= 2* FRAME_TIME_WHIP && t <= FRAME_TIME_WHIP*3)
	{

		if (size == SHORT_WHIP)
		{
			if (state_whip == WHIP_STATE_RIGHT)
				SetPosition(x + 22, y + 7);//
			else
				SetPosition(x - 22, y + 5);//
		}
		else
		{
			if (state_whip == WHIP_STATE_RIGHT)
				SetPosition(x + 22, y + 7);//
			else
				SetPosition(x - 39, y + 5);
		}
	}
	if (fight == true)
	{
		coEventsResult.clear();
		CalcPotentialCollisions(coObjects, coEvents);
		FilterCollisionImmediately(coEvents, coEventsResult);
		CSimon* simon = CSimon::GetInstance();
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CCandle *> (e->obj))
			{
				CCandle *candle = dynamic_cast<CCandle *>(e->obj);

				if (candle->state != CANDLE_STATE_DELETE)
				{
					candle->SetState(CANDLE_STATE_DISAPPEAR);
				}
			}
			else if (dynamic_cast<CMonster *> (e->obj))
			{
				CMonster *monster = dynamic_cast<CMonster *>(e->obj);
				if (monster->state != MONSTER_STATE_DELETE && monster->state != MONSTER_STATE_DISAPPEAR)
				{
					if (IsSubHP)
					{
						monster->SetHealth(monster->GetHealth() - 1);
						IsSubHP = false;
					}
				}
			}
			else if (dynamic_cast<CBrick *>(e->obj))
			{
				CBrick *brick = dynamic_cast<CBrick *>(e->obj);
				brick->SetDel(brick->GetDel() + 1);
				if (brick->GetDel() <= 10)
					brick->SetState(BRICK_STATE_HALF);
				else
					brick->SetState(BRICK_STATE_DELETE);


			}
		}
	}
}
void CWhip::Render()
{
	int ani = 2 * state + state_whip;
	DWORD t = GetTickCount() - FrameWhip;
	if (t <= 3 * FRAME_TIME_WHIP)
		animations[ani]->Render(x, y, 255);
	else
		animations[ani]->SetCureentFrame(2);
}


void CWhip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	if (state == WHITE_WHIP)
	{
		right = x + WHITE_WHIP_BBOX_WIDTH;
		bottom = y + WHITE_WHIP_BBOX_HEIGHT;
	}
	else if (state == BLUE_WHIP)
	{
		right = x + BLUE_WHIP_BBOX_WIDTH;
		bottom = y + BLUE_WHIP_BBOX_HEIGHT;
	}
	else if (state == YELLOW_WHIP)
	{
		right = x + YELLOW_WHIP_BBOX_WIDTH;
		bottom = y + YELLOW_WHIP_BBOX_HEIGHT;
	}
}

void CWhip::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case WHITE_WHIP:
		size = SHORT_WHIP;
		damage = 1;
		break;
	case BLUE_WHIP:
		size = SHORT_WHIP;
		damage = 2;
		break;
	case YELLOW_WHIP:
		size = LONG_WHIP;
		damage = 2;
		break;
	}
}

