#include "Simon.h"
#include "debug.h"
#include "Candle.h"
#include "Game.h"
#include "Panther.h"
#include "HidenObject.h"
#include "EntranceLevel.h"
#include "ClockTowerLevel.h"
#include "Ghoul.h"
#include "Bat.h"
#include "Eagle.h"
#include "Hunchback.h"
#include "Dracula.h"
#include "Brick.h"
DWORD FrameCollusion;
int color = 255;
float stair_x = 0, stair_y = 0;
int nx1;
DWORD time_reset;
CSimon *CSimon::__instance = NULL;
void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	if (time == 0)
		Reset = true;
	else
	{
		CGameObject::Update(dt);
		if (IsUp != 2)
			IsUp = 0;
		if (IsDown != 2)
			IsDown = 0;
		if (stair != 2)
			vy += SIMON_GRAVITY;
		if (state != SIMON_STATE_KNEE && previousstate == SIMON_STATE_KNEE)
		{
			previousstate = NULL;
			SetPosition(x, y - 5);
			SetState(SIMON_STATE_IDLE);
		}
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;
		coEventsResult.clear();
		if (stair != 2 && stair != 5 && stair != 6)
			stair = 0;
		if (state != SIMON_STATE_DIE)
			CalcPotentialCollisions(coObject, coEvents);

		if (fight)
		{
			whip->SetPosition(x, y);
			DWORD t = GetTickCount() - whip->GetFrameWhip();
			if (t >= 2 * FRAME_TIME_WHIP)
			{
				if (whip->GetCurrentFrame() == 2)
					whip->fight = true;
				if (t >= 3 * FRAME_TIME_WHIP)
				{
					fight = false;
					whip->fight = false;
				}
			}
			whip->Update(dt, coObject);
			whip->SetPosition(x, y);
		}
		DWORD t = GetTickCount() - FrameWeapon;
		if (skill)
		{
			if (t >= 3 * FRAME_TIME_WHIP)
			{
				skill = false;
				ResetFight();
			}
		}
		/*if (t < 2000)
			weapon->Update(dt, coObject);*/
		coEventsResult.clear();
		FilterCollisionImmediately(coEvents, coEventsResult);
		bool test = true;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CHidenObject *> (e->obj))
			{
				CHidenObject *hidenobject = dynamic_cast<CHidenObject *>(e->obj);
				if (hidenobject->GetState() == HIDENOBJECT_STATE_STAIR_UP)
				{
					nx1 = hidenobject->nx;
					hidenobject->GetStair_XY(stair_x, stair_y);
					if (stair != 2 && stair != 4)
						stair = 1;
					if (stair == 2 && IsDown != 2)
						IsDown = 1;
				}
				else if (hidenobject->GetState() == HIDENOBJECT_STATE_STAIR_DOWN)
				{
					nx1 = hidenobject->nx;
					hidenobject->GetStair_XY(stair_x, stair_y);
					if (stair != 2 && stair != 4)
						stair = 3;
					if (stair == 2 && IsUp != 2)
						IsUp = 1;
				}
				else if (hidenobject->GetState() == HIDENOBJECT_STATE_STAIR_UP_DOWN)
				{
					int test;
					float size_x, size_y;
					hidenobject->GetSize(size_x, size_y);
					if (hidenobject->y + size_y >= y + SIMON_BBOX_IDLE_HEIGHT)
						test = 0;
					else
						test = 1;
					nx1 = hidenobject->nx;
					hidenobject->GetStair_XY(stair_x, stair_y);
					if (stair != 2 && stair != 5 && stair != 6)
						stair = 4;
					if (stair == 2 && IsDown != 2 && test == 0)
						IsDown = 1;
					if (stair == 2 && IsUp != 2 && test == 1)
						IsUp = 1;
				}
			}
			else if (dynamic_cast<CHeart *>(e->obj))
			{
				CHeart *hearts = dynamic_cast<CHeart *>(e->obj);
				heart += hearts->GetHearts();
				hearts->SetState(ITEM_STATE_DELETE);
			}
			else if (dynamic_cast<CPotRoast *>(e->obj))
			{
				CPotRoast *potroast = dynamic_cast<CPotRoast *>(e->obj);
				if (potroast->state != ITEM_STATE_DELETE)
				{
					health += potroast->GetHealth();
					if (health > 16) health = 16;
				}
				potroast->SetState(ITEM_STATE_DELETE);
			}
			else if (dynamic_cast<CMoneyBag *>(e->obj))
			{
				CMoneyBag *moneybag = dynamic_cast<CMoneyBag *>(e->obj);
				if (moneybag->GetSize() == MONEY_BAG_BIG)
					score += 1000;
				else
				{
					if (state == MONEY_BAG_RED)
						score += 100;
					else if (state == MONEY_BAG_BLUE)
						score += 400;
					else if (state == MONEY_BAG_WHITE)
						score += 700;
				}
				moneybag->SetState(ITEM_STATE_DELETE);
			}
			else if (dynamic_cast<CDagger *>(e->obj))
			{
				CItems *items = dynamic_cast<CDagger *>(e->obj);
				if (items->state == ITEM_STATE_ITEM)
				{
					OnSkill = true;
					weapon = new CDagger();
					items->SetState(ITEM_STATE_DELETE);
				}
			}
			else if (dynamic_cast<CAxe *>(e->obj))
			{
				CItems *items = dynamic_cast<CAxe *>(e->obj);
				if (items->state == ITEM_STATE_ITEM)
				{
					OnSkill = true;
					weapon = new CAxe();
					items->SetState(ITEM_STATE_DELETE);
				}
			}
			else if (dynamic_cast<CBoomerang *>(e->obj))
			{
				CItems *items = dynamic_cast<CBoomerang *>(e->obj);
				if (items->state == ITEM_STATE_ITEM)
				{
					OnSkill = true;
					weapon = new CBoomerang();
					items->SetState(ITEM_STATE_DELETE);
				}
			}
			else  if (dynamic_cast<CHollyWater *>(e->obj))
			{
				CItems *items = dynamic_cast<CHollyWater *>(e->obj);
				if (items->state == ITEM_STATE_ITEM)
				{
					OnSkill = true;
					weapon = new CHollyWater();
					items->SetState(ITEM_STATE_DELETE);
				}
			}
			else if (dynamic_cast<CWhipUpdate *> (e->obj))
			{
				CItems *items = dynamic_cast<CWhipUpdate *>(e->obj);
				if (whip->state == WHITE_WHIP)
				{
					whip->SetState(BLUE_WHIP);
				}
				else if (whip->state == BLUE_WHIP)
				{
					whip->SetState(YELLOW_WHIP);
				}
				state_update = state;
				SetState(SIMON_STATE_UPDATE);
				items->SetState(ITEM_STATE_DELETE);
				FrameUpdate = GetTickCount();
			}

			else if (dynamic_cast<CMonster *> (e->obj))
			{
				CMonster *monster = dynamic_cast<CMonster *>(e->obj);
				if (dynamic_cast<CDracula *> (e->obj) && monster->state != DRACULA_STATE_FIRE
					&& monster->state != DRACULA_STATE_IDLE)
				{
					break;
				}
				else if (dynamic_cast<CBat *> (e->obj) && monster->state == BAT_STATE_SLEEPING)
				{
					CBat *bat = dynamic_cast<CBat *>(e->obj);
					float cx, cy;
					bat->GetPositionAppear(cx, cy);
					bat->SetPosition(cx, cy);
					if (bat->GetSize() == BAT_SIZE_SMALL)
					{
						int state;
						state = bat->GetStateAppear();
						bat->SetState(state);
					}
					else
						bat->SetState(BAT_STATE_FLY);
				}
				else if (dynamic_cast<CFishman *> (e->obj) && monster->state == MONSTER_STATE_SLEEPING)
				{
					CFishman *fishman = dynamic_cast<CFishman *>(e->obj);
					float cx, cy, tx, ty;
					fishman->GetPositionAppear(cx, cy);
					fishman->GetPosition(tx, ty);
					fishman->SetPostionAppear(tx, ty);
					if (fishman->nx > 0)
						fishman->SetPosition(x + 80.0f, 164.0f);
					if (fishman->nx < 0)
						fishman->SetPosition(x - 80.0f, 164.0f);
					fishman->GetPosition(tx, ty);
					int state;
					state = fishman->GetStateAppear();
					fishman->SetState(state);
				}
				else if (dynamic_cast<CEagle *> (e->obj) && monster->state == EAGLE_STATE_SLEEPING)
				{
					CEagle *eagle = dynamic_cast<CEagle *>(e->obj);
					float cx, cy, tx, ty;
					eagle->GetPositionAppear(cx, cy);
					eagle->GetPosition(tx, ty);
					eagle->SetPosstionAppear(tx, ty);
					eagle->SetPosition(x - 80.0f, cy);
					eagle->GetPosition(tx, ty);
					CHunchback* hunchback;
					hunchback = new CHunchback();
					hunchback->SetPosition(tx + 10.0f, ty + 21.0f);
					hunchback->SetState(HUNCHBACK_STATE_FLY_RIGHT);
					CCells* cell = map->GetCell();
					cell->InitCells(hunchback);
					map->SetCell(cell);
					int state;
					state = eagle->GetStateAppear();
					eagle->SetState(state);
				}
				else if (collusion == 0 && monster->state != MONSTER_STATE_DELETE &&
					monster->state != MONSTER_STATE_DISAPPEAR)
				{
					if (stair != 2)
					{
						collusion = 1;
						SetState(SIMON_STATE_COLLUSION);
					}
					else
						collusion = 2;
					fight = false;
					whip->fight = false;
					ResetFight();
					health -= monster->GetDamage();
					collusion_nx = nx;
					FrameCollusion = GetTickCount();
				}
			}
			else if (dynamic_cast<CBullet *>(e->obj) && collusion == 0)
			{
				CBullet *bullet = dynamic_cast<CBullet *>(e->obj);
				if (stair != 2)
				{
					collusion = 1;
					SetState(SIMON_STATE_COLLUSION);
				}
				else
					collusion = 2;
				fight = false;
				whip->fight = false;
				ResetFight();
				health -= bullet->GetDamage();
				collusion_nx = nx;
				FrameCollusion = GetTickCount();
			}
			else if (dynamic_cast<CBone *>(e->obj) && collusion == 0)
			{
				CBone *bone = dynamic_cast<CBone *>(e->obj);
				if (stair != 2)
				{
					collusion = 1;
					SetState(SIMON_STATE_COLLUSION);
				}
				else
					collusion = 2;
				fight = false;
				whip->fight = false;
				ResetFight();
				health -= bone->GetDamage();
				collusion_nx = nx;
				FrameCollusion = GetTickCount();
			}
			else if (dynamic_cast<CDoor *>(e->obj))
			{
				CDoor *door = dynamic_cast<CDoor *>(e->obj);
				if (state_auto == 6)
				{
					door->SetStop(true);
					door->SetState(DOOR_STATE_OPEN);
					state_auto = 7;
				}
				else if (state_auto == 7)
				{
					DWORD now = GetTickCount();
					if (now - door->GetTimeOpen() > 300)
					{
						if (door->state == DOOR_STATE_OPEN)
							state_auto = 4;
						else if (door->state == DOOR_STATE_CLOSE)
						{
							state_auto = -1;
							camera_auto = 3;
							door->SetState(DOOR_STATE_NORMAL);
						}
					}
				}
				else if (state_auto == 8)
				{

					door->SetStop(true);
					door->SetState(DOOR_STATE_CLOSE);
					state_auto = 7;
				}
			}
			else if (dynamic_cast<COtherStuff *>(e->obj))
			{
				IsChangeMap = true;
				stage = 6;
			}
		}
		for (UINT i = 0; i < coEvents.size(); i++)
		{
			LPCOLLISIONEVENT e = coEvents[i];
			if (dynamic_cast<CHidenObject *> (e->obj))
			{
				CHidenObject *hidenobject = dynamic_cast<CHidenObject *>(e->obj);
				if (hidenobject->GetState() != HIDENOBJECT_STATE_NORMAL)
				{
					coEvents.erase(coEvents.begin() + i);
					i--;
				}
			}
			else if (dynamic_cast<CDoor *> (e->obj))
			{
				CDoor *door = dynamic_cast<CDoor *>(e->obj);
				if (door->IsGo == false)
				{
					coEvents.erase(coEvents.begin() + i);
					i--;
				}
			}
			else if (dynamic_cast <CBrick *> (e->obj))
				continue;
			else
			{
				coEvents.erase(coEvents.begin() + i);
				i--;
			}
		}
		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
			test = false;
		}
		else
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
					if (stair != 2)
					{						
						if (test)
						{
							if (y + min_ty * dy + ny * 0.4f >= 132)
								DebugOut(L"y=%f\n", y + min_ty * dy + ny * 0.4f);
							x += min_tx * dx + nx * 0.4f;
							y += min_ty * dy + ny * 0.4f;
							test = false;
						}
					}
					DWORD now = GetTickCount();
					if (now - FrameCollusion > 100)
					{
						if (ny != 0 && stair != 2) {
							vy = 0; jump = 0;
						}
						if (collusion == 1 && ny < 0)
							if (state == SIMON_STATE_COLLUSION)
							{
								SetState(SIMON_STATE_KNEE);
								FrameCollusion = GetTickCount();
							}
					}
				}
				else if (dynamic_cast<CBrick *> (e->obj))
				{
					if (test)
					{
						if (y + min_ty * dy + ny * 0.4f >= 132)
							DebugOut(L"y=%f\n", y + min_ty * dy + ny * 0.4f);
						x += min_tx * dx + nx * 0.4f;
						y += min_ty * dy + ny * 0.4f;
					}
					test = false;
				}
				else if (dynamic_cast<CDoor *>(e->obj))
				{
					CDoor *door = dynamic_cast<CDoor *>(e->obj);
					if (door->GetIsAuto() == true)
					{
						if (door->GetIsHiden() == true && door->IsGo == true)
						{
							if (door->GetIsStair() == true)
							{
								if (stair == 2)
								{
									if (door->nx == 1)
									{
										door->IsGo = false;
										if (door->cx != 0 || door->cy != 0)
										{
											simon_x = door->cx;
											simon_y = door->cy;
										}
										map->SetIsNext(true);
										map->SetNextScene(door->GetScene());
									}
									else
									{
										door->IsGo = false;
										if (door->cx != 0 || door->cy != 0)
										{
											simon_x = door->cx;
											simon_y = door->cy;
										}
										map->SetIsFall(true);
										map->SetNextScene(door->GetScene());
									}
								}
							}
							else
							{
								door->IsGo = false;
								state_auto = 5;
								if (this->nx > 0)
									simon_x = door->x + door->size;
								else
									simon_x = door->x - door->size;
								map->SetNextScene(door->GetScene());
							}
						}
						else if (door->GetIsHiden() == false && door->IsGo == true)
						{
							x += dx;
							CCells* cell = map->GetCell();
							float width, height;
							int column, row;
							map->GetTileMap()->GetSize(width, height);
							column = (int)width / CELL_WIDTH + 1;
							row = (int)height / CELL_HEIGHT + 1;
							cell = new CCells(column, row);
							map->SetCell(cell);
							test = false;
							SetState(SIMON_STATE_IDLE);
							door->IsGo = false;
							camera_auto = 2;
							state_auto = -1;
							map->SetNextScene(door->GetScene());
						}
					}
					else
					{
						simon_x = 0;
						simon_y = 0;
						door->IsGo = false;
						map->SetIsNext(true);
						map->SetNextScene(door->GetScene());
					}
				}

			}
		}
		if (test)
		{
			if (y+dy >= 132)
				DebugOut(L"y=%f\n",  y);
			x += dx;
			y += dy;
		}
		DWORD now = GetTickCount();
		if (now - FrameCollusion > 100 && collusion == 1 && state == SIMON_STATE_KNEE)
		{
			if (health <= 0)
			{
				IsDie = true;
				y += 20;
				time_reset = GetTickCount();
				collusion = 0;
				stair = 0;
			}
			else
				collusion = 2;
		}
		else if ( collusion == 2)
		{
			if (health <= 0)
			{
				IsDie = true;
				y += 20;
				time_reset = GetTickCount();
				collusion = 0;
				stair = 0;
			}
			if (now - FrameCollusion > 2000)
				collusion = 0;
		}
		if ((y >= 190.0f || time==0) && !IsDie)
		{
			vx = 0;
			vy = 0;
			IsDie = true;
			time_reset = GetTickCount();
		}

		if (IsDie)
		{
			SetState(SIMON_STATE_DIE);
			collusion = 0;
			if (now - time_reset > TIME_RESET)
			{
				Reset = true;
				IsDie = false;
			}
		}
		Auto();
		if (camera_auto == 0)
			Camera();
		else
			CameraAuto();


		//DebugOut(L"state_auto=%d\n", state_auto);
		//DebugOut(L"IsUp=%d\nIsDown=%d\n", IsUp,IsDown);
		//DebugOut(L"state=%d\n", state);
		//DebugOut(L"up=%d\ndown=%d\n", IsUp, IsDown);
		//DebugOut(L"x=%f\ny=%f\n", x, y);	
		//DebugOut(L"y=%f\n",  y);
		//DebugOut(L"heart=%d\n", heart);
		//DebugOut(L"stair=%d\n", stair);
	}
}

