#include "Whip.h"
#include "Candle.h"
#include "InputImage.h"
#include <vector>
#include "Simon.h"
#include "debug.h"
#include "Ghoul.h"
#include "Brick.h"
#include "Panther.h"
#include "Dracula.h"
#include "HeadDracula.h"
#include "Bullet.h"
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
	CSimon* simon = CSimon::GetInstance();
	FindPosstion();
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
					Chiteffect* hiteffect = new Chiteffect();
					hiteffect->SetPosition(candle->x, candle->y);
					hiteffect->SetState(HITEFFECT_STATE_HIT);
					CCells* cell = simon->map->GetCell();
					cell->InitCells(hiteffect);
					simon->map->SetCell(cell);
				}
			}
			else if (dynamic_cast<CHeadDracula *>(e->obj))
			{
				CDracula *dracula = CDracula::GetInstance();
				CHeadDracula *head = dynamic_cast<CHeadDracula *>(e->obj);
				if (dracula->state == DRACULA_STATE_FIRE || dracula->state == DRACULA_STATE_IDLE)
				{
					if (dracula->GetIsInjure())
					{
						dracula->SetHealth(dracula->GetHealth() - 1);
						if (dracula->GetHealth() <= 0)
						{
							head->SetState(HEAD_STATE_FLY_AWAY);
							dracula->SetState(DRACULA_STATE_DIE);
						}
						dracula->SetIsInjure(false);
						dracula->SetTimeInjure();

						Chiteffect* hiteffect = new Chiteffect();
						hiteffect->SetPosition(head->x, head->y);
						hiteffect->SetState(HITEFFECT_STATE_HIT);
						CCells* cell = simon->map->GetCell();
						cell->InitCells(hiteffect);
						simon->map->SetCell(cell);
					}
				}
			}
			else if (dynamic_cast<CDracula *>(e->obj))
			{

			}
			else if (dynamic_cast<CMonster *> (e->obj))
			{
				CMonster *monster = dynamic_cast<CMonster *>(e->obj);
				CDracula *dracula = dynamic_cast<CDracula *>(monster);
				CSpiritDracula *spiritdracula = dynamic_cast<CSpiritDracula *>(monster);

				if (dracula == NULL && spiritdracula == NULL)
				{
					if (monster->state != MONSTER_STATE_DELETE && monster->state != MONSTER_STATE_DISAPPEAR
						&& monster->state != MONSTER_STATE_SLEEPING)
					{
						if (IsSubHP)
						{
							monster->SetHealth(monster->GetHealth() - damage);
							IsSubHP = false;

							Chiteffect* hiteffect = new Chiteffect();
							hiteffect->SetPosition(monster->x, monster-> y);
							hiteffect->SetState(HITEFFECT_STATE_HIT);
							CCells* cell = simon->map->GetCell();
							cell->InitCells(hiteffect);
							simon->map->SetCell(cell);
						}
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
					brick->SetState(BRICK_STATE_DISAPPEAR);


			}
			else if (dynamic_cast<CHidenObject *> (e->obj))
			{
				CSpiritDracula *spiritdracula = CSpiritDracula::GetInstance();
				CHidenObject *head = dynamic_cast<CHidenObject *> (e->obj);

				if (head->GetState() == HIDENOBJECT_STATE_HEAD)
				{
					if (spiritdracula->GetIsInjure())
					{
						spiritdracula->SetHealth(spiritdracula->GetHealth() - 1);
						if (spiritdracula->GetHealth() <= 0)
						{
							/*head->SetState(HEAD_STATE_FLY_AWAY);*/
							spiritdracula->SetState(SPIRITDRACULA_STATE_DIE);
						}
						spiritdracula->SetIsInjure(false);
						spiritdracula->SetTimeInjure();
						Chiteffect* hiteffect = new Chiteffect();
						hiteffect->SetPosition(head->x, head->y);
						hiteffect->SetState(HITEFFECT_STATE_HIT);
						CCells* cell = simon->map->GetCell();
						cell->InitCells(hiteffect);
						simon->map->SetCell(cell);
					}
				}
			}
			else if (dynamic_cast<CBullet *>(e->obj))
			{
				CBullet *bullet = dynamic_cast<CBullet *>(e->obj);
				bullet->SetState(BULLET_STATE_REFLECT);
			}
		}
	}
}
void CWhip::Render()
{
	FindPosstion();
	int ani = 2 * state + state_whip;
	DWORD t = GetTickCount() - FrameWhip;
	animations[ani]->SetCureentFrame(currentFrame);
	animations[ani]->Render_now(x, y, 255);
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

void CWhip::FindPosstion()
{
	if (currentFrame == 0)
	{
		if (size == SHORT_WHIP)
		{
			if (state_whip == WHIP_STATE_RIGHT)
				SetPosition(x -8, y + 8);
			else
				SetPosition(x + 29, y + 8);
		}
		else
		{
			if (state_whip == WHIP_STATE_RIGHT)
				SetPosition(x - 8, y + 8);
			else
				SetPosition(x + 30, y + 8);
		}
		IsSubHP = true;
	}
	else if (currentFrame == 1)
	{

		if (size == SHORT_WHIP)
		{
			if (state_whip == WHIP_STATE_RIGHT)
				SetPosition(x - 6, y + 4);
			else
				SetPosition(x + 22, y + 5);
		}
		else
		{
			if (state_whip == WHIP_STATE_RIGHT)
				SetPosition(x - 7, y + 5);
			else
				SetPosition(x + 22, y + 5);
		}
	}
	else if (currentFrame == 2)
	{
		if (size == SHORT_WHIP)
		{
			if (state_whip == WHIP_STATE_RIGHT)
				SetPosition(x + 30, y + 8);
			else
				SetPosition(x - 23, y + 7);
		}
		else
		{
			if (state_whip == WHIP_STATE_RIGHT)
				SetPosition(x + 30, y + 10);
			else
				SetPosition(x - 39, y + 8);
		}
	}
}

