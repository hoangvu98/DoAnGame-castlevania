#include "Simon.h"
#include "debug.h"
#include "Candle.h"
#include "Game.h"
#include "Panther.h"
#include "HidenObject.h"
#include "EntranceLevel.h"
#include "Ghoul.h"
DWORD FrameCollusion;
int color = 255;
float stair_x = 0;
int nx1;
CSimon *CSimon::__instance = NULL;
void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	CGameObject::Update(dt);
	CEntranceLevel *level1 = CEntranceLevel::GetInstance();
	CGame *game = CGame::GetInstance();
	float widthofmap;
	float heightofmap;
	level1->GetSizeOfMap(widthofmap, heightofmap);
	if (stair == 0)
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
	if (stair != 2)
		stair = 0;
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObject, coEvents);

	if (fight == true)
	{
		whip->SetPosition(x, y);
		DWORD t = GetTickCount() - whip->GetFrameWhip();
		if (t >= 300)
		{
			whip->fight = true;
			if (t >= 450)
			{
				fight = false;
				whip->fight = false;
			}
		}
		whip->Update(dt, coObject);
	}
	if (skill)
	{
		weapon->Update(dt);
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
				if (stair != 2)
					stair = 1;
				if (stair == 2 && IsDown != 2)
					IsDown = 1;
			}
			else if (hidenobject->GetState() == HIDENOBJECT_STATE_STAIR_DOWN)
			{
				nx1 = hidenobject->nx;
				stair_x = hidenobject->GetStair_X();
				if (stair != 2)
					stair = 3;
				if (stair == 2 && IsUp != 2)
					IsUp = 1;
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT e = coEvents[i];
		if (dynamic_cast<CCandle *> (e->obj))
		{
			coEvents.erase(coEvents.begin() + i);
			i--;
		}
		else if (dynamic_cast<CHidenObject *> (e->obj))
		{
			CHidenObject *hidenobject = dynamic_cast<CHidenObject *>(e->obj);
			if (hidenobject->GetState() != HIDENOBJECT_STATE_NORMAL)
			{
				coEvents.erase(coEvents.begin() + i);
				i--;
			}
		}
	}
	if (coEvents.size() == 0)
	{
		/*x += dx;
		y += dy;*/
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
				/*if (hidenobject->GetState() == HIDENOBJECT_STATE_NORMAL)
				{*/
				x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;
				test = false;
				DWORD now = GetTickCount();
				if (now - FrameCollusion > 100)
				{
					if (nx != 0) vx = 0;
					if (ny != 0) {
						vy = 0; jump = true;
					}
					if (collusion == 1 && ny < 0)
						if (state == SIMON_STATE_COLLUSION)
							SetState(SIMON_STATE_KNEE);
				}
				//}
			}
			else if (dynamic_cast<CHeart *>(e->obj))
			{
				CItems *items = dynamic_cast<CHeart *>(e->obj);
				items->SetState(ITEM_STATE_DELETE);
			}
			else if (dynamic_cast<CMoneyBag *>(e->obj))
			{
				CItems *items = dynamic_cast<CMoneyBag *>(e->obj);
				items->SetState(ITEM_STATE_DELETE);
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
			else if (dynamic_cast<CDoor *>(e->obj))
			{
				level1->SetScene(SCENE_3);
				CDoor *door = dynamic_cast<CDoor *>(e->obj);
				door->SetState(DOOR_STATE_OPEN);
			}
			else if (dynamic_cast<CPanther *> (e->obj))
			{
				if (collusion == 0)
				{
					CPanther *panther = dynamic_cast<CPanther *>(e->obj);
					collusion = 1;
					SetState(SIMON_STATE_COLLUSION);
					collusion_nx = nx;
					FrameCollusion = GetTickCount();
				}
			}
			else if (dynamic_cast<CGhoul *> (e->obj))
			{
				if (collusion == 0)
				{
					CGhoul *ghoul = dynamic_cast<CGhoul *>(e->obj);
					collusion = 1;
					SetState(SIMON_STATE_COLLUSION);
					collusion_nx = nx;
					FrameCollusion = GetTickCount();
				}
			}
		}
	}
	if (test)
	{
		x += dx;
		y += dy;
		test = true;
	}
	if (state_auto == 1)
	{
		if (x > stair_x)
		{
			SetState(SIMON_STATE_WALKING_LEFT);
			state_auto = 2;
		}
		else if (x < stair_x)
		{
			state_auto == 3;
			SetState(state = SIMON_STATE_WALKING_RIGHT);
		}
	}
	else if (state_auto == 2)
	{
		if (x <= stair_x)
		{
			if (stair == 1)
			{
				SetState(SIMON_STATE_STAIR_UP);
				x = stair_x;
				nx = nx1;
				x += 8;
			}
			else
			{
				SetState(SIMON_STATE_STAIR_DOWN);
				x = stair_x;
				nx = nx1;
				x -= 8;
			}
			SetFrameStair();
			GetPosition(simon_x, simon_y);
			stair = 2;
			state_auto = 0;
		}
	}
	else if (state_auto == 3)
	{
		if (x >= stair_x)
		{
			if (stair == 1)
			{
				SetState(SIMON_STATE_STAIR_UP);
				x = stair_x;
				nx = nx1;
				x += 8;
			}
			else
			{
				SetState(SIMON_STATE_STAIR_DOWN);
				x = stair_x;
				nx = nx1;
				x -= 8;
			}
			SetFrameStair();
			GetPosition(simon_x, simon_y);
			stair = 2;
			state_auto = 0;
		}
	}
	if (state == SIMON_STATE_STAIR_DOWN || state == SIMON_STATE_STAIR_UP)
	{
		DWORD now = GetTickCount();
		test_stair = now - FrameStair;
	}
	else
		test_stair = 0;
	if (state != SIMON_STATE_STAIR_DOWN && state != SIMON_STATE_STAIR_UP)
	{
		float cx, cy;
		game->GetCamera(cx, cy);
		if (x > 100.0f)
		{
			game->SetCamera(x - 100.0f, 0.0f);
			if (cx < 0) game->SetCamera(0.0f, 0.0f);
			if (cx + 256.0f >= widthofmap)
			{
				game->SetCamera(cx, 0.0f);
				if (x < 620.0f) game->SetCamera(x - 100.0f, 0.0f);
			}
		}
	}
	else
	{
		float x1;
		if (nx > 0)
			x1 = simon_x + (float)8 / TIME_STAIR * test_stair;
		else
			x1 = simon_x - (float)8 / TIME_STAIR * test_stair;
		float cx, cy;
		game->GetCamera(cx, cy);
		if (x1 > 100.0f)
		{
			game->SetCamera(x1 - 100.0f, 0.0f);
			if (cx < 0) game->SetCamera(0.0f, 0.0f);
			if (cx + 256.0f >= widthofmap)
			{
				game->SetCamera(cx, 0.0f);
				if (x1 < 620.0f) game->SetCamera(x1 - 100.0f, 0.0f);
			}
		}
	}

	//sau nay se sua thanh CDoor
	//if (x >= 704.0f)
	//{
	//	
	//	level1->SetScene(SCENE_2);
	//	SetPosition(10.0f, 80.0f);
	//	game->SetCamera(0.0f, 0.0f);
	//	//level1->Update();
	//}
	DWORD now = GetTickCount();
	if (now - FrameCollusion > 1000 && collusion == 1)
	{
		collusion = 2;
	}
	else if (now - FrameCollusion > 3000)
	{
		collusion = 0;
	}
}

