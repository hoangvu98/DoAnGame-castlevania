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
DWORD FrameCollusion;
int color = 255;
float stair_x = 0;
int nx1;
CSimon *CSimon::__instance = NULL;
CMap *level1 = CClockTowerLevel::GetInstance();
void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
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

	if (fight == true)
	{
		whip->SetPosition(x, y);
		DWORD t = GetTickCount() - whip->GetFrameWhip();
		if (t >= 2 * FRAME_TIME_WHIP)
		{
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
	if (skill)
	{
		weapon->Update(dt, coObject);
	}
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
				stair_x = hidenobject->GetStair_X();
				if (stair != 2 && stair != 4)
					stair = 1;
				if (stair == 2 && IsDown != 2)
					IsDown = 1;
			}
			else if (hidenobject->GetState() == HIDENOBJECT_STATE_STAIR_DOWN)
			{
				nx1 = hidenobject->nx;
				stair_x = hidenobject->GetStair_X();
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
				stair_x = hidenobject->GetStair_X();
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
			OnSkill = true;
			CItems *items = dynamic_cast<CDagger *>(e->obj);
			weapon = new CDagger();
			items->SetState(ITEM_STATE_DELETE);
		}
		else if (dynamic_cast<CAxe *>(e->obj))
		{
			OnSkill = true;
			CItems *items = dynamic_cast<CAxe *>(e->obj);
			weapon = new CAxe();
			items->SetState(ITEM_STATE_DELETE);
		}
		else if (dynamic_cast<CBoomerang *>(e->obj))
		{
			OnSkill = true;
			CItems *items = dynamic_cast<CBoomerang *>(e->obj);
			weapon = new CBoomerang();
			items->SetState(ITEM_STATE_DELETE);
		}
		else  if (dynamic_cast<CHollyWater *>(e->obj))
		{
			OnSkill = true;
			CItems *items = dynamic_cast<CHollyWater *>(e->obj);
			weapon = new CHollyWater();
			items->SetState(ITEM_STATE_DELETE);
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
			if (dynamic_cast<CBat *> (e->obj) && monster->state == BAT_STATE_SLEEPING)
			{
				CBat *bat = dynamic_cast<CBat *>(e->obj);
				float cx, cy;
				bat->GetPositionAppear(cx, cy);
				bat->SetPosition(cx, cy);
				if (bat->GetSize() == BAT_SIZE_SMALL)
				{
					int state;
					state=bat->GetStateAppear();
					bat->SetState(state);
				}
				else
					bat->SetState(BAT_STATE_FLY);
			}
			else if (dynamic_cast<CEagle *> (e->obj) && monster->state == EAGLE_STATE_SLEEPING)
			{
				CEagle *eagle = dynamic_cast<CEagle *>(e->obj);
				float cx, cy,tx,ty;
				eagle->GetPositionAppear(cx, cy);
				eagle->GetPosition(tx, ty);
				eagle->SetPosstionAppear(tx, ty);
				eagle->SetPosition(x-80.0f, cy);
				eagle->GetPosition(tx, ty);
				CHunchback* hunchback;
				hunchback = new CHunchback();
				hunchback->SetPosition(tx+10.0f, ty+21.0f);
				hunchback->SetState(HUNCHBACK_STATE_FLY_RIGHT);
				CCells* cell = level1->GetCell();
				cell->InitCells(hunchback);
				level1->SetCell(cell);
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
				health -= monster->GetDamage();
				collusion_nx = nx;
				FrameCollusion = GetTickCount();
			}		
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
					x += min_tx * dx + nx * 0.4f;
					y += min_ty * dy + ny * 0.4f;
					test = false;
				}
				//test = false;
				/*if (nx != 0) {
					vx = 0;
				}
				if (ny != 0) {
					vy = 0; jump = 0;
				}*/
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
									level1->SetIsNext(true);
									level1->SetNextScene(door->GetScene());
								}
								else
								{
									door->IsGo = false;
									if (door->cx != 0 || door->cy != 0)
									{
										simon_x = door->cx;
										simon_y = door->cy;
									}
									level1->SetIsFall(true);
									level1->SetNextScene(door->GetScene());
								}
							}
						}
						else
						{
							door->IsGo = false;
							state_auto = 5;
							if (nx > 0)
								simon_x = door->x + door->size;
							else
								simon_x = door->x - door->size;
							level1->SetNextScene(door->GetScene());
						}
					}
					else if (door->GetIsHiden() == false && door->IsGo == true)
					{
						SetState(SIMON_STATE_IDLE);
						door->IsGo = false;
						camera_auto = 2;
						state_auto = -1;
						level1->SetNextScene(door->GetScene());
					}
				}
				else
				{
					door->IsGo = false;
					level1->SetIsNext(true);
					level1->SetNextScene(door->GetScene());
				}
			}

		}
	}
	if (test)
	{
		x += dx;
		y += dy;
	}
	DWORD now = GetTickCount();
	if (now - FrameCollusion > 100 && collusion == 1 && state == SIMON_STATE_KNEE)
	{
		collusion = 2;
	}
	else if (now - FrameCollusion > 2000 && collusion == 2)
	{
		collusion = 0;
	}

	Auto();
	if (camera_auto == 0)
		Camera();
	else
		CameraAuto();
	if (y >= 180.0f || health<=0)
	{
		vx = 0;
		vy = 0;
		Reset = true;
	}
	//DebugOut(L"state_auto=%d\n", state_auto);
	//DebugOut(L"IsUp=%d\nIsDown=%d\n", IsUp,IsDown);
	//DebugOut(L"state=%d\n", state);
	//DebugOut(L"up=%d\ndown=%d\n", IsUp, IsDown);
	//DebugOut(L"x=%f\ny=%f\n", x, y);
	//DebugOut(L"heart=%d\n", heart);
	//DebugOut(L"stair=%d\n", stair);
}

