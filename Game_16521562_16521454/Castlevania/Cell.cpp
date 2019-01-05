#include "Cell.h"
#include "debug.h"
#include "HidenObject.h"

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
				for (k = 0; k < (int)cells[i][j].GetObjects().size(); k++)
				{
					LPGAMEOBJECT e = cells[i][j].GetObjects()[k];				
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
			int x1 = (int)x / CELL_WIDTH;
			int x2 = (int)(x + width) / CELL_WIDTH;
			int j = (int)y / CELL_HEIGHT;
			for (int i = x1; i <= x2; i++)
			{
				hidenobject = new CHidenObject();
				hidenobject->SetState(HIDENOBJECT_STATE_NORMAL);
				hidenobject->SetPosition((float)i*CELL_WIDTH, y);
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
			int x = (int)object->x / CELL_WIDTH;
			int y = (int)object->y / CELL_HEIGHT;
			cells[x][y].SetObjects(object);
		}
	}
	else
	{
		int x = (int)object->x / CELL_WIDTH;
		int y = (int)object->y / CELL_HEIGHT;
		cells[x][y].SetObjects(object);
	}
}