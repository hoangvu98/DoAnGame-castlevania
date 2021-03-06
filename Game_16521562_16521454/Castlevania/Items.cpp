#include "Items.h"
#include <fstream>
#include "InputImage.h"
#include "Simon.h"
#include "HidenObject.h"
#include "Monster.h"
#include "Candle.h"
#include "Dracula.h"
#include "SpiritDracula.h"
using namespace std;


CItems::CItems()
{

}


CItems::~CItems()
{
}

void CItems::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	CGameObject::Update(dt);
	vy = ITEM_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	bool IsUpdatePossiton = false;
	CalcPotentialCollisions(coObject, coEvents);
	if (coEvents.size() != 0)
	{
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
					IsUpdatePossiton = true;
					y += min_ty * dy + ny * 0.4f;
				}

			}
		}
	}
	DWORD now = GetTickCount();
	if (now - time_disapear > ITEM_TIME_DISAPEAR)
		SetState(ITEM_STATE_DELETE);
	if (!IsUpdatePossiton)
		y += dy;
}

void CDagger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == ITEM_STATE_ITEM)
		CItems::Update(dt, coObjects);
	else
	{
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;
		CGameObject::Update(dt);
		if (state != ITEM_STATE_DELETE)
		{
			float min_tx, min_ty, nx = 0, ny;
			coEventsResult.clear();
			CalcPotentialCollisions(coObjects, coEvents);
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				CSimon* simon = CSimon::CSimon::GetInstance();
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<CMonster *> (e->obj))
				{
					CMonster *monster = dynamic_cast<CMonster *>(e->obj);
					if (monster->state != MONSTER_STATE_DELETE && monster->state != MONSTER_STATE_DISAPPEAR)
					{
						monster->SetHealth(monster->GetHealth() - damage);
						SetState(ITEM_STATE_DELETE);
					}
				}
				else if (dynamic_cast<CCandle *> (e->obj))
				{
					CCandle *candle = dynamic_cast<CCandle *>(e->obj);
					if (candle->state != CANDLE_STATE_DELETE)
					{
						candle->SetState(CANDLE_STATE_DISAPPEAR);
						simon->SetSkill(false);
						SetState(ITEM_STATE_DELETE);
					}
				}
			}
			DWORD now = GetTickCount();
			if (now - time_delete > 1000)
				SetState(ITEM_STATE_DELETE);
		}
		x += dx;
		DebugOut(L"x=%f\n", x);
	}
}


void CDagger::Render()
{
	if (state == ITEM_STATE_WEAPON_LEFT)
	{
		animations[1]->Render(x, y);
	}
	else if (state != ITEM_STATE_DELETE)
	{
		animations[0]->Render(x, y);
	}
}

void CDagger::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + DAGGER_BBOX_WIDTH;
	bottom = y + DAGGER_BBOX_HEIGHT;
}
void CDagger::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ITEM_STATE_WEAPON_LEFT:
		vx = -SPEED_DAGGER;
		time_delete = GetTickCount();
		break;
	case ITEM_STATE_WEAPON_RIGHT:
		vx = SPEED_DAGGER;
		time_delete = GetTickCount();
	}
}
void CHeart::Render()
{
	if (state != ITEM_STATE_DELETE)
	{
		switch (size)
		{
		case HEART_BIG:
			animations[1]->Render(x, y);
			break;
		case HEART_SMALL:
			animations[0]->Render(x, y);
			break;
		}
	}
}

void CHeart::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	switch (size)
	{
	case HEART_BIG:
		right = x + HEART_BBOX_BIG_WIDTH;
		bottom = y + HEART_BBOX_BIG_HEIGHT;
		break;
	case HEART_SMALL:
		right = x + HEART_BBOX_SMALL_WIDTH;
		bottom = y + HEART_BBOX_SMALL_HEIGHT;
		break;
	}
}
void CWhipUpdate::Render()
{
	if (state != ITEM_STATE_DELETE)
	{
		animations[0]->Render(x, y);
	}
}

void CWhipUpdate::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + WHIP_UPDATE_BBOX_WIDTH;
	bottom = y + WHIP_UPDATE_BBOX_HEIGHT;
}

CMoneyBag::CMoneyBag(int size, int state)
{
	this->state = state;
	this->size = size;
	AddAnimation(13001);
	AddAnimation(13002);
	AddAnimation(13003);
}

void CMoneyBag::Render()
{
	if (state != ITEM_STATE_DELETE)
	{
		animations[state]->Render(x, y);
	}
}

void CMoneyBag::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + MONEY_BAG_BBOX_WIDTH;
	bottom = y + MONEY_BAG_BBOX_HEIGHT;
}