void CSimon::Render()
{
	int ani;
	bool IsRenDer = false;
	if (state == SIMON_STATE_DIE)
	{
		color = 255;
		if (nx > 0)
			ani = SIMON_ANI_DIE_RIGHT;
		else
			ani = SIMON_ANI_DIE_LEFT;
	}
	else
	{
		if (collusion != 1)
		{
			if (collusion == 0)
				color = 255;
			else
			{
				if (color == 150)
					color = 200;
				else
					color = 150;
			}
			if (stair == 2)
			{
				DWORD now = GetTickCount();
				if (state == SIMON_STATE_STAIR_UP)
				{
					if (nx > 0)
						ani = SIMON_ANI_STAIR_UP_RIGHT;
					else
						ani = SIMON_ANI_STAIR_UP_LEFT;
				}
				else if (state == SIMON_STATE_STAIR_DOWN)
				{
					if (nx > 0)
						ani = SIMON_ANI_STAIR_DOWN_RIGHT;
					else
						ani = SIMON_ANI_STAIR_DOWN_LEFT;
				}
				else
				{
					    if (fight == true || skill==true)
						{
							if (state == SIMON_STATE_STAIR_UP_IDLE)
							{

								if (nx > 0)
									ani = SIMON_ANI_STAIR_FIGHT_UP_RIGHT;
								else
									ani = SIMON_ANI_STAIR_FIGHT_UP_LEFT;
							}
							else
							{
								if (nx > 0)
									ani = SIMON_ANI_STAIR_FIGHT_DOWN_RIGHT;
								else
									ani = SIMON_ANI_STAIR_FIGHT_DOWN_LEFT;
							}
							if (fight == true)
							{
								if (nx > 0)whip->SetStateWhip(WHIP_STATE_RIGHT);
								else whip->SetStateWhip(WHIP_STATE_LEFT);
							}
						}
						else
						{
							if (state == SIMON_STATE_STAIR_UP_IDLE)
							{
								if (nx > 0)
									ani = SIMON_ANI_STAIR_IDLE_UP_RIGHT;
								else
									ani = SIMON_ANI_STAIR_IDLE_UP_LEFT;
							}
							else if (state == SIMON_STATE_STAIR_DOWN_IDLE)
							{
								if (nx > 0)
									ani = SIMON_ANI_STAIR_IDLE_DOWN_RIGHT;
								else
									ani = SIMON_ANI_STAIR_IDLE_DOWN_LEFT;
							}
						}
				}
			}
			else
			{
				if (state == SIMON_STATE_UPDATE)
				{
					IsRenDer = true;
					if (state_update == SIMON_STATE_WALKING_LEFT)
						ani = SIMON_ANI_WALKING_LEFT;
					else
						ani = SIMON_ANI_WALKING_RIGHT;
					if (alpha == 255)
					{
						animations[ani]->Render_now(x, y, 255, alpha, 28, 36);
						alpha = 237;
					}
					else
					{
						animations[ani]->Render_now(x, y);
						alpha = 255;
					}
				}
				else
				{
					DWORD now = GetTickCount();
					if (state == SIMON_STATE_BEHIND)
						ani = SIMON_ANI_BEHIND;
					else
					{
						if (fight == true || skill == true)
						{
							if (mx == 1)
							{
								if (nx > 0)
									ani = SIMON_ANI_KNEE_FIGHT_RIGHT;
								else
									ani = SIMON_ANI_KNEE_FIGHT_LEFT;
							}
							else
							{
								if (nx > 0)
									ani = SIMON_ANI_FIGHT_RIGHT;
								else
									ani = SIMON_ANI_FIGHT_LEFT;
							}
							if (nx > 0)whip->SetStateWhip(WHIP_STATE_RIGHT);
							else whip->SetStateWhip(WHIP_STATE_LEFT);
						}
						else
						{
							if (mx == 1)
							{
								if (nx > 0)
									ani = SIMON_ANI_JUMP_RIGHT; //SIMON_ANI_KNEE_RIGHT
								else
									ani = SIMON_ANI_JUMP_LEFT; //SIMON_ANI_KNEE_LEFT
							}
							else if (state == SIMON_STATE_WALKING_RIGHT)
								ani = SIMON_ANI_WALKING_RIGHT;
							else if (state == SIMON_STATE_WALKING_LEFT)
								ani = SIMON_ANI_WALKING_LEFT;
							else
							{
								if (nx > 0)
									ani = SIMON_ANI_IDLE_RIGHT;
								else
									ani = SIMON_ANI_IDLE_LEFT;
							}

							if (vy < 0 && nx < 0)
								ani = SIMON_ANI_JUMP_LEFT;
							else if (vy < 0 && nx > 0)
								ani = SIMON_ANI_JUMP_RIGHT;
						}
					}				
				}
			}
		}
		else
		{
			if (state == SIMON_STATE_KNEE)
			{
				if (nx > 0)
					ani = SIMON_ANI_JUMP_RIGHT;//knee
				else
					ani = SIMON_ANI_JUMP_LEFT;//knee
				if (color == 200)
				{
					color = 150;
				}
				else
				{
					color = 200;
				}
			}
			else if (state == SIMON_STATE_COLLUSION)
			{
				color = 255;
				if (nx > 0)
					ani = SIMON_ANI_COLLUSION_RIGHT;
				else
					ani = SIMON_ANI_COLLUSION_LEFT;

			}
		}
	}
	if (!IsRenDer)
	{
		DWORD t = GetTickCount() - whip->GetFrameWhip();
		if (fight == true)
		{
			if (t <= FRAME_TIME_WHIP && nx > 0)
				animations[ani]->Render(x - 7, y, color);
			else if (t >= 2 * FRAME_TIME_WHIP && nx < 0)
				animations[ani]->Render(x - 6, y, color);
			else
				animations[ani]->Render(x, y, color);
			whip->SetCurrentFrame(animations[ani]->GetCureentFrame());
			whip->Render();
		}
		else
			animations[ani]->Render(x, y, color);
	}
	/*DWORD t = GetTickCount() - FrameWeapon;
	if (t< 2000)
		weapon->Render();*/
	RenderBoundingBox(100);
}

