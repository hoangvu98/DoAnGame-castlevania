#include "ClockTowerLevel.h"
#include <fstream>
#include "Resource.h"
#include "Candle.h"
#include "HidenObject.h"
#include "Simon.h"

CClockTowerLevel *CClockTowerLevel::__instance = NULL;

CClockTowerLevel::CClockTowerLevel()
{
}

void CClockTowerLevel::LoadMap()
{
	ifstream in;
	textures->Add(ID_CANDLE, CANDLE_TEXTURE_PATH, D3DCOLOR_XRGB(34, 177, 76));
	LPDIRECT3DTEXTURE9 texture_map;
	LPANIMATION ani = new CAnimation(100);
	LPDIRECT3DTEXTURE9 texture_candle = textures->Get(ID_CANDLE);
	CCandle *candle;
	CSimon *simon = CSimon::GetInstance();
	CHidenObject *hobj;
	switch (scene)
	{
	case SCENE_1:
		textures->Add(ID_MAP_LEVEL_6, LEVEL6_STAGE16_PATH, D3DCOLOR_XRGB(255, 255, 255));
		texture_map = textures->Get(ID_MAP_LEVEL_6);
		tilemap->LoadTileMap(STAGE_16_MAP_DATA, texture_map);

		int column, row;

		float width, height;
		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cells = new CCells(column, row);

		hobj = new CHidenObject();
		hobj->SetPosition(1345.0f, 143.0f);
		hobj->SetSize(192.0f, 15.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(1217.0f, 80.0f);
		hobj->SetSize(161.0f, 15.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(1153.0f, 80.0f);
		hobj->SetSize(33.0f, 15.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(1089.0f, 80.0f);
		hobj->SetSize(33.0f, 15.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(992.0f, 80.0f);
		hobj->SetSize(66.0f, 15.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(895.0f, 80.0f);
		hobj->SetSize(66.0f, 15.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(673.0f, 80.0f);
		hobj->SetSize(192.0f, 15.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(607.0f, 80.0f);
		hobj->SetSize(33.0f, 15.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(480.0f, 80.0f);
		hobj->SetSize(98.0f, 15.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(352.0f, 80.0f);
		hobj->SetSize(33.0f, 15.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(417.0f, 80.0f);
		hobj->SetSize(33.0f, 15.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(33.0f, 77.0f);
		hobj->SetSize(288.0f, 15.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(0.0f, 0.0f);
		hobj->SetSize(33.0f, 182.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		break;
	case SCENE_2:
		textures->Add(ID_MAP_LEVEL_6, LEVEL6_STAGE17A_PATH, D3DCOLOR_XRGB(255, 255, 255));
		texture_map = textures->Get(ID_MAP_LEVEL_6);
		tilemap->LoadTileMap(STAGE_17A_MAP_DATA, texture_map);

		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cells = new CCells(column, row);

		hobj = new CHidenObject();
		hobj->SetPosition(738.0f, 80.0f);
		hobj->SetSize(30.0f, 98.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(706.0f, 80.0f);
		hobj->SetSize(30.0f, 15.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(610.0f, 48.0f);
		hobj->SetSize(30.0f, 15.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(642.0f, 113.0f);
		hobj->SetSize(30.0f, 15.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(512.0f, 113.0f);
		hobj->SetSize(130.0f, 62.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(482.0f, 0.0f);
		hobj->SetSize(30.0f, 174.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(418.0f, 113.0f);
		hobj->SetSize(62.0f, 29.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(366.0f, 18.0f);
		hobj->SetSize(80.0f, 18.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(305.0f, 80.0f);
		hobj->SetSize(80.0f, 18.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(224.0f, 143.0f);
		hobj->SetSize(64.0f, 32.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(161.0f, 143.0f);
		hobj->SetSize(30.0f, 15.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(162.0f, 0.0f);
		hobj->SetSize(30.0f, 46.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(258.0f, 49.0f);
		hobj->SetSize(30.0f, 15.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(33.0f, 48.0f);
		hobj->SetSize(95.0f, 15.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(0.0f, 0.0f);
		hobj->SetSize(32.0f, 175.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		break;
	case SCENE_3:
		textures->Add(ID_MAP_LEVEL_6, LEVEL6_STAGE17B_PATH, D3DCOLOR_XRGB(255, 255, 255));
		texture_map = textures->Get(ID_MAP_LEVEL_6);
		tilemap->LoadTileMap(STAGE_17B_MAP_DATA, texture_map);

		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cells = new CCells(column, row);
		break;
	case SCENE_4:
		textures->Add(ID_MAP_LEVEL_6, LEVEL6_STAGE18A_PATH, D3DCOLOR_XRGB(255, 255, 255));
		texture_map = textures->Get(ID_MAP_LEVEL_6);
		tilemap->LoadTileMap(STAGE_18A_MAP_DATA, texture_map);

		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cells = new CCells(column, row);
		break;
	case SCENE_5:
		textures->Add(ID_MAP_LEVEL_6, LEVEL6_STAGE18B_PATH, D3DCOLOR_XRGB(255, 255, 255));
		texture_map = textures->Get(ID_MAP_LEVEL_6);
		tilemap->LoadTileMap(STAGE_18B_MAP_DATA, texture_map);

		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cells = new CCells(column, row);
		break;
	}
}


void CClockTowerLevel::Update()
{
	if (prev_scene != scene)
	{
		LoadMap();
		prev_scene = scene;
	}
}

void CClockTowerLevel::Render()
{
	tilemap->Render(0.0f, 0.0f);
}

CClockTowerLevel::~CClockTowerLevel()
{
}

CClockTowerLevel * CClockTowerLevel::GetInstance()
{
	if (__instance == NULL) __instance = new CClockTowerLevel();
	return __instance;
}
