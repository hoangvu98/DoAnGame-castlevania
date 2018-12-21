#pragma once
#include <vector>
#include "Game.h"
#include "GameObject.h"
using namespace std;

#define CELL_WIDTH	64
#define CELL_HEIGHT	56
class CCell
{
	vector<LPGAMEOBJECT> objects;
	float width;
	float height;
public:
	void GetSize(float width, float height) { width = this->width; height = this->height; }
	void SetObjects(LPGAMEOBJECT object);
	vector<LPGAMEOBJECT> GetObjects() { return objects; }
	void XoaObject(int k);
	void Update(DWORD dt);
	void Render();
	CCell();
	~CCell();
};
typedef CCell *LPCELL;

class CCells
{
	int row;
	int column;

	LPCELL *cells;
public:
	CCells();
	CCells(int row, int column);
	~CCells();

	void InitCells(LPGAMEOBJECT object);
	void GetListOfObjects(vector<LPGAMEOBJECT> *list_object, float cam_x, float cam_y);
	void GetListOfObjectsnotchange(vector<LPGAMEOBJECT> *list_object, float cam_x, float cam_y);
	void Update(DWORD dt, float cam_x, float cam_y);
	void Render(float cam_x, float cam_y);
	CCell GetCell(int x, int y);
};