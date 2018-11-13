#include "Simon.h"
#include "debug.h"
#include "Candle.h"
#include "Game.h"
#include "HidenObject.h"
#include "EntranceLevel.h"
void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	CGameObject::Update(dt);
	CEntranceLevel *level1 = CEntranceLevel::GetInstance();
	CGame *game = CGame::GetInstance();
	float widthofmap;
	float heightofmap;
	level1->GetSizeOfMap(widthofmap, heightofmap);
	vy += SIMON_GRAVITY;
	if (state != SIMON_STATE_KNEE && previousstate== SIMON_STATE_KNEE)
	{
		previousstate = NULL;
		SetPosition(x, y - 9);
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObject, coEvents);

	if (fight == true)
	{
		if (nx < 0)
			whip->SetPosition(x - 22, y + 5);
		else
			whip->SetPosition(x + 22, y + 5);
		whip->Update(dt, coObject);
		if (whip->fight == true)
		{
			fight = false;
			whip->fight = false;
		}
	}
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{

		float min_tx, min_ty, nx = 0, ny;
		
		for (UINT i = 0; i < coEvents.size(); i++)
		{
			LPCOLLISIONEVENT e = coEvents[i];
			if (dynamic_cast<CCandle *> (e->obj))
				coEvents.erase(coEvents.begin() + i);
		}
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;
		
		
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CHidenObject *> (e->obj))
			{
				if (nx != 0) vx = 0;
				if (ny != 0) {
					vy = 0; jump = true;
				}
			}
			/*else if (dynamic_cast<CItem *> (e->obj))
			{
				CItem *item = dynamic_cast<CItem *>(e->obj);
				if(item->state== ITEM_STATE_HEART_SMALL) heart++;
				if (item->state == ITEM_STATE_HEART_BIG) heart+=2;
				if (item->state == ITEM_STATE_WHIP_UPDATE)
				{
					state_update = state;
					if(whip->state==WHITE_WHIP)
						whip->SetState(BLUE_WHIP);
					else if(whip->state == BLUE_WHIP)
						whip->SetState(YELLOW_WHIP);
					else if (whip->state == YELLOW_WHIP)
						whip->SetState(RED_WHIP);
					SetState(SIMON_STATE_UPDATE);
					FrameUpdate = GetTickCount();
				}
				x += dx;
				y += dy;
				item->SetState(ITEM_STATE_DELETE);
			}*/
			else if (dynamic_cast<CHeart *>(e->obj))
			{
				CItems *items = dynamic_cast<CHeart *>(e->obj);
				x += dx;
				y += dy;
				items->SetState(ITEM_STATE_DELETE);
			}
			else if (dynamic_cast<CDagger *>(e->obj))
			{
				OnSkill = true;
				CItems *items = dynamic_cast<CDagger *>(e->obj);
				weapon = new CDagger();
				weapon->LoadData();
				x += dx;
				y += dy;
				items->SetState(ITEM_STATE_DELETE);
			}
			else if (dynamic_cast<CDoor *>(e->obj))
			{
				level1->SetScene(SCENE_2);
				SetPosition(10.0f, 80.0f);
				game->SetCamera(0.0f, 0.0f);
			}

		}
	}
	//DebugOut(L"heart = %d\n", heart);
	
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
	DebugOut(L"x = %f, y = %f\n", x, y);
	//sau nay se sua thanh CDoor
	//if (x >= 704.0f)
	//{
	//	
	//	level1->SetScene(SCENE_2);
	//	SetPosition(10.0f, 80.0f);
	//	game->SetCamera(0.0f, 0.0f);
	//	//level1->Update();
	//}
}

void CSimon::Render()
{
	int ani;
	if (state == SIMON_STATE_UPDATE)
	{
		if (state_update == SIMON_STATE_WALKING_LEFT)
			ani = SIMON_ANI_WALKING_LEFT;
		else
			ani = SIMON_ANI_WALKING_RIGHT;
		if (alpha == 255)
		{
			animations[ani]->Render_now(x, y, 255, alpha, 28,36);
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
		if (skill==true && now-FrameWeapon<300)
		{
			if (nx > 0)
				ani = SIMON_ANI_FIGHT_RIGHT;
			else
				ani = SIMON_ANI_FIGHT_LEFT;
			animations[ani]->Render(x, y, 255);
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
				whip->Render();
				animations[ani]->Render(x, y, 255);
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
				animations[ani]->Render(x, y, 255);
			}
		}
	}
	DWORD now = GetTickCount();
	if (skill)
	{
		if (now - FrameWeapon > 5000)
		{
			skill = false;
		}
		else
		{
			float temp_x, temp_y;
			weapon->GetPosition(temp_x, temp_y);
			weapon->SetPosition(temp_x + 5, temp_y);
			weapon->Render();
		}
	}
}

void CSimon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	if (vx == 0 && mx == 1)
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
		if (mx == 0 )
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
		if(previousstate!= SIMON_STATE_KNEE)
			SetPosition(x, y + 9);
		previousstate = SIMON_STATE_KNEE;
		vx = 0;
		mx = 1;
		break;
	case SIMON_STATE_UPDATE:
		vx = 0;
		break;
	}
}