void CSimon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	DWORD t = GetTickCount() - whip->GetFrameWhip();
	if (state == SIMON_STATE_DIE)
	{
		right = x + 30;
		bottom = y + 14;
	}
	else if (vy < 0)
	{
		right = x + SIMON_BBOX_KNEE_WIDTH;
		bottom = y + SIMON_BBOX_KNEE_HEIGHT;
	}
	else if (vx == 0 && mx == 1)
	{
		right = x + SIMON_BBOX_KNEE_WIDTH;
		bottom = y + SIMON_BBOX_KNEE_HEIGHT;
	}
	else
	{
		right = x + SIMON_BBOX_IDLE_WIDTH;
		bottom = y + SIMON_BBOX_IDLE_HEIGHT;
	}


}


void CSimon::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SIMON_STATE_WALKING_LEFT:
		if (mx == 0)
			vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_WALKING_RIGHT:
		if (mx == 0)
			vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_JUMP:
		vy = -SIMON_JUMP_SPEED;
		break;
	case SIMON_STATE_IDLE:
		vx = 0;
		mx = 0;
		break;
	case SIMON_STATE_KNEE:
		previousstate = SIMON_STATE_KNEE;
		vx = 0;
		mx = 1;
		break;
	case SIMON_STATE_UPDATE:
		vx = 0;
		break;
	case SIMON_STATE_STAIR_UP_IDLE:
		vx = 0;
		vy = 0;
		break;
	case SIMON_STATE_STAIR_DOWN_IDLE:
		vx = 0;
		vy = 0;
		break;
	case SIMON_STATE_STAIR_UP:
		if (nx > 0)
		{
			vx = 8.0f / TIME_STAIR;
			animations[SIMON_ANI_STAIR_UP_RIGHT]->SetCureentFrame(-1);
		}
		else
		{
			vx = -8.0f / TIME_STAIR;
			animations[SIMON_ANI_STAIR_UP_LEFT]->SetCureentFrame(-1);
		}
		vy = -8.0f / TIME_STAIR;
		break;
	case SIMON_STATE_STAIR_DOWN:
		if (nx > 0)
		{
			vx = 8.0f / TIME_STAIR;
			animations[SIMON_ANI_STAIR_DOWN_RIGHT]->SetCureentFrame(-1);
		}
		else
		{
			vx = -8.0f / TIME_STAIR;
			animations[SIMON_ANI_STAIR_DOWN_LEFT]->SetCureentFrame(-1);
		}
		vy = 8.0f / TIME_STAIR;
		break;
	case SIMON_STATE_COLLUSION:
		if (collusion_nx > 0)
		{
			nx = 1;
			vx = SIMON_WALKING_SPEED;
		}
		else
		{
			nx = -1;
			vx = -SIMON_WALKING_SPEED;
		}
		vy = -0.15f;
		break;
	case SIMON_STATE_BEHIND:
		vx = 0;
		break;
	case SIMON_STATE_DIE:
		vx = 0;
		vy = 0;
		break;
	}
}

