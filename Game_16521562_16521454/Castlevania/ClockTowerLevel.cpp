#include "ClockTowerLevel.h"
#include <fstream>
#include "Resource.h"
#include "Candle.h"
#include "HidenObject.h"
#include "Simon.h"
#include "Door.h"
#include "Eagle.h"
#include "Bat.h"
#include "Dracula.h"
#include "SpiritDracula.h"
CClockTowerLevel *CClockTowerLevel::__instance = NULL;

CClockTowerLevel::CClockTowerLevel()
{
}

void CClockTowerLevel::LoadMap()
{
	CCandle *candle;
	CSkeleton *skeleton;
	CSimon *simon = CSimon::GetInstance();
	CEagle *eagle;
	CBat* bat;
	CDracula *dracula;
	ifstream in;
	LPGAMEOBJECT object;
	int i;

	switch (scene)
	{
	case SCENE_6_1:
		simon->SetStage(16);
		int column, row;

		float width, height;
		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cells = new CCells(column, row);

		in.open("Data\\ClockTowerLevel_Scene1.txt");
		for (i = 0; i < 10; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cells->InitCells(object);
		}
		in.close();

		/*bat = new CBat(BAT_SIZE_BIG);
		bat->SetPosition(1343.0f, 0.0f);
		bat->SetPosstionAppear(1220.0f, 0.0f);
		bat->SetSize(10, 70);
		cells->InitCells(bat);

		bat = new CBat(BAT_SIZE_BIG);
		bat->SetPosition(793.0f, 0.0f);
		bat->SetPosstionAppear(673.0f, 0.0f);
		bat->SetSize(10, 70);
		cells->InitCells(bat);
*/
/*bat = new CBat(BAT_SIZE_BIG);
bat->SetPosition(580.0f, 0.0f);
bat->SetPosstionAppear(460.0f, 0.0f);
bat->SetSize(10, 70);
cells->InitCells(bat);

candle = new CCandle(SMALL_CANDLE, AXE);
candle->SetPosition(1501.0f, 84.0f);
candle->SetState(CANDLE_STATE_NORMAL);
cells->InitCells(candle);*/

/*for (int i = 0; i < 2; i++)
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
cells->InitCells(candle);*/
		break;
	case SCENE_6_2:
		simon->SetStage(17);
		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cells = new CCells(column, row);

		in.open("Data\\ClockTowerLevel_Scene2.txt");
		for (i = 0; i < 11; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cells->InitCells(object);
		}
		in.close();

		/*candle = new CCandle(SMALL_CANDLE);
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

		eagle = new CEagle();
		eagle->SetPosstionAppear(220.0f, 68.0f);
		eagle->SetPosition(257, 33);
		eagle->SetSize(30, 16);
		eagle->SetState(EAGLE_STATE_SLEEPING);
		eagle->SetStateAppear(EAGLE_STATE_FLY_RIGHT);
		cells->InitCells(eagle);

		eagle = new CEagle();
		eagle->SetPosstionAppear(200.0f, 68.0f);
		eagle->SetPosition(224, 125);
		eagle->SetSize(63, 21);
		eagle->SetState(EAGLE_STATE_SLEEPING);
		eagle->SetStateAppear(EAGLE_STATE_FLY_RIGHT);
		cells->InitCells(eagle);

		skeleton = new CSkeleton(612.0f, 79.0f);
		skeleton->SetState(SKELETON_STATE_WALKING_RIGHT);
		cells->InitCells(skeleton);*/
		break;
	case SCENE_6_3:
		simon->SetStage(17);
		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cells = new CCells(column, row);

		in.open("Data\\ClockTowerLevel_Scene3.txt");
		for (i = 0; i < 12; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cells->InitCells(object);
		}
		in.close();

		/*skeleton = new CSkeleton(592.0f, 113.0f);
		skeleton->SetState(SKELETON_STATE_WALKING_RIGHT);
		cells->InitCells(skeleton);

		skeleton = new CSkeleton(613.0f, 15.0f);
		skeleton->SetState(SKELETON_STATE_WALKING_RIGHT);
		cells->InitCells(skeleton);

		eagle = new CEagle();
		eagle->SetPosstionAppear(515.0f, 50.0f);
		eagle->SetPosition(542, 32);
		eagle->SetSize(16, 16);
		eagle->SetState(EAGLE_STATE_SLEEPING);
		eagle->SetStateAppear(EAGLE_STATE_FLY_RIGHT);
		cells->InitCells(eagle);

		eagle = new CEagle();
		eagle->SetPosstionAppear(277.0f, 69.0f);
		eagle->SetPosition(335, 35);
		eagle->SetSize(80, 13);
		eagle->SetState(EAGLE_STATE_SLEEPING);
		eagle->SetStateAppear(EAGLE_STATE_FLY_RIGHT);
		cells->InitCells(eagle);

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
		cells->InitCells(candle);*/

		break;
	case SCENE_6_4:
		simon->SetStage(18);
		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cells = new CCells(column, row);

		dracula = CDracula::GetInstance();
		dracula->SetHealth(1);
		break;
	case SCENE_6_5:
		simon->SetStage(18);
		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cells = new CCells(column, row);

		in.open("Data\\ClockTowerLevel_Scene5.txt");
		for (i = 0; i < 9; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cells->InitCells(object);
		}

		in.close();

		candle = new CCandle(SMALL_CANDLE, HOLLYWATER);
		candle->SetPosition(477.0f, 50.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		/*candle = new CCandle(SMALL_CANDLE, HOLLYWATER);
		candle->SetPosition(0 * 64.0f + 30.0f, 83.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		candle = new CCandle(SMALL_CANDLE, BOOMERANG);
		candle->SetPosition(3 * 64.0f + 30.0f, 83.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);
		for (int i = 0; i < 3; i++)
		{
			candle = new CCandle(SMALL_CANDLE);
			candle->SetPosition(i * 64.0f + 30.0f, 83.0f);
			candle->SetState(CANDLE_STATE_NORMAL);
			cells->InitCells(candle);
		}
		for (int i = 4; i < 7; i++)
		{
			candle = new CCandle(SMALL_CANDLE);
			candle->SetPosition(i * 64.0f + 30.0f, 83.0f);
			candle->SetState(CANDLE_STATE_NORMAL);
			cells->InitCells(candle);
		}


		dracula = CDracula::GetInstance();
		dracula->Setnx(-1);
		dracula->SetState(DRACULA_STATE_SLEEPING);
		cells->InitCells(dracula);*/
		break;
	}
}

void CClockTowerLevel::LoadObject()
{
	LPDIRECT3DTEXTURE9 texture_map;
	CHidenObject *hobj;
	CDoor* door;
	ifstream in;
	LPGAMEOBJECT object;
	int i;

	switch (scene)
	{
	case SCENE_6_1:
		textures->Add(ID_MAP_LEVEL_6, LEVEL6_STAGE16_PATH, D3DCOLOR_XRGB(255, 255, 255));
		texture_map = textures->Get(ID_MAP_LEVEL_6);
		tilemap->LoadTileMap(STAGE_16_MAP_DATA, texture_map);

		int column, row;

		float width, height;
		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cellsobject = new CCells(column, row);

		in.open("Data\\hobj_CT_Scene1.txt");
		for (i = 0; i < 16; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cellsobject->InitCells(object);
		}
		in.close();

		in.open("Data\\door_scene1_CLockTower.txt");
		CInputImage::LoadDoorFromFile(in, door);
		cellsobject->InitCells(door);
		in.close();

		//hobj = new CHidenObject();
		//hobj->SetPosition(1345.0f, /*143.0f*/145.0f);
		//hobj->SetSize(192.0f, 15.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		/*hobj = new CHidenObject();
		hobj->SetPosition(1217.0f, 81.0f);
		hobj->SetSize(161.0f, 15.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cellsobject->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(1153.0f, 81.0f);
		hobj->SetSize(33.0f, 15.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cellsobject->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(1089.0f, 81.0f);
		hobj->SetSize(33.0f, 15.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cellsobject->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(992.0f, 81.0f);
		hobj->SetSize(66.0f, 15.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cellsobject->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(895.0f, 81.0f);
		hobj->SetSize(66.0f, 15.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cellsobject->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(673.0f, 81.0f);
		hobj->SetSize(192.0f, 15.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cellsobject->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(607.0f, 81.0f);
		hobj->SetSize(33.0f, 15.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cellsobject->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(480.0f, 81.0f);
		hobj->SetSize(98.0f, 15.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cellsobject->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(352.0f, 81.0f);
		hobj->SetSize(33.0f, 15.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cellsobject->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetPosition(417.0f, 81.0f);
		hobj->SetSize(33.0f, 15.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cellsobject->InitCells(hobj);*/

		//hobj = new CHidenObject();
		//hobj->SetPosition(33.0f, /*77.0f*/ 81.0f);
		//hobj->SetSize(288.0f, 15.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		/*hobj = new CHidenObject();
		hobj->SetPosition(0.0f, 0.0f);
		hobj->SetSize(33.0f, 182.0f);
		hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		cellsobject->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		hobj->SetSize(24.0f, 13.0f);
		hobj->SetPosition(1360.0f, 68.0f);
		hobj->SetStair_XY(1370.0f, 50);
		hobj->nx = 1;
		cellsobject->InitCells(hobj);

		hobj = new CHidenObject();
		hobj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		hobj->SetSize(28.0f, 14.0f);
		hobj->SetPosition(1420.0f, 130.0f);
		hobj->SetStair_XY(1434.0f, 113);
		hobj->nx = -1;
		cellsobject->InitCells(hobj);

		door = new CDoor();
		door->SetPosition(90.0f, 50.0f);
		door->size = 30;
		door->SetIsHiDen(true);
		door->SetScene(2);
		cellsobject->InitCells(door);*/
		break;
	case SCENE_6_2:
		textures->Add(ID_MAP_LEVEL_6, LEVEL6_STAGE17A_PATH, D3DCOLOR_XRGB(255, 255, 255));
		texture_map = textures->Get(ID_MAP_LEVEL_6);
		tilemap->LoadTileMap(STAGE_17A_MAP_DATA, texture_map);

		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cellsobject = new CCells(column, row);

		in.open("Data\\hobj_CT_Scene2.txt");
		for (i = 0; i < 25; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cellsobject->InitCells(object);
		}
		in.close();

		in.open("Data\\door_scene2_CLockTower.txt");
		for (i = 0; i < 3; i++)
		{
			CInputImage::LoadDoorFromFile(in, door);
			door->SetIsStair(true);
			cellsobject->InitCells(door);
		}
		in.close();

		//door = new CDoor();
		//door->SetState(DOOR_STATE_NORMAL);
		//door->SetPosition(100.0f, 0.0f);
		//door->cx = 92.0f;
		//door->cy = 144.0f;
		//door->SetIsHiDen(true);
		//door->SetIsStair(true);
		//door->SetScene(3);
		//cellsobject->InitCells(door);

		//door = new CDoor();
		//door->SetState(DOOR_STATE_NORMAL);
		//door->SetPosition(325.0f, 0.0f);
		//door->cx = 315.08f;
		//door->cy = 143.06f;
		//door->SetIsHiDen(true);
		//door->SetIsStair(true);
		//door->SetScene(3);
		//cellsobject->InitCells(door);

		//hobj = new CHidenObject();
		//hobj->SetPosition(738.0f, /*80.0f*/82.0f);
		//hobj->SetSize(30.0f, 98.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(706.0f, /*80.0f*/82.0f);
		//hobj->SetSize(30.0f, 15.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(610.0f, /*48.0f*/50.0f);
		//hobj->SetSize(30.0f, 15.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(642.0f, /*113.0f*/114.0f);
		//hobj->SetSize(30.0f, 15.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(512.0f, /*113.0f*/114.0f);
		//hobj->SetSize(130.0f, 62.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(482.0f, 0.0f);
		//hobj->SetSize(30.0f, 174.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(418.0f, /*113.0f*/114.0f);
		//hobj->SetSize(62.0f, 29.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(366.0f, /*18.0f*/19.0f);
		//hobj->SetSize(80.0f, 18.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(305.0f, /*80.0f*/81.0f);
		//hobj->SetSize(80.0f, 18.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(224.0f, /*143.0f*/146.0f);
		//hobj->SetSize(64.0f, 32.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(161.0f, /*143.0f*/146.0f);
		//hobj->SetSize(30.0f, 15.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(162.0f, 0.0f);
		//hobj->SetSize(30.0f, 46.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(258.0f, 49.0f);
		//hobj->SetSize(30.0f, 15.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(33.0f, /*48.0f*/50.0f);
		//hobj->SetSize(95.0f, 15.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(0.0f, 0.0f);
		//hobj->SetSize(32.0f, 175.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		//hobj->SetSize(25.0f, 10.0f);
		//hobj->SetPosition(538.0f, 104.0f);
		//hobj->SetStair_XY(538.0f, 83);
		//hobj->nx = 1;
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		//hobj->SetSize(19.0f, 8.0f);
		//hobj->SetPosition(606.0f, 42.0f);
		//hobj->SetStair_XY(600, 19);
		//hobj->nx = -1;
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		//hobj->SetSize(26.0f, 10.0f);
		//hobj->SetPosition(215.0f, 136.0f);
		//hobj->SetStair_XY(216.0f, 114);
		//hobj->nx = -1;
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		//hobj->SetSize(23.0f, 9.0f);
		//hobj->SetPosition(111.0f, 41.0f);
		//hobj->SetStair_XY(121.0f, 19);
		//hobj->nx = 1;
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		//hobj->SetSize(26.0f, 11.0f);
		//hobj->SetPosition(54.0f, 39.0f);
		//hobj->SetStair_XY(59.0f, 19);
		//hobj->nx = 1;
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		//hobj->SetSize(30.0f, 12.0f);
		//hobj->SetPosition(626.0f, 38.0f);
		//hobj->SetStair_XY(634.0f, 17);
		//hobj->nx = 1;
		//cellsobject->InitCells(hobj);


	/*	hobj = new CHidenObject();
		hobj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		hobj->SetSize(19.0f, 10.0f);
		hobj->SetPosition(279.0f, 38.0f);
		hobj->SetStair_XY(283.0f, 20);
		hobj->nx = 1;
		cellsobject->InitCells(hobj);*/

		//door = new CDoor();
		//door->SetState(DOOR_STATE_NORMAL);
		//door->SetPosition(680.0f, 0.0f);
		//door->cx = 672.02f;
		//door->cy = 139.38f;
		//door->SetIsHiDen(true);
		//door->SetIsStair(true);
		//door->SetScene(3);
		//cellsobject->InitCells(door);

		//hobj = new CHidenObject();
		//hobj->SetPosition(675.0f, 106.0f);
		//hobj->SetSize(7.0f, 7.0f);
		//hobj->SetState(HIDENOBJECT_STATE_JUMP);
		//hobj->Setnx(1);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(695.0f, 75.0f);
		//hobj->SetSize(7.0f, 7.0f);
		//hobj->SetState(HIDENOBJECT_STATE_JUMP);
		//hobj->Setnx(-1);
		//cellsobject->InitCells(hobj);
		break;
	case SCENE_6_3:
		textures->Add(ID_MAP_LEVEL_6, LEVEL6_STAGE17B_PATH, D3DCOLOR_XRGB(255, 255, 255));
		texture_map = textures->Get(ID_MAP_LEVEL_6);
		tilemap->LoadTileMap(STAGE_17B_MAP_DATA, texture_map);

		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cellsobject = new CCells(column, row);

		in.open("Data\\hobj_CT_Scene3.txt");
		for (i = 0; i < 32; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cellsobject->InitCells(object);
		}
		in.close();

		in.open("Data\\door_scene3_CLockTower.txt");

		CInputImage::LoadDoorFromFile(in, door);
		door->SetIsAuto(false);
		door->SetIsStair(true);
		cellsobject->InitCells(door);

		for (i = 0; i < 3; i++)
		{
			CInputImage::LoadDoorFromFile(in, door);
			door->SetIsStair(true);
			cellsobject->InitCells(door);
		}
		in.close();

		//door = new CDoor();
		//door->SetState(DOOR_STATE_NORMAL);
		//door->SetPosition(0.0f, 45.0f);
		//door->SetIsAuto(false);
		//door->SetIsHiDen(true);
		//door->SetIsStair(true);
		//door->SetScene(4);
		//cellsobject->InitCells(door);

		//door = new CDoor();
		//door->SetState(DOOR_STATE_NORMAL);
		//door->SetPosition(80.0f, 170.0f);
		//door->cx = 89.0f;
		//door->cy = -11.0f;
		//door->SetIsHiDen(true);
		//door->SetIsStair(true);
		//door->SetScene(2);
		//cellsobject->InitCells(door);


		//door = new CDoor();
		//door->SetState(DOOR_STATE_NORMAL);
		//door->SetPosition(671.0f, 172.0f);
		//door->cx = 663.04f;
		//door->cy = -12.04f;
		//door->SetIsHiDen(true);
		//door->SetIsStair(true);
		//door->SetScene(2);
		//cellsobject->InitCells(door);

		//door = new CDoor();
		//door->SetState(DOOR_STATE_NORMAL);
		//door->SetPosition(300.0f, 160.0f);
		//door->cx = 312.04f;
		//door->cy = -11.08f;
		//door->SetIsHiDen(true);
		//door->SetIsStair(true);
		//door->SetScene(2);
		//cellsobject->InitCells(door);

		//hobj = new CHidenObject();
		//hobj->SetPosition(639.0f, 145.0f);
		//hobj->SetSize(32.0f, 12.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(1.0f, /*81.0f*/82.0f);
		//hobj->SetSize(32.0f, 94.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(128.0f, 146.0f);
		//hobj->SetSize(30.0f, 29.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(160.0f, 16.0f);
		//hobj->SetSize(32.0f, 159.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(257.0f, /*113.0f*/114.0f);
		//hobj->SetSize(62.0f, 30.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(/*336.0f*/336.0f, /*145.0f*/146.0f);
		//hobj->SetSize(46.0f, 17.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(434.0f, /*144.0f*/146.0f);
		//hobj->SetSize(47.0f, 18.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(368.0f, /*113.0f*/114.0f);
		//hobj->SetSize(79.0f, 16.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(336.0f, /*47.0f*/49.0f);
		//hobj->SetSize(79.0f, 3.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(449.0f, /*47.0f*/49.0f);
		//hobj->SetSize(32.0f, 31.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(481.0f, /*47.0f*/49.0f);
		//hobj->SetSize(190.0f, 14.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//for (int i = 0; i < 5; i++)
		//{
		//	hobj = new CHidenObject();
		//	hobj->SetPosition(481.0f, 63.0f + 16.0f*i);
		//	hobj->SetSize(33.0f, 16.0f);
		//	hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//	cellsobject->InitCells(hobj);
		//}

		//hobj = new CHidenObject();
		//hobj->SetPosition(481.0f, 144.0f);
		//hobj->SetSize(33.0f, 32.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(514.0f, /*145.0f*/146.0f);
		//hobj->SetSize(126.0f, 30.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(705.0f, 81.0f);
		//hobj->SetSize(30.0f, 15.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(705.0f, 145.0f);
		//hobj->SetSize(30.f, 15.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(737.0f, 1.0f);
		//hobj->SetSize(31.0f, 175.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(33.0f, /*81.0f*/82.0f);
		//hobj->SetSize(32.0f, 16.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(1.0f, 1.0f);
		//hobj->SetSize(32.0f, 16.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		//hobj->SetSize(17.0f, 7.0f);
		//hobj->SetPosition(701.0f, 137.0f);
		//hobj->SetStair_XY(697.0f, 115);
		//hobj->nx = -1;
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		//hobj->SetSize(26.0f, 10.0f);
		//hobj->SetPosition(629.0f, 135.0f);
		//hobj->SetStair_XY(634.0f, 113);
		//hobj->nx = 1;
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		//hobj->SetSize(23.0f, 7.0f);
		//hobj->SetPosition(656.0f, 42.0f);
		//hobj->SetStair_XY(665.0f, 19);
		//hobj->nx = 1;
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		//hobj->SetSize(23.0f, 8.0f);
		//hobj->SetPosition(303.0f, 105.0f);
		//hobj->SetStair_XY(313.0f, 83);
		//hobj->nx = 1;
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		//hobj->SetSize(25.0f, 8.0f);
		//hobj->SetPosition(42.0f, 72.0f);
		//hobj->SetStair_XY(57.0f, 50);
		//hobj->nx = 1;
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetState(HIDENOBJECT_STATE_STAIR_UP_DOWN);
		//hobj->SetSize(22.0f, 11.0f);
		//hobj->SetPosition(702.0f, 69.0f);
		//hobj->SetStair_XY(697, 50);
		//hobj->nx = -1;
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetState(HIDENOBJECT_STATE_STAIR_UP_DOWN);
		//hobj->SetSize(24.0f, 11.0f);
		//hobj->SetPosition(349.0f, 133.0f);
		//hobj->SetStair_XY(345.0f, 114);
		//hobj->nx = -1;
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetState(HIDENOBJECT_STATE_STAIR_UP_DOWN);
		//hobj->SetSize(27.0f, 15.0f);
		//hobj->SetPosition(127.0f, 129.0f);
		//hobj->SetStair_XY(122.0f, 114);
		//hobj->nx = -1;
		//cellsobject->InitCells(hobj);
		break;
	case SCENE_6_4:
		textures->Add(ID_MAP_LEVEL_6, LEVEL6_STAGE18A_PATH, D3DCOLOR_XRGB(255, 255, 255));
		texture_map = textures->Get(ID_MAP_LEVEL_6);
		tilemap->LoadTileMap(STAGE_18A_MAP_DATA, texture_map);

		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cellsobject = new CCells(column, row);

		in.open("Data\\ClockTowerLevel_Scene4.txt");
		for (i = 0; i < 3; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cellsobject->InitCells(object);
		}
		in.close();

		in.open("Data\\door_scene4_CLockTower.txt");
		CInputImage::LoadDoorFromFile(in, door);
		door->SetIsStair(true);
		cellsobject->InitCells(door);
		in.close();

		//door = new CDoor();
		//door->SetState(DOOR_STATE_NORMAL);
		//door->SetPosition(100.0f, 0.0f);
		//door->cx = 597.22f;
		//door->cy = 146.22f;
		//door->SetIsHiDen(true);
		//door->SetIsStair(true);
		//door->SetScene(5);
		//cellsobject->InitCells(door);

		//hobj = new CHidenObject();
		//hobj->SetPosition(249.0f, 0.0f);
		//hobj->SetSize(36.0f, 93.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(184.0f, /*81.0f*/82.0f);
		//hobj->SetSize(65.0f, 15.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		//hobj->SetSize(24.0f, 10.0f);
		//hobj->SetPosition(175.0f, 71.0f);
		//hobj->SetStair_XY(177.0f, 50);
		//hobj->nx = -1;
		//cellsobject->InitCells(hobj);
		break;
	case SCENE_6_5:
		textures->Add(ID_MAP_LEVEL_6, LEVEL6_STAGE18B_PATH, D3DCOLOR_XRGB(255, 255, 255));
		texture_map = textures->Get(ID_MAP_LEVEL_6);
		tilemap->LoadTileMap(STAGE_18B_MAP_DATA, texture_map);

		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cellsobject = new CCells(column, row);

		in.open("Data\\hobj_CT_Scene5.txt");
		for (i = 0; i < 6; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cellsobject->InitCells(object);
		}
		in.close();

		in.open("Data\\door_scene5_CLockTower.txt");
		CInputImage::LoadDoorFromFile(in, door);
		door->SetIsStair(true);
		cellsobject->InitCells(door);

		in.close();

		//door = new CDoor();
		//door->SetState(DOOR_STATE_NORMAL);
		//door->SetPosition(607.0f, 175.0f);
		//door->cx = 117.0f;
		//door->cy = -10.0f;
		//door->SetIsHiDen(true);
		//door->SetIsStair(true);
		//door->SetScene(4);
		//cellsobject->InitCells(door);

		//hobj = new CHidenObject();
		//hobj->SetPosition(0.0f, 0.0f);
		//hobj->SetSize(2.0f, 146.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(2.0f, 146.0f);
		//hobj->SetSize(478.0f, 30.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(447.0f, /*113.0f*/114.0f);
		//hobj->SetSize(103.0f, 32.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(257.0f, 0.0f);
		//hobj->SetSize(15.0f, 79.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetPosition(514.0f, 0.0f);
		//hobj->SetSize(30.0f, 47.0f);
		//hobj->SetState(HIDENOBJECT_STATE_NORMAL);
		//cellsobject->InitCells(hobj);

		//hobj = new CHidenObject();
		//hobj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		//hobj->SetSize(21.0f, 10.0f);
		//hobj->SetPosition(527.0f, 103.0f);
		//hobj->SetStair_XY(535.0f, 84);
		//hobj->nx = 1;
		//cellsobject->InitCells(hobj);
		break;
	}
}


void CClockTowerLevel::Update()
{
	CSimon* simon = CSimon::GetInstance();
	if (prev_scene != scene)
	{
		LoadObject();
		LoadMap();
		prev_scene = scene;
		simon->SetReset(false);
	}
	else if (simon->GetReset())
	{
		LoadMap();
		simon->SetReset(false);
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
	if (scene == SCENE_6_1)
	{
		min = MIN_MAP_6_1;
		max = MAX_MAP_6_1;
	}
	else if (scene == SCENE_6_2)
	{
		min = MIN_MAP_6_2;
		max = MAX_MAP_6_2;
	}
	else if (scene == SCENE_6_3)
	{
		min = MIN_MAP_6_3;
		max = MAX_MAP_6_3;
	}
	else if (scene == SCENE_6_4)
	{
		min = MIN_MAP_6_4;
		max = MAX_MAP_6_4;
	}
	else if (scene == SCENE_6_5)
	{
		min = MIN_MAP_6_5;
		max = MAX_MAP_6_5;
	}
}
void CClockTowerLevel::NextScece(float &x, float &y)
{
	if (scene == SCENE_6_1)
	{
		x = 1462.0f;
		y = 112.0f;
	}
	else if (scene == SCENE_6_2)
	{
		x = 727.0f;
		y = 41.0f;
	}
	else if (scene == SCENE_6_4)
	{
		x = 232.0f;
		y = 50.0f;
	}
	else if (SCENE_6_5)
	{
		x = 0;
		y = 0;
	}
}

void CClockTowerLevel::ResetScene()
{
	if (scene == SCENE_6_1)
	{
		scene = SCENE_6_1;
	}
	else if (scene == SCENE_6_2 || scene == SCENE_6_3)
	{
		scene = SCENE_6_2;
	}
	else if (scene == SCENE_6_4 || scene == SCENE_6_5)
	{
		scene = SCENE_6_4;
	}
}