void CAxe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CSimon* simon = CSimon::CSimon::GetInstance();
	if (state == ITEM_STATE_ITEM)
		CItems::Update(dt, coObjects);
	else
	{
		CGameObject::Update(dt);
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;
		float min_tx, min_ty, nx = 0, ny;
		coEventsResult.clear();
		CalcPotentialCollisions(coObjects, coEvents);
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
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
				CDracula *dracula = dynamic_cast<CDracula *>(monster);
				CSpiritDracula *spiritdracula = dynamic_cast<CSpiritDracula *>(monster);

				if (dracula == NULL && spiritdracula == NULL)
				{
					if (monster->state != MONSTER_STATE_DELETE && monster->state != MONSTER_STATE_DISAPPEAR)
					{
						monster->SetHealth(monster->GetHealth() - damage);
						monster->SetIsInjure(false);
						monster->SetTimeInjure();
					}
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
					}
				}
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
					}
					/*if (spiritdracula->GetHealth() <= 0)
						spiritdracula->SetState(SPIRITDRACULA_STATE_DIE);
					else spiritdracula->SetHealth(spiritdracula->GetHealth() - 1);*/
				}
			}
			else if (dynamic_cast<CBullet *>(e->obj))
			{
				CBullet *bullet = dynamic_cast<CBullet *>(e->obj);
				bullet->SetState(BULLET_STATE_REFLECT);
			}
		}
		if (y >= 180.0f)
			SetState(ITEM_STATE_DELETE);
		vy += AXE_GRAVITY * dt;
		x += dx;
		y += dy;
	}
}

void CAxe::Render()
{
	if (state == ITEM_STATE_ITEM)
	{
		animations[0]->Render(x, y);
	}
	else if (state != ITEM_STATE_DELETE)
	{
		animations[1]->Render(x, y);
	}
}

void CAxe::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + AXE_BBOX_WIDTH;
	bottom = y + AXE_BBOX_HEIGHT;
}

void CAxe::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ITEM_STATE_WEAPON_LEFT:
		vx = -SPEED_AXE_X;
		vy = -SPEED_AXE_Y;
		break;
	case ITEM_STATE_WEAPON_RIGHT:
		vx = SPEED_AXE_X;
		vy = -SPEED_AXE_Y;
	}
}

CBoomerang::CBoomerang()
{
	fly = false;
	IsSetDistance = true;
	damage = 1;
	AddAnimation(15000);
	AddAnimation(15001);
	IsDelete = false;
}

void CBoomerang::Render()
{
	//int ani;
	if (state == ITEM_STATE_ITEM)
		animations[BOOMERANG_ANI_ITEM]->Render(x, y);
	else if (state == ITEM_STATE_WEAPON_LEFT || state == ITEM_STATE_WEAPON_RIGHT)
		animations[BOOMERANG_ANI_FLY]->Render(x, y);
	//RenderBoundingBox(200);
}

void CBoomerang::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BOOMERANG_BBOX_WIDTH;
	bottom = y + BOOMERANG_BBOX_HEIGHT;
}

void CBoomerang::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ITEM_STATE_WEAPON_LEFT:
		vx = -BOOMERANG_SPEED;
		break;
	case ITEM_STATE_WEAPON_RIGHT:
		vx = BOOMERANG_SPEED;
		break;
	case ITEM_STATE_DELETE:
		IsDelete = false;
		break;
	}
}

void CBoomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == ITEM_STATE_ITEM)
		CItems::Update(dt, coObjects);
	else
	{
		if (state != ITEM_STATE_DELETE)
		{
			CSimon *simon = CSimon::GetInstance();
			CGameObject::Update(dt);
			if (IsSetDistance)
			{
				IsSetDistance = false;
				float sx, sy;
				simon->GetPosition(sx, sy);
				left_distance = sx - DISTANCE_OF_BOOMERANG;
				right_distance = sx + DISTANCE_OF_BOOMERANG;
			}
			CGame* game = CGame::GetInstance();
			float cx, cy;
			game->GetCamera(cx, cy);
			if (x <= left_distance || x <= cx - 10.0f)
			{
				SetState(ITEM_STATE_WEAPON_RIGHT);
				fly = true;
				dx = 5.0f;
				if (IsDelete)
					SetState(ITEM_STATE_DELETE);
				else
					IsDelete = true;
			}
			if (x >= right_distance || x >= cx + VIEWPORT_WIDTH -10.0f)
			{
				SetState(ITEM_STATE_WEAPON_LEFT);
				fly = true;
				dx = -5.0f;
				if (IsDelete)
					SetState(ITEM_STATE_DELETE);
				else
					IsDelete = true;
			}
			vector<LPCOLLISIONEVENT> coEvents;
			vector<LPCOLLISIONEVENT> coEventsResult;

			CalcPotentialCollisions(coObjects, coEvents);
			if (coEvents.size() != 0)
			{
				float min_tx, min_ty, nx = 0, ny;
				FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
				for (UINT i = 0; i < coEventsResult.size(); i++)
				{
					LPCOLLISIONEVENT e = coEventsResult[i];
					if (dynamic_cast<CSimon *> (e->obj) && fly == true)
					{
						SetState(ITEM_STATE_DELETE);
						simon->SetSkill(false);
						fly = false;
					}
					else if (dynamic_cast<CCandle *> (e->obj))
					{
						CCandle *candle = dynamic_cast<CCandle *>(e->obj);
						if (candle->state != CANDLE_STATE_DELETE)
							candle->SetState(CANDLE_STATE_DISAPPEAR);
					}
					else if (dynamic_cast<CMonster *> (e->obj))
					{
						CMonster *monster = dynamic_cast<CMonster *>(e->obj);
						CDracula *dracula = dynamic_cast<CDracula *>(monster);
						CSpiritDracula *spiritdracula = dynamic_cast<CSpiritDracula *>(monster);

						if (dracula == NULL && spiritdracula == NULL)
						{
							if (monster->state != MONSTER_STATE_DELETE && monster->state != MONSTER_STATE_DISAPPEAR)
							{
								monster->SetHealth(monster->GetHealth() - damage);
								monster->SetIsInjure(false);
								monster->SetTimeInjure();
								Chiteffect* hiteffect = new Chiteffect();
								hiteffect->SetPosition(monster->x, monster->y);
								hiteffect->SetState(HITEFFECT_STATE_HIT);
								CCells* cell = simon->map->GetCell();
								cell->InitCells(hiteffect);
								simon->map->SetCell(cell);
							}
						}
					}
					else if (dynamic_cast<CHeadDracula *>(e->obj))
					{
						CDracula *dracula = CDracula::GetInstance();
						CHeadDracula *head = dynamic_cast<CHeadDracula *>(e->obj);
						if (dracula->state == DRACULA_STATE_FIRE || dracula->state == DRACULA_STATE_IDLE)
						{
								dracula->SetHealth(dracula->GetHealth() - 1);
								if (dracula->GetHealth() <= 0)
								{
									head->SetState(HEAD_STATE_FLY_AWAY);
									dracula->SetState(DRACULA_STATE_DIE);
								}
								Chiteffect* hiteffect = new Chiteffect();
								hiteffect->SetPosition(dracula->x, dracula->y);
								hiteffect->SetState(HITEFFECT_STATE_HIT);
								CCells* cell = simon->map->GetCell();
								cell->InitCells(hiteffect);
								simon->map->SetCell(cell);
						}
					}
					else if (dynamic_cast<CHidenObject *> (e->obj))
					{
						CSpiritDracula *spiritdracula = CSpiritDracula::GetInstance();
						CHidenObject *head = dynamic_cast<CHidenObject *> (e->obj);

						if (head->GetState() == HIDENOBJECT_STATE_HEAD)
						{
								spiritdracula->SetHealth(spiritdracula->GetHealth() - 1);
								if (spiritdracula->GetHealth() <= 0)
								{
									/*head->SetState(HEAD_STATE_FLY_AWAY);*/
									spiritdracula->SetState(SPIRITDRACULA_STATE_DIE);
								}
								
								Chiteffect* hiteffect = new Chiteffect();
								hiteffect->SetPosition(spiritdracula->x, spiritdracula->y);
								hiteffect->SetState(HITEFFECT_STATE_HIT);
								CCells* cell = simon->map->GetCell();
								cell->InitCells(hiteffect);
								simon->map->SetCell(cell);
						}
					}
					else if (dynamic_cast<CBullet *>(e->obj))
					{
						CBullet *bullet = dynamic_cast<CBullet *>(e->obj);
						bullet->SetState(BULLET_STATE_REFLECT);
					}
				}
			}
			x += dx;
		}
		else
		{
			IsSetDistance = true;
		}
	}
}
CHollyWater::CHollyWater()
{
	damage = 1;
	AddAnimation(16000);
	AddAnimation(16001);
	AddAnimation(16002);
}

