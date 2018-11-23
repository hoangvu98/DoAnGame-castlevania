#include "Whip.h"
#include "Candle.h"
#include "InputImage.h"
#include <vector>
#include "Simon.h"
#include "debug.h"
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
	if (t <= 150)
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
	}
	else if (t > 150 && t <= 300)
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
	else if (t >= 300)
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
		}
	}
}
void CWhip::Render()
{
	int ani = 2 * state + state_whip;
	animations[ani]->Render(x, y, 255);
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
	/*else if (state == RED_WHIP)
	{
		right = x + RED_WHIP_BBOX_WIDTH;
		bottom = y + RED_WHIP_BBOX_HEIGHT;
	}*/
}

void CWhip::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case WHITE_WHIP:
		state = WHITE_WHIP;
		size = SHORT_WHIP;
		break;
	case BLUE_WHIP:
		state = BLUE_WHIP;
		size = SHORT_WHIP;
		break;
	case YELLOW_WHIP:
		state = YELLOW_WHIP;
		size = LONG_WHIP;
		break;
	}
}

