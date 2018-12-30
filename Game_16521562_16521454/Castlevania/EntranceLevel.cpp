#include "EntranceLevel.h"
#include "Resource.h"
CEntranceLevel *CEntranceLevel::__instance = NULL;

void CEntranceLevel::LoadMap()
{
	CCandle *candle;
	CGhoul *ghoul;
	CSimon *simon = CSimon::GetInstance();
	CBrick *brick;
	CBat *bat;
	CFishman *fishman;
	CBossBat* bossbat;

	switch (scene)
	{
	case SCENE_1:
		simon->SetStage(1);
		int column, row;

		float width, height;
		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cells = new CCells(column, row);

		candle = new CCandle(BIG_CANDLE, HEART);
		candle->SetPosition(85.0f, 111.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		candle = new CCandle(BIG_CANDLE, WHIP_UPDATE);
		candle->SetPosition(222.0f, 111.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		candle = new CCandle(BIG_CANDLE, WHIP_UPDATE);
		candle->SetPosition(343.0f, 111.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		candle = new CCandle(BIG_CANDLE, AXE);
		candle->SetPosition(475.0f, 111.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		candle = new CCandle(BIG_CANDLE, DAGGER);
		candle->SetPosition(600.0f, 111.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		break;
	case SCENE_2:

		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cells = new CCells(column, row);

		/*panther = new CPanther();
		panther->SetState(PANTHER_STATE_IDLE);
		panther->Setnx(-1);
		panther->SetTurn(0);
		panther->SetPosition(690.0f, 79.0f);
		panther->SetTmpPosition(690.0f, 79.0f);
		panther->SetJump(false);
		panther->InitMovingArea();
		cells->InitCells(panther);

		panther = new CPanther();
		panther->Setnx(-1);
		panther->SetState(PANTHER_STATE_IDLE);
		panther->SetPosition(870.0f, 46.0f);
		panther->SetTmpPosition(870.0f, 46.0f);
		panther->SetTurn(0);
		panther->SetJump(false);
		panther->InitMovingArea();
		cells->InitCells(panther);

		panther = new CPanther();
		panther->Setnx(-1);
		panther->SetState(PANTHER_STATE_IDLE);
		panther->SetPosition(931.0f, 79.0f);
		panther->SetTmpPosition(931.0f, 79.0f);
		panther->SetTurn(0);
		panther->SetJump(false);
		panther->InitMovingArea();
		cells->InitCells(panther);*/

		for (int i = 0; i < 5; i++)
		{
			candle = new CCandle(SMALL_CANDLE);
			candle->SetPosition(i * 128.0f + 28.0f, 130.0f);
			candle->SetState(CANDLE_STATE_NORMAL);
			cells->InitCells(candle);
		}

		for (int i = 0; i < 4; i++)
		{
			candle = new CCandle(SMALL_CANDLE);
			candle->SetPosition(i * 128.0f + 90.0f, 115.0f);
			candle->SetState(CANDLE_STATE_NORMAL);
			cells->InitCells(candle);
		}

		for (int i = 0; i < 5; i++)
		{
			candle = new CCandle(SMALL_CANDLE);
			candle->SetPosition(i * 64.0f + 1051.0f, 129);
			candle->SetState(CANDLE_STATE_NORMAL);
			cells->InitCells(candle);
		}

		candle = new CCandle(SMALL_CANDLE);
		candle->SetPosition(603.0f, 96.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		candle = new CCandle(SMALL_CANDLE);
		candle->SetPosition(670.0f, 35.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		candle = new CCandle(SMALL_CANDLE);
		candle->SetPosition(731.0f, 129.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		candle = new CCandle(SMALL_CANDLE);
		candle->SetPosition(797.0f, 5.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		candle = new CCandle(SMALL_CANDLE);
		candle->SetPosition(858.0f, 34.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		candle = new CCandle(SMALL_CANDLE);
		candle->SetPosition(923.0f, 129.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		candle = new CCandle(SMALL_CANDLE);
		candle->SetPosition(991.0f, 32.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		candle = new CCandle(SMALL_CANDLE);
		candle->SetPosition(1370.0f, 94.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		candle = new CCandle(SMALL_CANDLE);
		candle->SetPosition(1436.0f, 35.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		candle = new CCandle(SMALL_CANDLE);
		candle->SetPosition(1500, 2);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		ghoul = new CGhoul();
		ghoul->SetPosition(250.0f, 127.0f);
		ghoul->SetState(GHOUL_STATE_LEFT);
		cells->InitCells(ghoul);

		ghoul = new CGhoul();
		ghoul->SetPosition(290.0f, 127.0f);
		ghoul->SetState(GHOUL_STATE_LEFT);
		cells->InitCells(ghoul);

		ghoul = new CGhoul();
		ghoul->SetPosition(330.0f, 127.0f);
		ghoul->SetState(GHOUL_STATE_LEFT);
		cells->InitCells(ghoul);
		break;
	case SCENE_3:
		simon->SetStage(2);

		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cells = new CCells(column, row);
		brick = new CBrick(1792.0f, 127.0f);
		brick->SetState(BRICK_STATE_FULL);
		cells->InitCells(brick);

		bat = new CBat(BAT_SIZE_SMALL);
		bat->SetPosition(1600.0f, 0.0f);
		bat->SetPosstionAppear(1770, 40);
		bat->SetSize(16, 62);
		bat->SetState(BAT_STATE_SLEEPING);
		bat->SetStateAppear(BAT_STATE_FLY_LEFT);
		bat->SetHeightFly(35.0f);
		cells->InitCells(bat);

		bat = new CBat(BAT_SIZE_SMALL);
		bat->SetPosition(1774.0f, 143.0f);
		bat->SetPosstionAppear(1900, 135);
		bat->SetSize(18, 15);
		bat->SetState(BAT_STATE_SLEEPING);
		bat->SetStateAppear(BAT_STATE_FLY_LEFT);
		bat->SetHeightFly(135.0f);
		cells->InitCells(bat);

		bat = new CBat(BAT_SIZE_SMALL);
		bat->SetPosition(1679.0f, 108.0f);
		bat->SetPosstionAppear(1550, 135);
		bat->SetSize(22, 51);
		bat->SetState(BAT_STATE_SLEEPING);
		bat->SetStateAppear(BAT_STATE_FLY_RIGHT);
		bat->SetHeightFly(135.0f);
		cells->InitCells(bat);

		bat = new CBat(BAT_SIZE_SMALL);
		bat->SetPosition(1904.0f, 108.0f);
		bat->SetPosstionAppear(1750, 135);
		bat->SetSize(18, 49);
		bat->SetState(BAT_STATE_SLEEPING);
		bat->SetStateAppear(BAT_STATE_FLY_RIGHT);
		bat->SetHeightFly(135.0f);
		cells->InitCells(bat);

		bat = new CBat(BAT_SIZE_SMALL);
		bat->SetPosition(1951.0f, 0.0f);
		bat->SetPosstionAppear(1800, 135);
		bat->SetSize(18, 62);
		bat->SetState(BAT_STATE_SLEEPING);
		bat->SetStateAppear(BAT_STATE_FLY_RIGHT);
		bat->SetHeightFly(35.0f);
		cells->InitCells(bat);

		candle = new CCandle(SMALL_CANDLE);
		candle->SetPosition(1629.0f, 33.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		candle = new CCandle(SMALL_CANDLE);
		candle->SetPosition(1567.0f, 130.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		candle = new CCandle(SMALL_CANDLE);
		candle->SetPosition(1689.0f, 18.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		candle = new CCandle(SMALL_CANDLE);
		candle->SetPosition(1837.0f, 17.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		candle = new CCandle(SMALL_CANDLE);
		candle->SetPosition(1757.0f, 97.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		candle = new CCandle(SMALL_CANDLE);
		candle->SetPosition(1885.0f, 129.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		candle = new CCandle(SMALL_CANDLE);
		candle->SetPosition(1946.0f, 18.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		candle = new CCandle(SMALL_CANDLE);
		candle->SetPosition(2004.0f, 36.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		break;

	case SCENE_4:

		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cells = new CCells(column, row);

		fishman = new CFishman();
		fishman->SetPostionAppear(164.0f, 164.0f);
		fishman->SetPosition(96, 0);
		fishman->SetSize(48, 83);
		fishman->SetState(MONSTER_STATE_SLEEPING);
		fishman->SetStateAppear(FISHMAN_STATE_JUMP);
		fishman->Setnx(-1);
		cells->InitCells(fishman);

		fishman = new CFishman();
		fishman->SetPostionAppear(20.0f, 164.0f);
		fishman->SetPosition(96, 0);
		fishman->SetSize(48, 83);
		fishman->SetState(MONSTER_STATE_SLEEPING);
		fishman->SetStateAppear(FISHMAN_STATE_JUMP);
		fishman->Setnx(1);
		cells->InitCells(fishman);

		fishman = new CFishman();
		fishman->SetPostionAppear(326.0f, 164.0f);
		fishman->SetPosition(368, 0);
		fishman->SetSize(81, 83);
		fishman->SetState(MONSTER_STATE_SLEEPING);
		fishman->SetStateAppear(FISHMAN_STATE_JUMP);
		fishman->Setnx(-1);
		cells->InitCells(fishman);

		fishman = new CFishman();
		fishman->SetPostionAppear(450.0f, 164.0f);
		fishman->SetPosition(368, 0);
		fishman->SetSize(81, 83);
		fishman->SetState(MONSTER_STATE_SLEEPING);
		fishman->SetStateAppear(FISHMAN_STATE_JUMP);
		fishman->Setnx(1);
		cells->InitCells(fishman);

		break;
	case SCENE_5:
		simon->SetStage(3);
		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cells = new CCells(column, row);

		ghoul = new CGhoul();
		ghoul->SetPosition(2062.0f, 127.0f);
		ghoul->SetState(GHOUL_STATE_RIGHT);
		ghoul->SetLimitArea(2050, 2352);
		cells->InitCells(ghoul);

		ghoul = new CGhoul();
		ghoul->SetPosition(2153.0f, 127.0f);
		ghoul->SetState(GHOUL_STATE_LEFT);
		ghoul->SetLimitArea(2050, 2352);
		cells->InitCells(ghoul);

		candle = new CCandle(SMALL_CANDLE);
		candle->SetPosition(2140.0f, 34.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		candle = new CCandle(SMALL_CANDLE);
		candle->SetPosition(2077.0f, 93.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		candle = new CCandle(SMALL_CANDLE);
		candle->SetPosition(2205.0f, 67.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		candle = new CCandle(SMALL_CANDLE/*, INVINCIBILITY_POTION*/);
		candle->SetPosition(2268.0f, 37.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		candle = new CCandle(SMALL_CANDLE, AXE);
		candle->SetPosition(2397.0f, 101.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		candle = new CCandle(SMALL_CANDLE);
		candle->SetPosition(2333.0f, 132.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		for (int i = 0; i < 2; i++)
		{
			candle = new CCandle(SMALL_CANDLE);
			candle->SetPosition(i * 66.0f + 2460.0f, 131.0f);
			candle->SetState(CANDLE_STATE_NORMAL);
			cells->InitCells(candle);
		}

		for (int i = 0; i < 2; i++)
		{
			candle = new CCandle(SMALL_CANDLE);
			candle->SetPosition(i * 128.0f + 2588.0f, 99.0f);
			candle->SetState(CANDLE_STATE_NORMAL);
			cells->InitCells(candle);
		}

		candle = new CCandle(SMALL_CANDLE);
		candle->SetPosition(2652.0f, 130.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		bossbat = CBossBat::GetInstance();
		bossbat->SetPosition(2666.0f, 0.0f);
		bossbat->SetState(BOSS_BAT_STATE_SLEEP);
		cells->InitCells(bossbat);
		break;
	}
}

void CEntranceLevel::LoadObject()
{
	LPDIRECT3DTEXTURE9 texture_map;
	CHidenObject *hidenObj;
	CDoor *door;
	CSimon *simon = CSimon::GetInstance();
	switch (scene)
	{
	case SCENE_1:
		simon->SetStage(1);
		textures->Add(ID_MAP_LEVEL_1, LEVEL_1_STAGE1A_PATH, D3DCOLOR_XRGB(255, 255, 255));
		texture_map = textures->Get(ID_MAP_LEVEL_1);
		tilemap->LoadTileMap(STAGE_1A_MAP_DATA, texture_map);


		int column, row;

		float width, height;
		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cellsobject = new CCells(column, row);

		hidenObj = new CHidenObject();
		hidenObj->SetSize(768.0f, 16.0f);
		hidenObj->SetPosition(0, 146);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetSize(1.0f, 145.0f);
		hidenObj->SetPosition(1, 0);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetSize(16.0f, 88.0f);
		hidenObj->SetPosition(707.0f, 57.0f);
		hidenObj->SetState(HIDENOBJECT_STATE_CASTLE_GATE);
		cellsobject->InitCells(hidenObj);

		door = new CDoor();
		door->SetPosition(672.0f, 105.0f);
		door->size = 30;
		door->SetIsHiDen(true);
		door->SetScene(2);
		cellsobject->InitCells(door);
		break;
	case SCENE_2:
		textures->Add(ID_MAP_LEVEL_1, LEVEL_1_STAGE1B_PATH, D3DCOLOR_XRGB(255, 255, 255));
		texture_map = textures->Get(ID_MAP_LEVEL_1);
		tilemap = new CTileMap();
		tilemap->LoadTileMap(STAGE_1B_MAP_DATA, texture_map);
		//int column, row;

		//float width, height;
		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cellsobject = new CCells(column, row);

		hidenObj = new CHidenObject();
		hidenObj->SetSize(1530.0f, 15.0f);
		hidenObj->SetPosition(0.0f, /*160.0f*/161.0f);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetSize(147, 14);
		hidenObj->SetPosition(1386.0f, 67.0f);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetSize(1.0f, 160.0f);
		hidenObj->SetPosition(1.0f, 0.0f);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetSize(1.0f, 81.0f);
		hidenObj->SetPosition(1527.0f, 78.0f);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		hidenObj->SetSize(40.0f, 12.0f);
		hidenObj->SetPosition(607.0f, 148.0f);
		hidenObj->SetStair_XY(617.0f, 130.0f);
		hidenObj->nx = 1;
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		hidenObj->SetSize(27.0f, 11.0f);
		hidenObj->SetPosition(706.0f, 84.0f);
		hidenObj->SetStair_XY(714.0f, 66.0f);
		hidenObj->nx = 1;
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		hidenObj->SetSize(33.0f, 20.0f);
		hidenObj->SetPosition(929.0f, 80.0f);
		hidenObj->SetStair_XY(937.0f, 64);
		hidenObj->nx = -1;
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		hidenObj->SetSize(27.0f, 13.0f);
		hidenObj->SetPosition(1283.0f, 149.0f);
		hidenObj->SetStair_XY(1289.0f, 128);
		hidenObj->nx = 1;
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		hidenObj->SetSize(23.0f, 13.0f);
		hidenObj->SetPosition(682.0f, 81.0f);
		hidenObj->SetStair_XY(681.0f, 65);
		hidenObj->nx = -1;
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		hidenObj->SetSize(23.0f, 13.0f);
		hidenObj->SetPosition(746.0f, 52.0f);
		hidenObj->SetStair_XY(745.0f, 34);
		hidenObj->nx = -1;
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		hidenObj->SetSize(24.0f, 15.0f);
		hidenObj->SetPosition(895.0f, 50.0f);
		hidenObj->SetStair_XY(904.0f, 33);
		hidenObj->nx = 1;
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		hidenObj->SetSize(56.0f, 15.0f);
		hidenObj->SetPosition(1390.0f, 50.0f);
		hidenObj->SetStair_XY(1384.0f, 33);
		hidenObj->nx = -1;
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_JUMP);
		hidenObj->SetPosition(681.0f, 91.0f);
		hidenObj->SetSize(5.0f, 7.0f);;
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_JUMP);
		hidenObj->SetPosition(741.0f, 62.0f);
		hidenObj->SetSize(5.0f, 7.0f);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_JUMP);
		hidenObj->SetPosition(745.0f, 93.0f);
		hidenObj->SetSize(5.0f, 7.0f);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_JUMP);
		hidenObj->SetPosition(913.0f, 61.0f);
		hidenObj->SetSize(5.0f, 7.0f);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_JUMP);
		hidenObj->SetPosition(909.0f, 94.0f);
		hidenObj->SetSize(5.0f, 7.0f);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_JUMP);
		hidenObj->SetPosition(1025.0f, 91.0f);
		hidenObj->SetSize(5.0f, 7.0f);
		cellsobject->InitCells(hidenObj);


		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetSize(48.0f, 15.0f);
		hidenObj->SetPosition(688.0f, 98.0f);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(752.0f, 66.0f);
		hidenObj->SetSize(160.0, 15.0f);
		cellsobject->InitCells(hidenObj);

		/*hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(816.0f, 64.0f);
		hidenObj->SetSize(64.0f, 15.0f);
		cellsobject->InitCells(hidenObj);*/

		/*hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(879.0f, 64.0f);
		hidenObj->SetSize(32.0f, 15.0f);
		cellsobject->InitCells(hidenObj);*/

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(928.0f, 98.0f);
		hidenObj->SetSize(96.0f, 15.0f);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(1535.0f, 67.0f);
		hidenObj->SetSize(130.0f, 14.0f);
		cellsobject->InitCells(hidenObj);

		/*hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(992.0f, 96.0f);
		hidenObj->SetSize(32.0f, 15.0f);
		cellsobject->InitCells(hidenObj);*/




		/*for (int i = 0; i < 3; i++)
		{
			hidenObj = new CHidenObject();
			hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
			hidenObj->SetPosition(i * 48.0f + 1392.0f, 66.0f);
			hidenObj->SetSize(48.0f, 15.0f);
			cellsobject->InitCells(hidenObj);
		}*/

		door = new CDoor();
		door->SetState(DOOR_STATE_NORMAL);
		door->SetPosition(1530.0f, 15.0f);
		door->SetIsHiDen(false);
		door->SetScene(3);
		cellsobject->InitCells(door);
		/*for (int i = 0; i < 3; i++)
		{
			hidenObj = new CHidenObject();
			hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
			hidenObj->SetPosition(i * 64.0f + 1550.0f, 66.0f);
			hidenObj->SetSize(64.0f, 15.0f);
			cellsobject->InitCells(hidenObj);
		}*/
		break;
	case SCENE_3:
		simon->SetStage(2);
		textures->Add(ID_MAP_LEVEL_1, LEVEL_1_STAGE1B_PATH, D3DCOLOR_XRGB(255, 255, 255));
		texture_map = textures->Get(ID_MAP_LEVEL_1);
		tilemap->LoadTileMap(STAGE_1B_MAP_DATA, texture_map);

		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cellsobject = new CCells(column, row);

		hidenObj = new CHidenObject();
		hidenObj->SetPosition(1535.0f, 12.0f);
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetSize(5.0f, 51.0f);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(1792.0f, 81.0f);
		hidenObj->SetSize(33.0f, 32.0f);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(1824.0f, 81.0f);
		hidenObj->SetSize(33.0f, 80.0f);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(1792.0f, 110.0f);
		hidenObj->SetSize(17.0f, 16.0f);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(1808.0f, 110.0f);
		hidenObj->SetSize(17.0f, 49.0f);
		cellsobject->InitCells(hidenObj);

		door = new CDoor();
		door->SetState(DOOR_STATE_NORMAL);
		door->SetPosition(1921.0f, 166.0f);
		door->cx = 377.52f;
		door->cy = -12.48f;
		door->SetIsHiDen(true);
		door->IsGo = true;
		door->SetIsStair(true);
		door->SetScene(4);
		cellsobject->InitCells(door);

		door = new CDoor();
		door->SetState(DOOR_STATE_NORMAL);
		door->SetPosition(1600.0f, 166.0f);
		door->cx = 59.3f;
		door->cy = -11.74f;
		door->SetIsHiDen(true);
		door->IsGo = true;
		door->SetIsStair(true);
		door->SetScene(4);
		cellsobject->InitCells(door);

		door = new CDoor();
		door->SetState(DOOR_STATE_NORMAL);
		door->SetPosition(2042.0f, 13.0f);
		door->SetIsHiDen(false);
		door->IsGo = true;
		door->SetScene(5);
		cellsobject->InitCells(door);

		/*for (int i = 0; i < 2; i++)
		{
			hidenObj = new CHidenObject();
			hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
			hidenObj->SetPosition(i * 64.0f + 1535.0f, 65.0f);
			hidenObj->SetSize(64.0f, 15.0f);
			cellsobject->InitCells(hidenObj);
		}*/

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(1535.0f, /*66.0f*/67.0f);
		hidenObj->SetSize(128.0f, 15.0f);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(1539.0f, 162.0f);
		hidenObj->SetSize(/*64.0f*/513.0f, 15.0f);
		cellsobject->InitCells(hidenObj);

		/*hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(1904.0f, 160.0f);
		hidenObj->SetSize(18.0f, 15.0f);
		cellsobject->InitCells(hidenObj);*/

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(1539.0f, 77.0f);
		hidenObj->SetSize(5.0f, 82.0f);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(1529.0f, 0.0f);
		hidenObj->SetSize(15.0f, 12.0f);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(1953, 65);
		hidenObj->SetSize(129.0f, 15.0f);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(2040, 77);
		hidenObj->SetSize(5.0f, 79.0f);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(2016, 0);
		hidenObj->SetSize(32.0f, 12.0f);
		cellsobject->InitCells(hidenObj);
		/*for (int i = 0; i < 4; i++)
		{
			hidenObj = new CHidenObject();
			hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
			hidenObj->SetPosition(i * 64.0f + 1600.0f, 160.0f);
			hidenObj->SetSize(64.0f, 15.0f);
			cellsobject->InitCells(hidenObj);
		}*/

		/*for (int i = 0; i < 2; i++)
		{
			hidenObj = new CHidenObject();
			hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
			hidenObj->SetPosition(i * 64.0f + 1922.0f, 160.0f);
			hidenObj->SetSize(64.0f, 15.0f);
			cellsobject->InitCells(hidenObj);
		}*/

		/*for (int i = 0; i < 2; i++)
		{
			hidenObj = new CHidenObject();
			hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
			hidenObj->SetPosition(i * 48.0f + 1953.0f, 160.0f);
			hidenObj->SetSize(48.0f, 15.0f);
			cellsobject->InitCells(hidenObj);
		}*/

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(1665.0f, 97.0f);
		hidenObj->SetSize(48.0f, 15.0f);
		cellsobject->InitCells(hidenObj);

		/*hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(1857.0f, 160.0f);
		hidenObj->SetSize(48.0f, 15.0f);
		cellsobject->InitCells(hidenObj);*/

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(1889.0f, 97.0f);
		hidenObj->SetSize(48.0f, 15.0f);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(1857, 81);
		hidenObj->SetSize(32.0f, 15.0f);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		hidenObj->SetPosition(1695.0f, 80.0f);
		hidenObj->SetStair_XY(1705.0f, 64);
		hidenObj->SetSize(20.0f, 16.0f);
		hidenObj->nx = 1;
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		hidenObj->SetPosition(1760.0f, 147.0f);
		hidenObj->SetStair_XY(1768.0f, 128);
		hidenObj->SetSize(24.0f, 11.0f);
		hidenObj->nx = -1;
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		hidenObj->SetPosition(1920.0f, 78.0f);
		hidenObj->SetStair_XY(1929.0f, 64);
		hidenObj->SetSize(21.0f, 16.0f);
		hidenObj->nx = 1;
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		hidenObj->SetPosition(1984.0f, 147.0f);
		hidenObj->SetStair_XY(1993.0f, 128);
		hidenObj->SetSize(27.0f, 11.0f);
		hidenObj->nx = -1;
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		hidenObj->SetPosition(1567.0f, 147.0f);
		hidenObj->SetStair_XY(1575.0f, 128);
		hidenObj->SetSize(30.0f, 15.0f);
		hidenObj->nx = 1;
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		hidenObj->SetPosition(1888.0f, 147.0f);
		hidenObj->SetStair_XY(1896.0f, 128);
		hidenObj->SetSize(30.0f, 15.0f);
		hidenObj->nx = 1;
		cellsobject->InitCells(hidenObj);
		break;
	case SCENE_4:

		textures->Add(ID_MAP_LEVEL_1, LEVEL_1_STAGE2B_PATH, D3DCOLOR_XRGB(255, 255, 255));
		texture_map = textures->Get(ID_MAP_LEVEL_1);

		//tilemap = new CTileMap();
		tilemap->LoadTileMap(STAGE_2B_MAP_DATA, texture_map);

		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cellsobject = new CCells(column, row);



		door = new CDoor();
		door->SetState(DOOR_STATE_NORMAL);
		door->SetPosition(42.0f, 0.0f);
		door->cx = 1585.96f;
		door->cy = 139.03f;
		door->SetIsHiDen(true);
		door->IsGo = true;
		door->SetIsStair(true);
		door->SetScene(3);
		cellsobject->InitCells(door);


		door = new CDoor();
		door->SetState(DOOR_STATE_NORMAL);
		door->SetPosition(360.0f, 0.0f);
		door->cx = 1906.3f;
		door->cy = 138.3f;
		door->SetIsHiDen(true);
		door->IsGo = true;
		door->SetIsStair(true);
		door->SetScene(3);
		cellsobject->InitCells(door);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		hidenObj->SetPosition(88.0f, 39.0f);
		hidenObj->SetStair_XY(89.0f, 18);
		hidenObj->SetSize(25.0f, 12.0f);
		hidenObj->nx = -1;
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		hidenObj->SetPosition(432.0f, 68.0f);
		hidenObj->SetStair_XY(440.0f, 50);
		hidenObj->SetSize(21.0f, 14.0f);
		hidenObj->nx = -1;
		cellsobject->InitCells(hidenObj);


		/*for (int i = 0; i < 7; i++)
		{
			hidenObj = new CHidenObject();
			hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
			hidenObj->SetPosition(i * 32.0f, 83.0f);
			hidenObj->SetSize(32.0f, 15.0f);
			cellsobject->InitCells(hidenObj);
		}*/

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(0.0f, 83.0f);
		hidenObj->SetSize(224.0f, 15.0f);
		cellsobject->InitCells(hidenObj);
		/*for (int i = 0; i < 5; i++)
		{
			hidenObj = new CHidenObject();
			hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
			hidenObj->SetPosition(i * 32.0f + 320.0f, 82.0f);
			hidenObj->SetSize(32.0f, 15.0f);
			cellsobject->InitCells(hidenObj);
		}*/

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(320.0f, 83.0f);
		hidenObj->SetSize(161.0f, 14.0f);
		cellsobject->InitCells(hidenObj);

		/*for (int i = 0; i < 7; i++)
		{
			hidenObj = new CHidenObject();
			hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
			hidenObj->SetPosition(504.0f, i * 16.0f);
			hidenObj->SetSize(8.0f, 16.0f);
			cellsobject->InitCells(hidenObj);
		}*/

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(504.0f, 0.0f);
		hidenObj->SetSize(8.0f, 96.0f);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(97.0f, 50.0f);
		hidenObj->SetSize(32.0f, 15.0f);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(257.0f, 83.0f);
		hidenObj->SetSize(32.0f, 15.0f);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(481.0f, 114.0f);
		hidenObj->SetSize(32.0f, 15.0f);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(449.0f, 146.0f);
		hidenObj->SetSize(32.0f, 15.0f);
		cellsobject->InitCells(hidenObj);

		break;
	case SCENE_5:
		simon->SetStage(3);
		textures->Add(ID_MAP_LEVEL_1, LEVEL_1_STAGE1B_PATH, D3DCOLOR_XRGB(255, 255, 255));
		texture_map = textures->Get(ID_MAP_LEVEL_1);

		tilemap->LoadTileMap(STAGE_1B_MAP_DATA, texture_map);

		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cellsobject = new CCells(column, row);


		hidenObj = new CHidenObject();
		hidenObj->SetPosition(2049.0f, /*65.0f*/66.0f);
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetSize(112.0f, 15.0f);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetPosition(2040.0f, /*160.0f*/161.0f);
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetSize(780.0f, 16.0f);
		//hidenObj->SetSize(176.0f, 15.0f);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetPosition(2177.0f, /*97.0f*/98.0f);
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetSize(176.0f, 15.0f);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetPosition(2721.0f, /*127.0f*/129.0f);
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetSize(30.0f, 13.0f);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetPosition(2771.0f, /*94.0f*/98.0f);
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetSize(44.0f, 14.0f);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetPosition(2145.0f, 48.0f);
		hidenObj->SetSize(20.0f, 17.0f);
		hidenObj->SetStair_XY(2153, 32);
		hidenObj->nx = 1;
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetPosition(2177.0f, 86.0f);
		hidenObj->SetSize(32.0f, 12.0f);
		hidenObj->SetStair_XY(2184, 65);
		hidenObj->nx = -1;
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetPosition(2335.0f, 81.0f);
		hidenObj->SetSize(23.0f, 16.0f);
		hidenObj->SetStair_XY(2345, 65);
		hidenObj->nx = 1;
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetPosition(2400.0f, 150.0f);
		hidenObj->SetSize(33.0f, 11.0f);
		hidenObj->SetStair_XY(2409, 128);
		hidenObj->nx = -1;
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		cellsobject->InitCells(hidenObj);


		hidenObj = new CHidenObject();
		hidenObj->SetPosition(2727.0f, 117.0f);
		hidenObj->SetSize(25.0f, 13.0f);
		hidenObj->SetStair_XY(2730, 96);
		hidenObj->nx = 1;
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		cellsobject->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetPosition(2762.0f, 81.0f);
		hidenObj->SetSize(25.0f, 16.0f);
		hidenObj->SetStair_XY(2760, 65);
		hidenObj->nx = -1;
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		cellsobject->InitCells(hidenObj);
		break;
	}
}

void CEntranceLevel::Update()
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

void CEntranceLevel::Render()
{
	/*switch(scene)
	{
	case SCENE_1:
		tilemap->Render(0.0f, 0.0f);
		break;
	case SCENE_2:
		tilemap->Render(0.0f, 0.0f);
		break;
	}*/
	tilemap->Render(0.0f, 0.0f);
}

void CEntranceLevel::GetSizeMap(float &min, float &max)
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

CEntranceLevel * CEntranceLevel::GetInstance()
{
	if (__instance == NULL) __instance = new CEntranceLevel();
	return __instance;
}
void CEntranceLevel::NextScece(float &x, float &y)
{
	if (scene == SCENE_1)
	{
		x = 10.0f;
		y = 114.5f;
	}
	else if (scene == SCENE_2)
	{
		x = 10.0f;
		y = 127.0f;
	}
	else if (scene == SCENE_3)
	{
		x = 1555.7f;
		y = 34.6f;
	}
	else if (scene == SCENE_5)
	{
		x = 2062.1f;
		y = 34.6f;
	}
}

void CEntranceLevel::ResetScene()
{
	if (scene == SCENE_1)
	{
		scene = SCENE_1;
	}
	else if (scene == SCENE_2)
	{
		scene = SCENE_2;
	}
	else if (scene == SCENE_4 || scene == SCENE_3)
	{
		scene = SCENE_3;
	}
	else if (scene == SCENE_5)
	{
		scene == SCENE_5;
	}
}