void CSimon::Render()
{
	int ani;
	bool IsRenDer = false;
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
				if (skill == true && now - FrameWeapon < 3 * FRAME_TIME_WHIP)
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
					animations[ani]->Render(x, y, color);
				}
				else
				{
					if (fight == true)
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
						if (nx > 0)whip->SetStateWhip(WHIP_STATE_RIGHT);
						else whip->SetStateWhip(WHIP_STATE_LEFT);
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
			if (skill)
			{
				if (now - FrameWeapon > 600) skill = false;
				else weapon->Render();
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
				else if (skill == true && now - FrameWeapon < 450)
				{
					if (nx > 0)
						ani = SIMON_ANI_FIGHT_RIGHT;
					else
						ani = SIMON_ANI_FIGHT_LEFT;
				}
				else
				{
					if (fight == true)
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
				if (skill)
				{
					if (now - FrameWeapon > 600)	skill = false;
					else weapon->Render();
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
	RenderBoundingBox(100);
}

void CSimon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	DWORD t = GetTickCount() - whip->GetFrameWhip();
	if (vy < 0)
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
	}
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
		level1->GetSizeMap(min, max);
		SetState(SIMON_STATE_WALKING_RIGHT);
		if (x > max)
		{
			state_auto = -1;
			SetState(SIMON_STATE_IDLE);
			camera_auto = 3;
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
				level1->SetIsNext(true);
			}
		}
		else
		{
			if (x < simon_x)
			{
				simon_x = 0;
				level1->SetIsNext(true);
			}
		}
	}
}

void CSimon::Camera()
{
	CGame *game = CGame::GetInstance();
	float min;
	float max;
	level1->GetSizeMap(min, max);
	if (level1->GetScene() == SCENE_5 && x + 128.0f > max)
	{
		MeetBoss = true;
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
	/*float cx, cy;
	game->GetCamera(cx, cy);
	DebugOut(L"camera=%f\n", cx);*/
}

void CSimon::CameraAuto()
{
	CGame *game = CGame::GetInstance();
	float min;
	float max;
	level1->GetSizeMap(min, max);

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
			state_auto = 4;
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
			level1->SetIsNext(true);
		}
	}
	//float cx, cy;
	//game->GetCamera(cx, cy);
	//DebugOut(L"camera=%f\n", cx);
}

CSimon::CSimon()
{
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
}

CSimon * CSimon::GetInstance()
{
	if (__instance == NULL)
		__instance = new CSimon();
	return __instance;
}
