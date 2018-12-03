#include "Panther.h"
#include "debug.h"
#include "Candle.h"
#include "Game.h"
void CPanther::InitMovingArea()
{
	/*temp_x = x;
	temp_y = y;*/
	left = x - DISTANCE;
	top = y;
	right = left + MOVING_AREA_WIDTH;
	bottom = top + MOVING_AREA_HEIGHT;
}

CPanther::CPanther()
{
	AddAnimation(4000);
	AddAnimation(4001);
	AddAnimation(4002);
	AddAnimation(4003);
	AddAnimation(4004);
	AddAnimation(4005);
	reset = false;
}

void CPanther::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + PANTHER_BBOX_WIDTH;
	bottom = y + PANTHER_BBOX_HEIGHT;
}

void CPanther::Reset()
{
	CSimon *simon = CSimon::GetInstance();

	SetState(PANTHER_STATE_IDLE);
	SetPosition(temp_x, temp_y);
	Setnx(-nx);
	SetTurn(0);
	SetJump(false);
	InitMovingArea();
}

void CPanther::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	float cx, cy;
	CGame *game = CGame::GetInstance();
	game->GetCamera(cx, cy);
	if (cx + VIEWPORT_WIDTH < left || cx > right)/*&& right > cx + VIEWPORT_WIDTH) */
		/*(left < cx && */ /*&& reset == false*/ //View port ko dung moving area
		reset = true;
	DebugOut(L"right = %f, cx = %f\n");
	DebugOut(L"left = %f, cx = %f\n");
	/*if (state != PANTHER_STATE_DIE)
	{*/
	CGameObject::Update(dt);
	vy += PANTHER_GRAVITY * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);


	for (UINT i = 0; i < coEvents.size(); i++)
	{
		if (dynamic_cast<CHidenObject *> (coEvents[i]->obj))
		{
			CHidenObject *hobj = dynamic_cast<CHidenObject *> (coEvents[i]->obj);
			if (hobj->GetState() == HIDENOBJECT_STATE_STAIR_DOWN ||
				hobj->GetState() == HIDENOBJECT_STATE_STAIR_UP)
				coEvents.erase(coEvents.begin() + i);
		}
		else if (dynamic_cast<CCandle *> (coEvents[i]->obj))
			coEvents.erase(coEvents.begin() + i);
	}

	if (coEvents.size() == 0)
	{
		if (turn == 1)
		{
			Setnx(-Getnx());
			turn = 0;
		}
		jump = false;
		this->x += dx;
		this->y += dy;

		/*if ((this->x < cx || this->x > cx + VIEWPORT_WIDTH) && run == true)
		{
			SetState(PANTHER_STATE_DIE);
			run = false;
			reset = true;
			DebugOut(L"Da set state ve die\n");
		}*/

	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		this->x += min_tx * dx + nx * 0.4f;
		this->y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		float x, y;
		CSimon *simon = CSimon::GetInstance();
		simon->GetPosition(x, y);

		if ((x >= left && x <= right)
			&& Getnx() < 0 && jump == false)
			SetState(PANTHER_STATE_WALKING_LEFT);
		else if ((x >= left && x <= right) && Getnx() > 0 && jump == false)
			SetState(PANTHER_STATE_WALKING_RIGHT);

		if ((x < left && x < right) && run == true && Getnx() < 0)
			SetState(PANTHER_STATE_WALKING_LEFT);
		else if ((x < left && x < right) && run == true && Getnx() > 0)
			SetState(PANTHER_STATE_WALKING_RIGHT);

		if (turn == 0 && jump == true)
			turn = 1;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			if (dynamic_cast<CHidenObject *> (coEventsResult[i]->obj))
			{
				CHidenObject *hobj = dynamic_cast<CHidenObject *> (coEventsResult[i]->obj);
				if (hobj->GetState() == HIDENOBJECT_STATE_JUMP)
				{
					jump = true;
					run = true;
					this->x += dx;
					this->y += dy;
				}
			}
		}
	}
	if (jump == true && Getnx() < 0)
		SetState(PANTHER_STATE_JUMP_LEFT);
	else if (jump == true && Getnx() > 0)
		SetState(PANTHER_STATE_JUMP_RIGHT);
	//}
	if (reset == true)
	{
		Reset();
		reset = false;
		//DebugOut(L"Da goi reset\n");
	}
	//DebugOut(L"state = %d\n", state);
}

void CPanther::Render()
{
	int ani;
	if (state == PANTHER_STATE_IDLE)
	{
		if (nx > 0) ani = PANTHER_ANI_IDLE_RIGHT;
		else ani = PANTHER_ANI_IDLE_LEFT;
	}
	if (state == PANTHER_STATE_JUMP_RIGHT)
	{
		ani = PANTHER_ANI_JUMP_RIGHT;
	}
	if (state == PANTHER_STATE_JUMP_LEFT)
	{
		ani = PANTHER_ANI_JUMP_LEFT;
	}
	if (state == PANTHER_STATE_WALKING_RIGHT)
	{
		ani = PANTHER_ANI_WALKING_RIGHT;
	}
	if (state == PANTHER_STATE_WALKING_LEFT)
	{
		ani = PANTHER_ANI_WALKING_LEFT;
	}
	animations[ani]->Render(x, y);
}

void CPanther::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PANTHER_STATE_WALKING_RIGHT:
		vx = PANTHER_WALKING_SPEED;
		nx = 1;
		break;
	case PANTHER_STATE_WALKING_LEFT:
		vx = -PANTHER_WALKING_SPEED;
		nx = -1;
		break;
	case PANTHER_STATE_JUMP_RIGHT:
		vy = -PANTHER_JUMP_SPEED_Y;
		vx = PANTHER_JUMP_SPEED_X;
		nx = 1;
		break;
	case PANTHER_STATE_JUMP_LEFT:
		vy = -PANTHER_JUMP_SPEED_Y;
		vx = -PANTHER_JUMP_SPEED_X;
		nx = -1;
		break;
	case PANTHER_STATE_IDLE:
		vx = 0;
		break;
	}
}

void CPanther::GetMovingArea(float & left, float & top, float & right, float & bottom)
{
	left = this->left;
	top = this->top;
	right = this->right;
	bottom = this->bottom;
}
