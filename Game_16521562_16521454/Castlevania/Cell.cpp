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
					list_object->push_back(e);
				}
		}
}

void CCells::ChangeCellOfObject(float cam_x, float cam_y)
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
					if (dynamic_cast <CCandle *> (e))
					{
						if (e->state == CANDLE_STATE_DELETE)
							cells[i][j].XoaObject(k);
					}					
					if (dynamic_cast <CItems *> (e))
					{
						if (e->state == ITEM_STATE_DELETE)
							cells[i][j].XoaObject(k);
					}
					else if (dynamic_cast <CDracula *> (e))
					{
						CDracula *dracula = dynamic_cast<CDracula *>(e);
						if (dracula->state == DRACULA_STATE_DIE && dracula->GetIsSpirit() == false)
						{
							cells[i][j].XoaObject(k);
						}
					}
					else if (dynamic_cast <CBossBat *> (e))
					{
						CBossBat *bossbat = dynamic_cast<CBossBat *>(e);
						if (bossbat->state == MONSTER_STATE_DELETE )
						{
							cells[i][j].XoaObject(k);
						}
					}
					else if (dynamic_cast<CMonster *> (e))
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
					else if (dynamic_cast<CBullet *> (e))
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
					else if (dynamic_cast<CBrick *>(e))
					{
						CBrick *brick = dynamic_cast<CBrick *>(e);
						if (brick->state == BRICK_STATE_DELETE)
							cells[i][j].XoaObject(k);
					}
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