void CSimon::ResetFight()
{
	animations[SIMON_ANI_FIGHT_LEFT]->SetCureentFrame(-1);
	animations[SIMON_ANI_FIGHT_RIGHT]->SetCureentFrame(-1);
	animations[SIMON_ANI_KNEE_FIGHT_LEFT]->SetCureentFrame(-1);
	animations[SIMON_ANI_KNEE_FIGHT_RIGHT]->SetCureentFrame(-1);
}

void CSimon::Auto()
{
	if (state_auto == -1)
	{
		vy = 0;
	}
	if (state_auto == 1) // tu dong di ve phia cau thang
	{
		if (x > stair_x)
		{
			SetState(SIMON_STATE_WALKING_LEFT);
			state_auto = 2;
		}
		else if (x < stair_x)
		{
			state_auto = 3;
			SetState(SIMON_STATE_WALKING_RIGHT);
		}
	}
	else if (state_auto == 2) //tu dong len cau thang
	{
		if (x <= stair_x)
		{
			x = stair_x;
			y = stair_y;
			nx = nx1;
			if (stair == 1)
			{
				SetState(SIMON_STATE_STAIR_UP);
			}
			else if (stair == 3)
			{
				SetState(SIMON_STATE_STAIR_DOWN);
			}
			else if (stair == 5)
			{
				SetState(SIMON_STATE_STAIR_UP);
			}
			else if (stair == 6)
			{
				SetState(SIMON_STATE_STAIR_DOWN);
			}
			SetFrameStair();
			stair = 2;
			state_auto = 0;
		}
	}
	else if (state_auto == 3) //tu dong len cau thang
	{
		if (x >= stair_x)
		{
			x = stair_x;
			y = stair_y;
			nx = nx1;
			if (stair == 1)
			{
				SetState(SIMON_STATE_STAIR_UP);
			}
			else if (stair == 3)
			{
				SetState(SIMON_STATE_STAIR_DOWN);
			}
			else if (stair == 5)
			{
				SetState(SIMON_STATE_STAIR_UP);
			}
			else if (stair == 6)
			{
				SetState(SIMON_STATE_STAIR_DOWN);
			}
			SetFrameStair();
			stair = 2;
			state_auto = 0;
		}
	}
	else if (state_auto == 4) //tu dong di qua cong hien
	{
		float min;
		float max;
		map->GetSizeMap(min, max);
		SetState(SIMON_STATE_WALKING_RIGHT);
		if (x > max)
		{
			state_auto = 8;
			SetState(SIMON_STATE_IDLE);
			simon_x = x;
			simon_y = y;
		}
	}
	else if (state_auto == 5)//tu dong di qua cong an
	{
		if (nx > 0)
		{
			SetState(SIMON_STATE_WALKING_RIGHT);
			vx = SIMON_WALKING_SPEED / 2;
		}
		else
		{
			SetState(SIMON_STATE_WALKING_LEFT);
			vx = -SIMON_WALKING_SPEED / 2;
		}
		if (nx > 0)
		{
			if (x > simon_x)
			{
				simon_x = 0;
				map->SetIsNext(true);
			}
		}
		else
		{
			if (x < simon_x)
			{
				simon_x = 0;
				map->SetIsNext(true);
			}
		}
	}
}

