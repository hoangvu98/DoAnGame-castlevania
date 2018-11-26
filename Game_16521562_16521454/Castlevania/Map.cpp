#include "Map.h"

CMap::CMap()
{

	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();
	animations = CAnimations::GetInstance();
	tilemap = new CTileMap();
	prev_scene = 0;
	scene = 0;
}

CMap::~CMap()
{
}


void CMap::NextScece(float &x, float &y)
{
	scene++;
	if (scene == 2)
	{
		x = 10.0f;
		y = 127.0f;
	}
	else if (scene == 4)
	{
		x = 20.0f;
		y = 28.0f;
	}
	else
	{
		x = 0;
		y = 0;
	}
}

vector<LPGAMEOBJECT> CMap::GetUpdateObjects()
{
	float cam_x, cam_y;
	CGame *game = CGame::GetInstance();
	game->GetCamera(cam_x, cam_y);
	vector<LPGAMEOBJECT> UpdateObjects;

	cells->GetListOfObjects(&UpdateObjects, cam_x, cam_y);
	return UpdateObjects;
}

void CMap::GetSizeOfMap(float &width, float &height)
{
	tilemap->GetSize(width, height);
}

void CMap::LoadMap()
{
	/*int column, row;

	float width, height;
	tilemap->GetSize(width, height);

	column = (int)width / CELL_WIDTH + 1;
	row = (int)height / CELL_HEIGHT + 1;

	cells = new CCells(row, column);*/

}

void CMap::Render()
{
}

