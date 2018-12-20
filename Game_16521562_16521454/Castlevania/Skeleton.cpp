#include "Skeleton.h"
#include "Simon.h"
#include "Candle.h"
#include "HidenObject.h"
#include "Door.h"
#include "debug.h"

CSkeleton::CSkeleton()
{
}

CSkeleton::CSkeleton(float x, float y)
{
	health = 1;
	damage = 4;
	SetPosition(x, y);
	AddAnimation(220011); //ani left
	AddAnimation(220012); // ani right
	for (int i = 0; i < 3; i++)
		bone.push_back(new CBone());

	for (int i = 0; i < 3; i++)
	{
		bone[i]->SetPosition(x + 5.0f, y + 10.0f);
		bone[i]->InitHeight();
	}

	bone[0]->SetSpeed(0.02f, 0.1f);
	bone[1]->SetSpeed(0.03f, 0.1f);
	bone[2]->SetSpeed(0.04, 0.1f);

	number = 0;

	fire = false;

	jump = false;

	is_back = false;

	start_to_throw = GetTickCount();
}

void CSkeleton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	

	CSimon *simon = CSimon::GetInstance();
	CMonster::Update(dt, coObjects);
	if (state != MONSTER_STATE_DELETE && state != MONSTER_STATE_DISAPPEAR)
	{
		DWORD now = GetTickCount();

		if (simon->x < this->x) Setnx(-1);
		else Setnx(1);
		
		if (is_back == true)
		{
			SetMinMax();
			SetLeftRight();
			is_back = false;
		}

		if (isChange == false)
			if ((this->x < min || this->x > max) && jump == false)
				vx = -vx;

		if (abs(simon->x - this->x) < DISTANCE_WITH_SIMON && jump == false) //chay lui khi simon den gan
		{
			isChange = true;
			if ((nx > 0 && vx > 0) || (nx < 0 && vx < 0))
			{
				vx = -vx;
				is_back = true;
			}
		}
		else isChange = false;
		if ((simon->x  < left || simon->x > right) && jump == false) // Chay tro lai khi simon da di ra xa
		{
			isChange = true;
			if ((nx > 0 && vx < 0) || (nx < 0 && vx > 0))
			{
				vx = -vx;
				is_back = true;
			}
		}
		else isChange = false;

		
		CGameObject::Update(dt);
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		vy += SKELETON_GRAVITY * dt;

		coEventsResult.clear();
		CalcPotentialCollisions(coObjects, coEvents);
		
		

		for (UINT i = 0; i < coEvents.size(); i++)//Xoa cac doi tuong khong can thiet
		{
			LPCOLLISIONEVENT e = coEvents[i];
			if (dynamic_cast<CCandle *>(e->obj) || dynamic_cast<CDoor *>(e->obj))
			{
				coEvents.erase(coEvents.begin() + i);
				i--;
			}
			else if (dynamic_cast<CHidenObject *>(e->obj))
			{
				CHidenObject *hobj = dynamic_cast<CHidenObject *>(e->obj);
				if (hobj->GetState() == HIDENOBJECT_STATE_STAIR_UP ||
					hobj->GetState() == HIDENOBJECT_STATE_STAIR_DOWN)
				{
					coEvents.erase(coEvents.begin() + i);
					i--;
				}
			}
		}

		bool test = true;
		
		if (coEvents.size() != 0)
		{
			float min_tx, min_ty, nx = 0, ny;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			//if (nx != 0) vx = 0;
			if (ny != 0) vy = 0;

			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<CHidenObject *>(e->obj))
				{
					CHidenObject *hobj = dynamic_cast<CHidenObject *>(e->obj);
					if (hobj->GetState() == HIDENOBJECT_STATE_NORMAL)
					{
						this->x += min_tx * dx + nx * 0.4f;
						this->y += min_ty * dy + ny * 0.4f;
						//jump = false;
						test = false;
					}
					else if (hobj->GetState() == HIDENOBJECT_STATE_JUMP)
					{
						jump = true;
						jump_time = GetTickCount();
					}
				}
			}
		}
		/*int random = rand() % 3;
		number = random;
		if (now - start_to_throw >= TIME_TO_THROW_BONES && fire == false)
		{
			SetState(SKELETON_STATE_THROW_BONE);
			for (int i = 0; i < number; i++)
			{
				bone[i]->SetPosition(this->x + 5.0f, this->y + 10.0f);
				bone[i]->InitHeight();
				if (this->nx > 0) bone[i]->nx = 1;
				else bone[i]->nx = -1;
			}
			fire = true;
			start_to_throw = GetTickCount();
		}
		else
			if (now - start_to_throw >= 4000)
			{
				fire = false;
				for (int i = 0; i < number; i++)
					bone[i]->SetFall(false);
				if (this->nx > 0) SetState(SKELETON_STATE_WALKING_RIGHT);
				else SetState(SKELETON_STATE_WALKING_LEFT);
				start_to_throw = GetTickCount();
			}
		if (fire == true)
			for (int i = 0; i < number; i++)
				bone[i]->Update(dt, coObjects);*/

		if (jump == true)
		{
			SetState(SKELETON_STATE_JUMP);
			if (now - jump_time >= 280)
				jump = false;
		}
		else
			vy += SKELETON_GRAVITY * dt;

		if (test == true)
		{
			this->x += dx;
			this->y += dy;
		}
	}
	DebugOut(L"min %f, x %f, max %f\n", min, x, max);
}

void CSkeleton::Render()
{
	if (nx > 0)
		animations[SKELETON_ANI_WALKING_RIGHT]->Render(x, y);
	else
		if (nx < 0)animations[SKELETON_ANI_WALKING_LEFT]->Render(x, y);

	if (fire == true)
		for (int i = 0; i < number; i++)
			bone[i]->Render();
	//RenderBoundingBox(200);
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
		//nx = -1;
		vx = -SKELETON_WALKING_SPEED;
		break;
	case SKELETON_STATE_WALKING_RIGHT:
		//nx = 1;
		vx = SKELETON_WALKING_SPEED;
		break;
	case SKELETON_STATE_JUMP:
		//vx = SKELETON_WALKING_SPEED;
		vy = -SKELETON_JUMP_SPEED_Y;
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

void CSkeleton::SetLeftRight()
{
	left = x - MOVING_AREA_WIDTH;
	right = x + MOVING_AREA_WIDTH;
}


CSkeleton::~CSkeleton()
{
}