void CSimon::Camera()
{
	CGame *game = CGame::GetInstance();
	float min;
	float max;
	map->GetSizeMap(min, max);
	if (dynamic_cast<CEntranceLevel *>(map))
	{
		if (map->GetScene() == SCENE_5 && x + 128.0f > max && !MeetBoss)
		{
			MeetBoss = true;
			CHidenObject *hidenobject;
			hidenobject = new CHidenObject();
			hidenobject->SetState(HIDENOBJECT_STATE_NORMAL);
			hidenobject->SetPosition(2570, 0);
			hidenobject->SetSize(6, 160);
			CCells* cell = map->GetCell();
			cell->InitCells(hidenobject);
			map->SetCell(cell);
			CBossBat* bossbat = CBossBat::GetInstance();
			bossbat->SetState(BOSS_BAT_STATE_fLY);
		}
		if (!MeetBoss)
		{
			if (x - 128.0f < min)
			{
				game->SetCamera(min, 0.0f);
			}
			else if (x + 128.0f > max)
			{
				game->SetCamera(max - 256.0f, 0.0f);
			}
			else
				game->SetCamera(x - 128.0f, 0.0f);
		}
	}
	else if (dynamic_cast<CClockTowerLevel *>(map))
	{
		if (map->GetScene() == SCENE_6_5 && x - 128.0f < min && !MeetBoss)
		{
			MeetBoss = true;
			CHidenObject *hidenobject;
			hidenobject = new CHidenObject();
			hidenobject->SetState(HIDENOBJECT_STATE_NORMAL);
			hidenobject->SetPosition(240, 0);
			hidenobject->SetSize(6, 160);
			CCells* cell = map->GetCell();
			cell->InitCells(hidenobject);
			map->SetCell(cell);
			CDracula* dracula = CDracula::GetInstance();
			dracula->SetState(DRACULA_STATE_INVISIBLE);
		}
		if (!MeetBoss)
		{
			if (x - 128.0f < min)
			{
				game->SetCamera(min, 0.0f);
			}
			else if (x + 128.0f > max)
			{
				game->SetCamera(max - 256.0f, 0.0f);
			}
			else
				game->SetCamera(x - 128.0f, 0.0f);
		}
	}
}

