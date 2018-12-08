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

		//nen
		candle = new CCandle(SMALL_CANDLE, AXE);
		candle->SetPosition(1501.0f, 84.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		for (int i = 0; i < 2; i++)
		{
			candle = new CCandle(SMALL_CANDLE);
			candle->SetPosition(i * 68.0f + 1371.0f, 112.0f);
			candle->SetState(CANDLE_STATE_NORMAL);
			cells->InitCells(candle);
		}

		for (int i = 0; i < 3; i++)
		{
			candle = new CCandle(SMALL_CANDLE);
			candle->SetPosition(i * 69.0f + 670.0f, 47.0f);
			candle->SetState(CANDLE_STATE_NORMAL);
			cells->InitCells(candle);
		}

		candle = new CCandle(SMALL_CANDLE);
		candle->SetPosition(92.0f, 14.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

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

		candle = new CCandle(SMALL_CANDLE);
		candle->SetPosition(734.0f, 17.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		for (int i = 0; i < 3; i++)
		{
			candle = new CCandle(SMALL_CANDLE);
			candle->SetPosition(i * 58.0f + 539.0f, 82.0f);
			candle->SetState(CANDLE_STATE_NORMAL);
			cells->InitCells(candle);
		}

		for (int i = 0; i < 3; i++)
		{
			candle = new CCandle(SMALL_CANDLE);
			candle->SetPosition(i * 65.0f + 92.0f, 114.0f);
			candle->SetState(CANDLE_STATE_NORMAL);
			cells->InitCells(candle);
		}

		candle = new CCandle(SMALL_CANDLE);
		candle->SetPosition(283.0f, 18.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);
		break;
	case SCENE_3:
		textures->Add(ID_MAP_LEVEL_6, LEVEL6_STAGE17B_PATH, D3DCOLOR_XRGB(255, 255, 255));
		texture_map = textures->Get(ID_MAP_LEVEL_6);
		tilemap->LoadTileMap(STAGE_17B_MAP_DATA, texture_map);

		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cells = new CCells(column, row);

		hobj = new CHidenObject();
		hobj->SetPosition(1.0f, 81.0f);
		hobj->SetSize(32.0f, 94.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(128.0f, 146.0f);
		hobj->SetSize(30.0f, 29.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(160.0f, 16.0f);
		hobj->SetSize(32.0f, 159.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(257.0f, 113.0f);
		hobj->SetSize(62.0f, 30.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(352.0f, 143.0f);
		hobj->SetSize(32.0f, 16.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(434.0f, 144.0f);
		hobj->SetSize(47.0f, 18.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(368.0f, 113.0f);
		hobj->SetSize(79.0f, 16.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(336.0f, 47.0f);
		hobj->SetSize(79.0f, 16.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(449.0f, 47.0f);
		hobj->SetSize(32.0f, 31.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(481.0f, 47.0f);
		hobj->SetSize(190.0f, 14.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(481.0f, 63.0f);
		hobj->SetSize(33.0f, 112.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(514.0f, 145.0f);
		hobj->SetSize(126.0f, 30.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(705.0f, 81.0f);
		hobj->SetSize(30.0f, 15.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(705.0f, 145.0f);
		hobj->SetSize(30.f, 15.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(737.0f, 1.0f);
		hobj->SetSize(31.0f, 175.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(33.0f, 81.0f);
		hobj->SetSize(32.0f, 16.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(1.0f, 1.0f);
		hobj->SetSize(32.0f, 16.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		candle = new CCandle(SMALL_CANDLE);
		candle->SetPosition(605.0f, 81.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		candle = new CCandle(SMALL_CANDLE);
		candle->SetPosition(667.0f, 17.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		for (int i = 0; i < 2; i++)
		{
			candle = new CCandle(SMALL_CANDLE);
			candle->SetPosition(i * 64.0f + 477.0f, 17.0f);
			candle->SetState(CANDLE_STATE_NORMAL);
			cells->InitCells(candle);
		}

		candle = new CCandle(SMALL_CANDLE);
		candle->SetPosition(284.0f, 82.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		for (int i = 0; i < 2; i++)
		{
			candle = new CCandle(SMALL_CANDLE);
			candle->SetPosition(i * 63.0f + 94.0f, 82.0f);
			candle->SetState(CANDLE_STATE_NORMAL);
			cells->InitCells(candle);
		}

		candle = new CCandle(SMALL_CANDLE);
		candle->SetPosition(28.0f, 16.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);
		break;
	case SCENE_4:
		textures->Add(ID_MAP_LEVEL_6, LEVEL6_STAGE18A_PATH, D3DCOLOR_XRGB(255, 255, 255));
		texture_map = textures->Get(ID_MAP_LEVEL_6);
		tilemap->LoadTileMap(STAGE_18A_MAP_DATA, texture_map);

		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cells = new CCells(column, row);

		hobj = new CHidenObject();
		hobj->SetPosition(249.0f, 0.0f);
		hobj->SetSize(36.0f, 93.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(184.0f, 81.0f);
		hobj->SetSize(65.0f, 15.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);
		break;
	case SCENE_5:
		textures->Add(ID_MAP_LEVEL_6, LEVEL6_STAGE18B_PATH, D3DCOLOR_XRGB(255, 255, 255));
		texture_map = textures->Get(ID_MAP_LEVEL_6);
		tilemap->LoadTileMap(STAGE_18B_MAP_DATA, texture_map);

		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cells = new CCells(column, row);

		hobj = new CHidenObject();
		hobj->SetPosition(0.0f, 0.0f);
		hobj->SetSize(2.0f, 146.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(2.0f, 146.0f);
		hobj->SetSize(478.0f, 30.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(450.0f, 114.0f);
		hobj->SetSize(95.0f, 30.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(257.0f, 0.0f);
		hobj->SetSize(15.0f, 79.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(514.0f, 0.0f);
		hobj->SetSize(30.0f, 47.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

		candle = new CCandle(SMALL_CANDLE);
		candle->SetPosition(477.0f, 50.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		for (int i = 0; i < 7; i++)
		{
			candle = new CCandle(SMALL_CANDLE);
			candle->SetPosition(i * 64.0f + 30.0f, 83.0f);
			candle->SetState(CANDLE_STATE_NORMAL);
			cells->InitCells(candle);
		}
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
