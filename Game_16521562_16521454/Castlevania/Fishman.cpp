#include "Fishman.h"

CFishman::CFishman()
{
	AddAnimation(18000);
	AddAnimation(18001);
	AddAnimation(18002);
	AddAnimation(18003);
	AddAnimation(18004);
	AddAnimation(18005);
	bullet = new CBullet();
	i = 0;
	j = 0;
	fire = false;
}

void CFishman::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + FISHMAN_BBOX_WIDTH;
	bottom = y + FISHMAN_BBOX_HEIGHT;
}

void CFishman::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
	vy += FISHMAN_GRAVITY * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		x += dx;
		x += min_tx * dx + nx * 0.4f;
		if (ny < 0)
		{
			y += min_ty * dy + ny * 0.4f;
			if (fire == false)
				if (this->nx < 0 && this->x >= FISHMAN_TURN) SetState(FISHMAN_STATE_WALKING_LEFT);
				else SetState(FISHMAN_STATE_WALKING_RIGHT);

			if (i >= 25 && fire == false)
			{
				SetState(FISHMAN_STATE_FIRE);
				bullet->SetPosition(x, y);
				bullet->Setnx(this->nx);
				i = 0;
			}
			else if (fire == false) i++;
			if (fire == true)
			{
				if (j >= 50)
				{
					fire = false;
					j = 0;
				}
				else
				{
					j++;
					bullet->Update(dt, coObjects);
				}
			}
		}
		else
			y += dy;
	}
}

void CFishman::Render()
{
	int ani;
	if (vx == 0)
	{
		if (nx < 0) ani = FISHMAN_ANI_FIRE_LEFT;
		else ani = FISHMAN_ANI_FIRE_RIGHT;
		bullet->Render();
	}
	else
	{
		if (nx < 0) ani = FISHMAN_ANI_WALKING_LEFT;
		else ani = FISHMAN_ANI_WALKING_RIGHT;
	}

	if (vy < 0)
	{
		if (nx < 0) ani = FISHMAN_ANI_JUMP_LEFT;
		else ani = FISHMAN_ANI_JUMP_RIGHT;

	}
	animations[ani]->Render(x, y);
}

void CFishman::SetState(int state)
{
	CGameObject::SetState(state);
	CGameObject::SetState(state);
	switch (state)
	{
	case FISHMAN_STATE_WALKING_RIGHT:
		vx = FISHMAN_WALKING_SPEED;
		nx = 1;
		break;
	case FISHMAN_STATE_WALKING_LEFT:
		vx = -FISHMAN_WALKING_SPEED;
		nx = -1;
		break;
	case FISHMAN_STATE_JUMP:
		vy = -FISHMAN_JUMP_SPEED_Y;
		break;
	case FISHMAN_STATE_FIRE:
		vx = 0;
		fire = true;
		break;
	}
}
