#include "Skeleton.h"
#include "Simon.h"
#include "Candle.h"

CSkeleton::CSkeleton()
{
}

CSkeleton::CSkeleton(float x, float y)
{
	health = 1;
	damage = 1;
	SetPosition(x, y);
	AddAnimation(220011); //ani left
	AddAnimation(220012); // ani right
	bone = new CBone();

	bone->SetPosition(x + 5.0f, y + 10.0f);
	bone->InitHeight();
	fire = false;
	start_to_throw = GetTickCount();
}

void CSkeleton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float sx, sy;
	CSimon *simon = CSimon::GetInstance();
	simon->GetPosition(sx, sy);
	CMonster::Update(dt, coObjects);
	if (state != MONSTER_STATE_DISAPPEAR && state != MONSTER_STATE_DELETE)
	{
		DWORD now;
		now = GetTickCount();
		vy += SKELETON_GRAVITY * dt;
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		CalcPotentialCollisions(coObjects, coEvents);
		for (UINT i = 0; i < coEvents.size(); i++)
			if (dynamic_cast<CCandle *> (coEvents[i]->obj))
				coEvents.erase(coEvents.begin() + i);

		if (coEvents.size() == 0)
		{

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

			/*if (this->nx > 0 && fire == false)
				SetState(SKELETON_STATE_WALKING_RIGHT);
			else
				if (this->nx < 0 && fire == false)
					SetState(SKELETON_STATE_WALKING_LEFT);*/

			if (this->x < min || this->x > max)
				vx = -vx;

			if (now - start_to_throw >= TIME_TO_THROW_BONES && fire == false)
			{
				SetState(SKELETON_STATE_THROW_BONE);
				bone->SetPosition(this->x + 5.0f, this->y + 10.0f);
				fire = true;
				start_to_throw = GetTickCount();
			}
			else
				if (now - start_to_throw >= TIME_TO_THROW_BONES)
				{
					fire = false;
					bone->SetFall(false);
					if (this->nx > 0) SetState(SKELETON_STATE_WALKING_RIGHT);
					else SetState(SKELETON_STATE_WALKING_LEFT);
					start_to_throw = GetTickCount();
				}
			if (fire == true)
				bone->Update(dt, coObjects);
		}
	}
}

void CSkeleton::Render()
{
	if (nx > 0)
	{
		animations[SKELETON_ANI_WALKING_RIGHT]->Render(x, y);
		//start_to_throw = GetTickCount();
	}
	else
	{
		if (nx < 0)animations[SKELETON_ANI_WALKING_LEFT]->Render(x, y);
		//start_to_throw = GetTickCount();
	}

	if (vx == 0 && vy == 0)
		bone->Render();
	RenderBoundingBox(200);
}

void CSkeleton::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + SKELETON_BBOX_WIDTH;
	bottom = y + SKELETON_BBOX_HEIGHT;
}

void CSkeleton::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SKELETON_STATE_WALKING_LEFT:
		nx = -1;
		vx = -SKELETON_WALKING_SPEED;
		break;
	case SKELETON_STATE_WALKING_RIGHT:
		nx = 1;
		vx = SKELETON_WALKING_SPEED;
		break;
	case SKELETON_STATE_THROW_BONE:
		vx = 0;
		vy = 0;
		break;
	}
}

void CSkeleton::SetMinMax()
{
	min = x - DISTANCE;
	max = x + DISTANCE;
}


CSkeleton::~CSkeleton()
{
}