void CSimon::Render()
{
	int ani;
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
		if (stair == 2 || state_auto == 4)
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
				if (skill == true && now - FrameWeapon < 450)
				{
					if (nx > 0)
						ani = SIMON_ANI_STAIR_FIGHT_RIGHT;
					else
						ani = SIMON_ANI_STAIR_FIGHT_LEFT;
					animations[ani]->Render(x, y, color);
				}
				else
				{
					if (fight == true)
					{
						if (nx > 0)
							ani = SIMON_ANI_STAIR_FIGHT_RIGHT;
						else
							ani = SIMON_ANI_STAIR_FIGHT_LEFT;
						whip->Render();
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
						else
						{
							if (nx > 0)
								ani = SIMON_ANI_STAIR_IDLE_DOWN_RIGHT;
							else
								ani = SIMON_ANI_STAIR_IDLE_DOWN_LEFT;
						}
					}
				}

			}
			if (state == SIMON_STATE_STAIR_UP)
			{
				if (animations[ani]->GetCureentFrame() == 0 && test == 0)
				{
					test = 1;
					if (nx > 0)
						x += 8;
					else
						x -= 8;
					y -= 8;
				}
				else if (animations[ani]->GetCureentFrame() == 1 && test == 1)
					test = 0;
			}
			else if (state == SIMON_STATE_STAIR_DOWN)
			{
				if (animations[ani]->GetCureentFrame() == 0 && test == 0)
					test = 1;
				else if (animations[ani]->GetCureentFrame() == 1 && test == 1)
				{
					test = 0;
					if (nx > 0)
						x += 8;
					else
						x -= 8;
					y += 8;
				}
			}
			if (skill)
			{
				if (now - FrameWeapon > 1000)	skill = false;
				else weapon->Render();
			}
			animations[ani]->Render(x, y, color);
		}
		else
		{
			if (state == SIMON_STATE_UPDATE)
			{

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
				if (skill == true && now - FrameWeapon < 450)
				{
					if (nx > 0)
						ani = SIMON_ANI_FIGHT_RIGHT;
					else
						ani = SIMON_ANI_FIGHT_LEFT;
					animations[ani]->Render(x, y, color);
				}
				else
				{
					if (fight == true)
					{
						if (vx == 0)
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
						}
						if (nx > 0)whip->SetStateWhip(WHIP_STATE_RIGHT);
						else whip->SetStateWhip(WHIP_STATE_LEFT);
						animations[ani]->Render(x, y, color);
						whip->Render();
					}
					else
					{
						if (vx == 0)
						{
							if (mx == 1)
							{
								if (nx > 0)
									ani = SIMON_ANI_JUMP_RIGHT; //SIMON_ANI_KNEE_RIGHT
								else
									ani = SIMON_ANI_JUMP_LEFT; //SIMON_ANI_KNEE_LEFT
							}
							else
							{
								if (nx > 0)
									ani = SIMON_ANI_IDLE_RIGHT;
								else
									ani = SIMON_ANI_IDLE_LEFT;
							}
						}
						else
						{
							if (nx > 0)
								ani = SIMON_ANI_WALKING_RIGHT;
							else
								ani = SIMON_ANI_WALKING_LEFT;
						}
						if (vy < 0 && nx < 0)
							ani = SIMON_ANI_JUMP_LEFT;
						else if (vy < 0 && nx > 0)
							ani = SIMON_ANI_JUMP_RIGHT;
						animations[ani]->Render(x, y, color);
					}
				}
				if (skill)
				{
					if (now - FrameWeapon > 1000)	skill = false;
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
				animations[ani]->Render(x, y, color);
				color = 150;
			}
			else
			{
				animations[ani]->Render(x, y, color);
				color = 200;
			}
		}
		else if (state == SIMON_STATE_COLLUSION)
		{
			if (nx > 0)
				ani = SIMON_ANI_COLLUSION_RIGHT;
			else
				ani = SIMON_ANI_COLLUSION_LEFT;
			animations[ani]->Render(x, y, 255);

		}
	}
	DebugOut(L"ani=%d\n", ani);
	RenderBoundingBox(100);
}

void CSimon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
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

int CSimon::GetPreviousState()
{
	return previousstate;
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
	case SIMON_STATE_STAIR_UP:
		vx = 0;
		vy = 0;
		break;
	case SIMON_STATE_STAIR_DOWN:
		vx = 0;
		vy = 0;
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
	}
}

CSimon * CSimon::GetInstance()
{
	if (__instance == NULL)
		__instance = new CSimon();
	return __instance;
}
