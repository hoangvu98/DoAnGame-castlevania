#include "Cell.h"
#include "debug.h"
#include "Candle.h"
#include "Simon.h"
#include "Ghoul.h"
#include "HidenObject.h"
#include "BossBat.h"
#include "Bat.h"
#include "Fishman.h"
#include "Bullet.h"
#include "SpiritDracula.h"
#include "Dracula.h"
void CCell::SetObjects(LPGAMEOBJECT object)
{
	objects.push_back(object);
}
void CCell::XoaObject(int k)
{
	objects.erase(objects.begin() + k);
}

void CCell::Update(DWORD dt)
{
	for (UINT i = 0; i < objects.size(); i++)
		objects[i]->Update(dt);
}

void CCell::Render()
{
	for (UINT i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

CCell::CCell()
{
	width = CELL_WIDTH;
	height = CELL_HEIGHT;
	objects.clear();
}


CCell::~CCell()
{
}

CCells::CCells()
{
}

CCells::CCells(int row, int column)
{
	this->row = row;
	this->column = column;
	int i;
	cells = new CCell *[row];
	for (i = 0; i < row; i++)
		cells[i] = new CCell[column];
}

CCells::~CCells()
{
}

void CCells::InitCells(LPGAMEOBJECT object)
{
	if (dynamic_cast<CHidenObject *> (object))
	{
		CHidenObject *hidenobject = dynamic_cast<CHidenObject *>(object);
		if (hidenobject->GetState() == HIDENOBJECT_STATE_NORMAL)
		{
			float width, height, x, y;
			hidenobject->GetSize(width, height);
			hidenobject->GetPosition(x, y);
			int x1 = x / CELL_WIDTH;
			int x2 = (x + width) / CELL_WIDTH;
			int j = y / CELL_HEIGHT;
			for (int i = x1; i <= x2; i++)
			{
				hidenobject = new CHidenObject();
				hidenobject->SetState(HIDENOBJECT_STATE_NORMAL);
				hidenobject->SetPosition(i*CELL_WIDTH, y);
				hidenobject->SetSize(CELL_WIDTH, height);
				if (i == x1)
				{
					hidenobject->x = x;
				}
				if (x1 == x2)
				{
					hidenobject->SetSize(width, height);
				}
				else if (i == x1)
				{
					hidenobject->SetSize((i + 1)*CELL_WIDTH - x, height);
				}
				else if (i == x2)
				{
					hidenobject->SetSize(x + width - i * CELL_WIDTH, height);
				}
				cells[i][j].SetObjects(hidenobject);
			}
		}
		else
		{
			int x = object->x / CELL_WIDTH;
			int y = object->y / CELL_HEIGHT;
			cells[x][y].SetObjects(object);
		}
	}
	else
	{
		int x = object->x / CELL_WIDTH;
		int y = object->y / CELL_HEIGHT;
		cells[x][y].SetObjects(object);
	}
}

void CCells::GetListOfObjects(vector<LPGAMEOBJECT>* list_object, float cam_x, float cam_y)
{
	int xs, ys;
	int xe, ye;
	int i, j, k;
	xs = (int)cam_x / CELL_WIDTH;
	ys = (int)cam_y / CELL_HEIGHT;

	xe = (int)(cam_x + 256.0f) / CELL_WIDTH;
	ye = (int)(cam_y + 185.0f) / CELL_HEIGHT;
	for (i = xs; i <= xe; i++)
		for (j = ys; j <= ye; j++)
		{
			if (cells[i][j].GetObjects().size() != 0)
				for (k = 0; k < cells[i][j].GetObjects().size(); k++)
				{
					LPGAMEOBJECT e = cells[i][j].GetObjects()[k];
					if (dynamic_cast<CMonster *> (e))
					{
						int a = e->x / CELL_WIDTH;
						int b = e->y / CELL_HEIGHT;
						if (a != i || b != j)
						{
							cells[i][j].XoaObject(k);
							if (xs <= a && a <= xe && ys <= b && b <= ye)
								cells[a][b].SetObjects(e);
						}
					}
					if (dynamic_cast<CBullet *> (e))
					{
						int a = e->x / CELL_WIDTH;
						int b = e->y / CELL_HEIGHT;
						if (a != i || b != j)
						{
							cells[i][j].XoaObject(k);
							if (xs <= a && a <= xe)
								if (ys <= b && b <= ye)
									cells[a][b].SetObjects(e);
						}
					}
				}
		}

	for (i = xs; i <= xe; i++)
		for (j = ys; j <= ye; j++)
		{
			if (cells[i][j].GetObjects().size() != 0)
				for (k = 0; k < cells[i][j].GetObjects().size(); k++)
				{
					LPGAMEOBJECT e = cells[i][j].GetObjects()[k];
					if (dynamic_cast<CCandle *> (e))
					{
						if (e->state == CANDLE_STATE_DELETE)
						{
							CCandle *candle = dynamic_cast<CCandle *>(e);
							if (candle->GetItems()->GetState() != ITEM_STATE_DELETE)
								list_object->push_back(candle->GetItems());
						}
						else
						{
							list_object->push_back(e);
						}
					}
					else if (dynamic_cast<CGhoul *> (e))
					{
						if (e->state == MONSTER_STATE_DELETE)
						{
							CGhoul *ghoul = dynamic_cast<CGhoul *>(e);
							if (ghoul->GetItems() != NULL)
								if (ghoul->GetItems()->GetState() != ITEM_STATE_DELETE)
									list_object->push_back(ghoul->GetItems());
							list_object->push_back(e);
						}
						list_object->push_back(e);
					}
					else if (dynamic_cast<CFishman *>(e))
					{
						if (e->state == MONSTER_STATE_DELETE)
						{
							CFishman *fishman = dynamic_cast<CFishman *>(e);
							if (fishman->GetItems() != NULL)
								if (fishman->GetItems()->GetState() != ITEM_STATE_DELETE)
									list_object->push_back(fishman->GetItems());
							list_object->push_back(e);
						}
						list_object->push_back(e);
					}
					else if (dynamic_cast<CBossBat *> (e))
					{
						CSimon* simon = CSimon::GetInstance();
						if (simon->MeetBoss)
						{
							e->SetState(BOSS_BAT_STATE_fLY);
							CHidenObject *hidenobject;
							hidenobject = new CHidenObject();
							hidenobject->SetState(HIDENOBJECT_STATE_NORMAL);
							hidenobject->SetPosition(2570, 0);
							hidenobject->SetSize(6, 160);
							list_object->push_back(hidenobject);
						}
						list_object->push_back(e);
					}
					else if (dynamic_cast<CSpiritDracula *> (e))
					{
						CSpiritDracula *spirit_dracula = dynamic_cast<CSpiritDracula *> (e);
						list_object->push_back(spirit_dracula->GetHead());
						list_object->push_back(e);
					}
					else if (dynamic_cast<CBat *> (e))
					{
						list_object->push_back(e);
						CBat *bat = dynamic_cast<CBat *>(e);
						if (bat->GetSize() == BAT_SIZE_BIG)
						{
							if (bat->state == BAT_STATE_FIRE)
								list_object->push_back(bat->GetBullet());
						}
					}
					else if (dynamic_cast<CDracula *> (e))
					{
						CSimon* simon = CSimon::GetInstance();
						if (simon->MeetBoss)
						{
							CHidenObject *hidenobject;
							hidenobject = new CHidenObject();
							hidenobject->SetState(HIDENOBJECT_STATE_NORMAL);
							hidenobject->SetPosition(240, 0);
							hidenobject->SetSize(6, 160);
							list_object->push_back(hidenobject);
							CDracula *dracula = dynamic_cast<CDracula *>(e);
							list_object->push_back(dracula->GetHead());
							/*if (dracula->GetSpiritDracula() != NULL)
								list_object->push_back(dracula->GetSpiritDracula());*/
							list_object->push_back(e);
						}
					}
					else
						list_object->push_back(e);
				}
		}

}

void CCells::Update(DWORD dt, float cam_x, float cam_y)
{
	int xs, ys;
	int xe, ye;
	int i, j;

	xs = (int)cam_x / CELL_WIDTH;
	ys = (int)cam_y / CELL_HEIGHT;

	xe = (int)(cam_x + 256.0f) / CELL_WIDTH;
	ye = (int)(cam_y + 160.0f) / CELL_HEIGHT;

	for (i = xs; i < xe; i++)
		for (j = ys; j < ye; j++)
			cells[i][j].Update(dt);

}

void CCells::Render(float cam_x, float cam_y)
{
	int xs, ys;
	int xe, ye;
	int i, j;

	xs = (int)cam_x / CELL_WIDTH;
	ys = (int)cam_y / CELL_HEIGHT;

	xe = (int)(cam_x + 256.0f) / CELL_WIDTH;
	ye = (int)(cam_y + 160.0f) / CELL_HEIGHT;

	for (i = xs; i < xe; i++)
		for (j = ys; j < ye; j++)
			cells[i][j].Render();
}

CCell CCells::GetCell(int x, int y)
{
	return cells[x][y];
}