void CHollyWater::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == ITEM_STATE_ITEM)
		CItems::Update(dt, coObjects);
	else
	{
		CGameObject::Update(dt);
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;
		if (vy <= 0.05f)
			vy += HOLLY_WATER_GRAVITY * dt;
		CalcPotentialCollisions(coObjects, coEvents);
		bool test = true;
		if (coEvents.size() != 0)
		{
			FilterCollisionImmediately(coEvents, coEventsResult);
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<CHidenObject *> (e->obj))
				{
					CHidenObject *hobj = dynamic_cast<CHidenObject *> (e->obj);
					if (hobj->state == HIDENOBJECT_STATE_NORMAL)
					{
						if (state != HOLLY_WATER_STATE_EXPLODE)
							time = GetTickCount();
						SetState(HOLLY_WATER_STATE_EXPLODE);
						test = false;					
					}
				}
				else if (dynamic_cast<CCandle *> (e->obj))
				{
					CCandle *candle = dynamic_cast<CCandle *>(e->obj);
					if (candle->state != CANDLE_STATE_DELETE)
						candle->SetState(CANDLE_STATE_DISAPPEAR);
				}
				else if (dynamic_cast<CSpiritDracula *>(e->obj))
				{
					CSpiritDracula *spiritdracula = dynamic_cast<CSpiritDracula *>(e->obj);
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
					}
				}
				else if (dynamic_cast<CMonster *> (e->obj))
				{
					CMonster *monster = dynamic_cast<CMonster *>(e->obj);
					CDracula *dracula = dynamic_cast<CDracula *>(monster);
					CSpiritDracula *spiritdracula = dynamic_cast<CSpiritDracula *>(monster);

					if (dracula == NULL && spiritdracula == NULL)
					{
						if (monster->state != MONSTER_STATE_DELETE && monster->state != MONSTER_STATE_DISAPPEAR)
						{
							if (monster->GetIsInjure())
							{
								monster->SetHealth(monster->GetHealth() - damage);
								monster->SetIsInjure(false);
								monster->SetTimeInjure();
							}
						}
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
						}
					}
				}
				else if (dynamic_cast<CBullet *>(e->obj))
				{
					CBullet *bullet = dynamic_cast<CBullet *>(e->obj);
					bullet->SetState(BULLET_STATE_REFLECT);
				}
				else if (dynamic_cast<CBullet *>(e->obj))
				{
					CBullet *bullet = dynamic_cast<CBullet *>(e->obj);
					bullet->SetState(BULLET_STATE_REFLECT);
				}
			}
		}
		if (test == true)
		{
			x += dx;
			y += dy;
		}
		if (state == HOLLY_WATER_STATE_EXPLODE)
		{
			DWORD now = GetTickCount();
			if (now - time > HOLLY_WATER_TIME_FIRE)
			{
				SetState(ITEM_STATE_DELETE);
			}
		}
	}
}

void CHollyWater::Render()
{
	if (state == ITEM_STATE_ITEM)
		animations[HOLLY_WATER_ANI_ITEM]->Render(x, y);
	else if (state == ITEM_STATE_WEAPON_LEFT || state == ITEM_STATE_WEAPON_RIGHT)
		animations[HOLLY_WATER_ANI_FALLING]->Render(x, y);
	else if (state == HOLLY_WATER_STATE_EXPLODE)
		animations[HOLLY_WATER_ANI_EXPLODE]->Render(x - 3, y - 3);
	//RenderBoundingBox(200);
}

void CHollyWater::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	if (state == HOLLY_WATER_STATE_EXPLODE)
	{
		right = x + FIRE_BBOX_WIDTH;
		bottom = y + FIRE_BBOX_HEIGHT;
	}
	else if (state == ITEM_STATE_ITEM)
	{
		right = x + ITEM_BBOX_WIDTH;
		bottom = y + ITEM_BBOX_HEIGHT;
	}
	else
	{
		right = x + BOTTLE_BBOX_WIDTH;
		bottom = y + BOTTLE_BBOX_HEIGHT;
	}
}

void CHollyWater::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ITEM_STATE_WEAPON_LEFT:
		vx = -HOLLY_WATER_FALLING_SPEED_X;
		vy = -HOLLY_WATER_FALLING_SPEDD_Y;
		break;
	case ITEM_STATE_WEAPON_RIGHT:
		vx = HOLLY_WATER_FALLING_SPEED_X;
		vy = -HOLLY_WATER_FALLING_SPEDD_Y;
		break;
	case HOLLY_WATER_STATE_EXPLODE:
		vx = 0;
		break;
	}
}

COtherStuff::COtherStuff()
{
	AddAnimation(260000);
}

void COtherStuff::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy = ITEM_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	bool IsUpdatePossiton = false;
	CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() != 0)
	{
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
					IsUpdatePossiton = true;
					y += min_ty * dy + ny * 0.4f;
				}

			}
		}
	}
	if (!IsUpdatePossiton)
		y += dy;
}

void COtherStuff::Render()
{
	animations[0]->Render(x, y);
}

void COtherStuff::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + OTHER_STUFF_WIDTH;
	bottom = y + OTHER_STUFF_HEIGHT;
}

void COtherStuff::SetState(int state)
{
	CGameObject::SetState(state);
}

CPotRoast::CPotRoast()
{
	health = 6;
	AddAnimation(270000);
}

void CPotRoast::Render()
{
	if (state == ITEM_STATE_ITEM)
		animations[0]->Render(x, y);
}

void CPotRoast::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + POT_ROAST_BBOX_WIDTH;
	bottom = y + POT_ROAST_BBOX_HEIGHT;
}
