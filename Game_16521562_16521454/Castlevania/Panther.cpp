#include "Panther.h"
#include "debug.h"
void CPanther::InitMovingArea()
{
	temp_x = x;
	temp_y = y;
	left = x - DISTANCE;
	top = y;
	right = left + MOVING_AREA_WIDTH;
	bottom = top + MOVING_AREA_HEIGHT;
}

void CPanther::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + PANTHER_BBOX_WIDTH;
	bottom = y + PANTHER_BBOX_HEIGHT;
}

void CPanther::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
	vy += PANTHER_GRAVITY * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != PANTHER_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);
	float x, y;
	CSimon *simon = CSimon::GetInstance();
	simon->GetPosition(x, y);

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		if (dynamic_cast<CHidenObject *> (coEvents[i]->obj))
		{
			CHidenObject *hobj = dynamic_cast<CHidenObject *> (coEvents[i]->obj);
			if (hobj->GetState() == HIDENOBJECT_STATE_STAIR_DOWN ||
				hobj->GetState() == HIDENOBJECT_STATE_STAIR_UP)
				coEvents.erase(coEvents.begin() + i);
		}
		else if (dynamic_cast<CSimon *> (coEvents[i]->obj))
			coEvents.erase(coEvents.begin() + i);
	}
	
	if (coEvents.size() == 0)
	{	
		if (turn == 1)
		{
			Setnx(-Getnx());
			/*if (nx < 0) SetState(PANTHER_STATE_WALKING_LEFT);
			else SetState(PANTHER_STATE_WALKING_RIGHT);*/
			turn = 0;
		}
		jump = false;
		this->x += dx;
		this->y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		this->x += min_tx * dx + nx * 0.4f;
		this->y += min_ty * dy + ny * 0.4f;

		
		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		if (x >= left && Getnx() < 0 && jump == false)
			SetState(PANTHER_STATE_WALKING_LEFT);
		else if (x >= left && Getnx() > 0 && jump == false)
			SetState(PANTHER_STATE_WALKING_RIGHT);

		if (x < left && run == true && Getnx() < 0)
			SetState(PANTHER_STATE_WALKING_LEFT);
		else if (x < left && run == true && Getnx() > 0)
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
