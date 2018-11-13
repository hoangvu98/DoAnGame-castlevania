#include "TileMap.h"
#include "Game.h"
#include "debug.h"
#include <fstream>
using namespace std;

void CTileMap::LoadTileMap(string fileName, LPDIRECT3DTEXTURE9 tex)
{
	ifstream in(fileName);
	if (!in)
	{
		DebugOut(L"Can't not open file: %s\n", fileName);
		return;
	}
	else DebugOut(L"Open file %s sucessful!", fileName);
	sprites = CSprites::GetInstance();

	in >> column;
	in >> row;

	width = TILE_WIDTH * column;
	height = TILE_HEIGHT * row;

	//khoi tao ma tran map
	int i = 0;
	int j = 0;

	map = new int *[row];
	for (i = 0; i < row; i++)
		map[i] = new int[column];
	i = 0;
	//doc ma tran tu file
	for (map[i][j]; in >> map[i][j];)
	{
		if (j < column - 1)
			j++;
		else
		{
			j = 0;
			if (i < row - 1) i++;
			else break;
		}
	}

	int id = 1;
	int tileset_width;
	int tileset_height;

	in >> tileset_width;
	in >> tileset_height;
	in.close();

	int left, top;

	for (top = 0; top < tileset_height; top += TILE_HEIGHT)
		for (left = 0; left < tileset_width; left += TILE_WIDTH)
		{
			sprites->Add(id, left, top, left + TILE_WIDTH, top + TILE_HEIGHT, tex);
			id++;
		}
	//id = 1;
}

void CTileMap::Render(float x, float y)
{
	int i, j;
	float x0, y0;
	x0 = x;
	y0 = y;

	/*float offset_x, offset_y;
	float cam_x, cam_y;
	CGame *game = CGame::GetInstance();
	game->GetCamera(cam_x, cam_y);

	offset_x = -cam_x + 0.0f * width;
	offset_y = -cam_y + 0.0f * height;*/
	float cam_x, cam_y;
	CGame *game = CGame::GetInstance();
	game->GetCamera(cam_x, cam_y);
	//DebugOut(L"cam_x = %f, cam_y = %f\n", cam_x, cam_y);
	for (i = 0; i < row; i++)
		for (j = 0; j < column; j++)
		{
			//DebugOut(L"x = %f, y = %f\n", x, y);
			sprites->Get(map[i][j])->Draw(x, y);
			if (j < column - 1) x += TILE_WIDTH/*+ offset_x*/;
			else
			{
				x = x0;
				if (i < row) y += TILE_HEIGHT/*+ offset_y*/;
			}
		}
	
}
