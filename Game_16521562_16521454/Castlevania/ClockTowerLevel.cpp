#include "ClockTowerLevel.h"
#include <fstream>
#include "Resource.h"
#include "Candle.h"
#include "HidenObject.h"
#include "Simon.h"
#include "Door.h"
#include "Eagle.h"
#include "Hunchback.h"
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
	CSkeleton *skeleton;
	CSimon *simon = CSimon::GetInstance();
	CHidenObject *hobj;
	CDoor * door;
	CEagle *eagle;
	CHunchback* hunchback;
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


		hobj = new CHidenObject();
		hobj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		hobj->SetSize(24.0f, 13.0f);
		hobj->SetPosition(1360.0f, 68.0f);
		hobj->SetStair_X(1369.0f);
		hobj->nx = 1;
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		hobj->SetSize(28.0f, 9.0f);
		hobj->SetPosition(1420.0f, 135.0f);
		hobj->SetStair_X(1434.0f);
		hobj->nx = -1;
		cells->InitCells(hobj);

		/*door = new CDoor();
		door->SetPosition(90.0f, 50.0f);
		door->size = 30;
		door->SetIsHiDen(true);
		door->SetScene(2);
		cells->InitCells(door);*/

		break;
	case SCENE_2:
		textures->Add(ID_MAP_LEVEL_6, LEVEL6_STAGE17A_PATH, D3DCOLOR_XRGB(255, 255, 255));
		texture_map = textures->Get(ID_MAP_LEVEL_6);
		tilemap->LoadTileMap(STAGE_17A_MAP_DATA, texture_map);

		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cells = new CCells(column, row);

	/*	eagle = new CEagle();
		eagle->SetPosition(515.0f, 34.0f);
		eagle->SetState(EAGLE_STATE_FLY_RIGHT);
		cells->InitCells(eagle);

		hunchback = new CHunchback();
		hunchback->SetPosition(525.0f, 55.0f);
		hunchback->SetState(HUNCHBACK_STATE_FLY_RIGHT);
		cells->InitCells(hunchback);*/

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

		hobj = new CHidenObject();
		hobj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		hobj->SetSize(25.0f, 10.0f);
		hobj->SetPosition(538.0f, 104.0f);
		hobj->SetStair_X(539.0f);
		hobj->nx = 1;
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		hobj->SetSize(19.0f, 8.0f);
		hobj->SetPosition(606.0f, 42.0f);
		hobj->SetStair_X(603.4f);
		hobj->nx = -1;
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		hobj->SetSize(26.0f, 10.0f);
		hobj->SetPosition(215.0f, 136.0f);
		hobj->SetStair_X(216.0f);
		hobj->nx = -1;
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		hobj->SetSize(23.0f, 9.0f);
		hobj->SetPosition(111.0f, 41.0f);
		hobj->SetStair_X(120.0f);
		hobj->nx = 1;
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		hobj->SetSize(26.0f, 11.0f);
		hobj->SetPosition(54.0f, 39.0f);
		hobj->SetStair_X(60.0f);
		hobj->nx = 1;
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		hobj->SetSize(30.0f, 11.0f);
		hobj->SetPosition(626.0f, 39.0f);
		hobj->SetStair_X(634.0f);
		hobj->nx = 1;
		cells->InitCells(hobj);


		hobj = new CHidenObject();
		hobj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		hobj->SetSize(19.0f, 10.0f);
		hobj->SetPosition(279.0f, 40.0f);
		hobj->SetStair_X(283.0f);
		hobj->nx = 1;
		cells->InitCells(hobj);

		door = new CDoor();
		door->SetState(DOOR_STATE_CLOSE);
		door->SetPosition(680.0f, 0.0f);
		door->cx = 669.84f;
		door->cy = 142.76f;
		door->SetIsHiDen(true);
		door->IsGo = true;
		door->SetIsStair(true);
		door->SetScene(3);
		cells->InitCells(door);

	/*	skeleton = new CSkeleton(612.0f, 79.0f);
		skeleton->SetMinMax();
		skeleton->SetState(SKELETON_STATE_WALKING_RIGHT);
		cells->InitCells(skeleton);*/

		break;
	case SCENE_3:
		textures->Add(ID_MAP_LEVEL_6, LEVEL6_STAGE17B_PATH, D3DCOLOR_XRGB(255, 255, 255));
		texture_map = textures->Get(ID_MAP_LEVEL_6);
		tilemap->LoadTileMap(STAGE_17B_MAP_DATA, texture_map);

		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cells = new CCells(column, row);


		hunchback = new CHunchback();
		hunchback->SetPosition(521.0f, 71.0f);
		hunchback->SetState(HUNCHBACK_STATE_FLY_RIGHT);
		cells->InitCells(hunchback);


		door = new CDoor();
		door->SetState(DOOR_STATE_CLOSE);
		door->SetPosition(671.0f, 172.0f);
		door->cx = 662.76f;
		door->cy = -11.16f;
		door->SetIsHiDen(true);
		door->IsGo = true;
		door->SetIsStair(true);
		door->SetScene(2);
		cells->InitCells(door);

		hobj = new CHidenObject();
		hobj->SetPosition(639.0f, 145.0f);
		hobj->SetSize(32.0f, 12.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cells->InitCells(hobj);

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

		hobj = new CHidenObject();
		hobj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		hobj->SetSize(17.0f, 7.0f);
		hobj->SetPosition(701.0f, 137.0f);
		hobj->SetStair_X(698.0f);
		hobj->nx = -1;
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		hobj->SetSize(26.0f, 10.0f);
		hobj->SetPosition(629.0f, 135.0f);
		hobj->SetStair_X(635.0f);
		hobj->nx = 1;
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		hobj->SetSize(23.0f, 7.0f);
		hobj->SetPosition(656.0f, 42.0f);
		hobj->SetStair_X(665.0f);
		hobj->nx = 1;
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		hobj->SetSize(23.0f, 8.0f);
		hobj->SetPosition(303.0f, 105.0f);
		hobj->SetStair_X(312.0f);
		hobj->nx = 1;
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		hobj->SetSize(22.0f, 8.0f);
		hobj->SetPosition(42.0f, 72.0f);
		hobj->SetStair_X(57.0f);
		hobj->nx = 1;
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetState(HIDENOBJECT_STATE_STAIR_UP_DOWN);
		hobj->SetSize(22.0f, 11.0f);
		hobj->SetPosition(702.0f, 69.0f);
		hobj->SetStair_X(699.4f);
		hobj->nx = -1;
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetState(HIDENOBJECT_STATE_STAIR_UP_DOWN);
		hobj->SetSize(24.0f, 11.0f);
		hobj->SetPosition(349.0f, 133.0f);
		hobj->SetStair_X(346.0f);
		hobj->nx = -1;
		cells->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetState(HIDENOBJECT_STATE_STAIR_UP_DOWN);
		hobj->SetSize(27.0f, 15.0f);
		hobj->SetPosition(127.0f, 129.0f);
		hobj->SetStair_X(122.0f);
		hobj->nx = -1;
		cells->InitCells(hobj);

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

		hobj = new CHidenObject();
		hobj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		hobj->SetSize(24.0f, 10.0f);
		hobj->SetPosition(175.0f, 71.0f);
		hobj->SetStair_X(177.0f);
		hobj->nx = -1;
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

		hobj = new CHidenObject();
		hobj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		hobj->SetSize(21.0f, 10.0f);
		hobj->SetPosition(527.0f, 103.0f);
		hobj->SetStair_X(535.0f);
		hobj->nx = 1;
		cells->InitCells(hobj);

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

void CClockTowerLevel::GetSizeMap(float & min, float & max)
{
	if (scene == SCENE_1)
	{
		min = MIN_MAP_1;
		max = MAX_MAP_1;
	}
	else if (scene == SCENE_2)
	{
		min = MIN_MAP_2;
		max = MAX_MAP_2;
	}
	else if (scene == SCENE_3)
	{
		min = MIN_MAP_3;
		max = MAX_MAP_3;
	}
	else if (scene == SCENE_4)
	{
		min = MIN_MAP_4;
		max = MAX_MAP_4;
	}
	else if (scene == SCENE_5)
	{
		min = MIN_MAP_5;
		max = MAX_MAP_5;
	}
}