void CSimon::CameraAuto()
{
	CGame *game = CGame::GetInstance();
	float min;
	float max;
	map->GetSizeMap(min, max);

	if (camera_auto == 2) //di chuyen camera qua simon
	{
		float cx, cy;
		game->GetCamera(cx, cy);
		if (cx < x - 128.0f)
		{
			game->SetCamera(cx + 1.0f, 0.0f);
		}
		else
		{
			camera_auto = -1;
			state_auto = 6;
		}
	}
	else if (camera_auto == 3)// di chuyen camera ve simon
	{
		float cx, cy;
		game->GetCamera(cx, cy);
		if (cx < x - 22.0f)
		{
			game->SetCamera(cx + 1.0f, 0.0f);
		}
		else
		{
			camera_auto = -1;
			state_auto = -1;
			map->SetIsNext(true);
		}
	}
	//float cx, cy;
	//game->GetCamera(cx, cy);
	//DebugOut(L"camera=%f\n", cx);
}


CSimon::CSimon()
{
	time = 400;
	live = 3;
	AddAnimation(101);
	AddAnimation(102);
	AddAnimation(201);
	AddAnimation(202);
	AddAnimation(301);
	AddAnimation(302);
	AddAnimation(401);
	AddAnimation(402);
	AddAnimation(501);
	AddAnimation(502);
	AddAnimation(601);
	AddAnimation(602);
	AddAnimation(603);
	AddAnimation(604);
	AddAnimation(701);
	AddAnimation(702);
	AddAnimation(703);
	AddAnimation(704);
	AddAnimation(801);
	AddAnimation(802);
	AddAnimation(803);
	AddAnimation(804);
	AddAnimation(901);
	AddAnimation(902);
	AddAnimation(1000);
	AddAnimation(1001);
	AddAnimation(1002);
	Reset = false;
	mx = 0;
	whip = new CWhip();
	whip->SetState(WHITE_WHIP);
	map = CEntranceLevel::GetInstance();
	IsChangeMap = false;
}

CSimon * CSimon::GetInstance()
{
	if (__instance == NULL)
		__instance = new CSimon();
	return __instance;
}
