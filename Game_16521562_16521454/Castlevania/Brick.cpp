#include "Brick.h"
#include "Simon.h"


CBrick::CBrick(float x, float y)
{
	SetPosition(x, y);
	AddAnimation(17000);
	AddAnimation(17001);
	del = 0;
	render = false;
	loop = 0;
	breakingwall = new CBreakingWall[4];
	item = new CPotRoast();
	item->SetPosition(1792.0f, 147.0f);
	item->SetState(ITEM_STATE_ITEM);

	for (int i = 0; i < 4; i++)
	{
		breakingwall[i].SetPosition(x + 2, y + 2);
		breakingwall[i].SetFall(false);
	}

	float tmp_x, tmp_y;
	breakingwall[0].GetPosition(tmp_x, tmp_y);
	breakingwall[0].SetSpeed(0.1f, 0.02f);
	breakingwall[0].SetHeight(tmp_y - 10);
	breakingwall[0].Setnx(1);

	breakingwall[1].GetPosition(tmp_x, tmp_y);
	breakingwall[1].SetSpeed(0.15f, 0.02f);
	breakingwall[1].SetHeight(tmp_y - 9);
	breakingwall[1].Setnx(1);

	breakingwall[2].GetPosition(tmp_x, tmp_y);
	breakingwall[2].SetSpeed(0.2f, 0.02f);
	breakingwall[2].SetHeight(tmp_y - 8);
	breakingwall[2].Setnx(-1);

	breakingwall[3].SetSpeed(0.12f, 0.02f);
	breakingwall[3].GetPosition(tmp_x, tmp_y);
	breakingwall[3].SetHeight(tmp_y - 7);
	breakingwall[3].Setnx(-1);
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == BRICK_STATE_HALF || state == BRICK_STATE_DISAPPEAR)
	{
		for (int i = 0; i < 4; i++)
			breakingwall[i].Update(dt);
		if (loop <= 100)
		{
			render = true;
			loop++;
		}
		else
		{
			render = false;
			//loop = 0;
			for (int i = 0; i < 4; i++)
			{
				breakingwall[i].SetPosition(x + 2, y + 2);
				breakingwall[i].SetFall(false);
			}
		}
	}
	//DebugOut(L"state %d\n", state);
	if (state == BRICK_STATE_DISAPPEAR)
	{
		CSimon *simon = CSimon::GetInstance();
		CCells *cells = simon->map->GetCell();
		cells->InitCells(item);
		simon->map->SetCell(cells);

		state = BRICK_STATE_DELETE;
	}
}

void CBrick::Render()
{
	if (state == BRICK_STATE_FULL)
		animations[BRICK_ANI_FULL]->Render(x, y);
	else if (state == BRICK_STATE_HALF)
	{
		animations[BRICK_ANI_HALF]->Render(x, y);
		if (render == true)
			for (int i = 0; i < 4; i++)
				breakingwall[i].Render();
	}
	else if (state == BRICK_STATE_DISAPPEAR)
	{
		if (render == true)
			for (int i = 0; i < 4; i++)
				breakingwall[i].Render();
		if (loop >= 100) render = 0;
	}
}

void CBrick::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BRICK_BBOX_WIDTH;
	bottom = y + BRICK_BBOX_HEIGHT;

}