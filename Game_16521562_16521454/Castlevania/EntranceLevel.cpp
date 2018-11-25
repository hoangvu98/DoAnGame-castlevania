#include "EntranceLevel.h"
#include "Resource.h"
CEntranceLevel *CEntranceLevel::__instance = NULL;

void CEntranceLevel::LoadMap()
{
	ifstream in;
	textures->Add(ID_CANDLE, CANDLE_TEXTURE_PATH, D3DCOLOR_XRGB(34, 177, 76));
	LPDIRECT3DTEXTURE9 texture_map;
	LPANIMATION ani = new CAnimation(100);
	LPDIRECT3DTEXTURE9 texture_candle = textures->Get(ID_CANDLE);
	float c_x, c_y;
	CCandle *candle;
	CDoor *door;
	CPanther *panther;
	CGhoul *ghoul;
	CSimon *simon = CSimon::GetInstance();
	CHidenObject *hidenObj;
	switch (scene)
	{
	case SCENE_1:
		
		textures->Add(ID_MAP_LEVEL_1, LEVEL_1_STAGE1A_PATH, D3DCOLOR_XRGB(255, 255, 255));
		texture_map = textures->Get(ID_MAP_LEVEL_1);
		tilemap->LoadTileMap(STAGE_1A_MAP_DATA, texture_map);
		
	
		int column, row;

		float width, height;
		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cells = new CCells(column, row);

		candle = new CCandle(BIG_CANDLE, DAGGER);
		candle->SetPosition(85.0f, 111.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		candle = new CCandle(BIG_CANDLE, HEART_SMALL);
		candle->SetPosition(222.0f, 111.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		candle = new CCandle(BIG_CANDLE,MONEY_BAG);
		candle->SetPosition(343.0f, 111.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		candle = new CCandle(BIG_CANDLE,AXE);
		candle->SetPosition(475.0f, 111.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		candle = new CCandle(BIG_CANDLE, /*DAGGER*/BOOMERANG);
		candle->SetPosition(600.0f, 111.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle);

		for (int i = 0; i < 13; i++)
		{
			CHidenObject *hidenObj = new CHidenObject();
			hidenObj->SetSize(64.0f, 15.0f);
			hidenObj->SetPosition(i * 64.0f, 145.0f);
			cells->InitCells(hidenObj);
		}
		hidenObj = new CHidenObject();
		hidenObj->SetSize(2.0f, 145.0f);
		hidenObj->SetPosition(0, 0);
		cells->InitCells(hidenObj);

	/*	hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_DOOR);
		hidenObj->SetSize(10.0f, 145.0f);
		hidenObj->SetPosition(625.0f, 0);
		cells->InitCells(hidenObj);*/

		door = new CDoor();
		door->SetPosition(672.0f, 105.0f);
		door->SetIsHiDen(true);
		cells->InitCells(door);

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

		cells = new CCells(column, row);

		for (int i = 0; i < 25; i++)
		{
			hidenObj = new CHidenObject();
			hidenObj->SetSize(64.0f, 15.0f);
			hidenObj->SetPosition(i * 64.0f, 160.0f);
			cells->InitCells(hidenObj);
		}
		hidenObj = new CHidenObject();
		hidenObj->SetSize(147,14);
		hidenObj->SetPosition(1386.0f, 66.0f);
		cells->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		hidenObj->SetSize(40.0f, 12.0f);
		hidenObj->SetPosition(607.0f, 148.0f);
		hidenObj->SetStair_X(607.0f);
		hidenObj->nx = 1;
		cells->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		hidenObj->SetSize(27.0f, 11.0f);
		hidenObj->SetPosition(706.0f, 84.0f);
		hidenObj->SetStair_X(706.0f);
		hidenObj->nx = 1;
		cells->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		hidenObj->SetSize(33.0f, 20.0f);
		hidenObj->SetPosition(929.0f, 80.0f);
		hidenObj->SetStair_X(930.0f);
		hidenObj->nx = -1;
		cells->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		hidenObj->SetSize(27.0f, 13.0f);
		hidenObj->SetPosition(1283.0f, 149.0f);
		hidenObj->SetStair_X(1282.0f);
		hidenObj->nx = 1;
		cells->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		hidenObj->SetSize(23.0f, 13.0f);
		hidenObj->SetPosition(682.0f, 81.0f);
		hidenObj->SetStair_X(689.0f);
		hidenObj->nx = -1;
		cells->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		hidenObj->SetSize(23.0f, 13.0f);
		hidenObj->SetPosition(746.0f, 52.0f);
		hidenObj->SetStair_X(754.0f);
		hidenObj->nx = -1;
		cells->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		hidenObj->SetSize(24.0f, 15.0f);
		hidenObj->SetPosition(895.0f, 50.0f);
		hidenObj->SetStair_X(912.0f);
		hidenObj->nx = 1;
		cells->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		hidenObj->SetSize(56.0f, 15.0f);
		hidenObj->SetPosition(1385.0f, 50.0f);
		hidenObj->SetStair_X(1393.0f);
		hidenObj->nx = -1;
		cells->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_JUMP);
		hidenObj->SetPosition(681.0f, 91.0f);
		hidenObj->SetSize(5.0f, 7.0f);;
		cells->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_JUMP);
		hidenObj->SetPosition(741.0f, 62.0f);
		hidenObj->SetSize(5.0f, 7.0f);
		cells->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_JUMP);
		hidenObj->SetPosition(736.0f, 93.0f);
		hidenObj->SetSize(5.0f, 7.0f);
		cells->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_JUMP);
		hidenObj->SetPosition(913.0f, 61.0f);
		hidenObj->SetSize(5.0f, 7.0f);
		cells->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_JUMP);
		hidenObj->SetPosition(921.0f, 94.0f);
		hidenObj->SetSize(5.0f, 7.0f);
		cells->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_JUMP);
		hidenObj->SetPosition(1025.0f, 91.0f);
		hidenObj->SetSize(5.0f, 7.0f);
		cells->InitCells(hidenObj);


		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetSize(55.0f, 15.0f);
		hidenObj->SetPosition(681.0f, 96.0f);
		cells->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(752.0f, 64.0f);
		hidenObj->SetSize(64.0f, 15.0f);
		cells->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(816.0f, 64.0f);
		hidenObj->SetSize(64.0f, 15.0f);
		cells->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(879.0f, 64.0f);
		hidenObj->SetSize(32.0f, 15.0f);
		cells->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(928.0f, 96.0f);
		hidenObj->SetSize(64.0f, 15.0f);
		cells->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(992.0f, 96.0f);
		hidenObj->SetSize(32.0f, 15.0f);
		cells->InitCells(hidenObj);

		panther = new CPanther();

		

		/*panther->SetState(PANTHER_STATE_IDLE);
		panther->Setnx(-1);
		panther->SetTurn(0);
		panther->SetPosition(690.0f, 80.0f);
		panther->SetJump(false);
		panther->InitMovingArea();
		cells->InitCells(panther);

		panther = new CPanther();
		panther->Setnx(-1);
		panther->SetState(PANTHER_STATE_IDLE);
		panther->SetPosition(882.0f, 48.0f);
		panther->SetTurn(0);
		panther->SetJump(false);
		panther->InitMovingArea();
		cells->InitCells(panther);

		panther = new CPanther();
		panther->Setnx(-1);
		panther->SetState(PANTHER_STATE_IDLE);
		panther->SetPosition(931.0f, 80.0f);
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

	/*	ghoul = new CGhoul();
		ghoul->SetPosition(250.0f, 127.0f);
		ghoul->SetState(GHOUL_STATE_RIGHT);
		cells->InitCells(ghoul);*/

		for (int i = 0; i < 3; i++)
		{
			hidenObj = new CHidenObject();
			hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
			hidenObj->SetPosition(i * 48.0f + 1392.0f, 65.0f);
			hidenObj->SetSize(48.0f, 15.0f);
			cells->InitCells(hidenObj);
		}

		door = new CDoor();
		door->SetState(DOOR_STATE_CLOSE);
		door->SetPosition(1530.0f, 15.0f);
		door->SetIsHiDen(false);
		cells->InitCells(door);
		for (int i = 0; i < 2; i++)
		{
			hidenObj = new CHidenObject();
			hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
			hidenObj->SetPosition(i * 64.0f + 1550.0f, 65.0f);
			hidenObj->SetSize(64.0f, 15.0f);
			cells->InitCells(hidenObj);
		}
		break;
	case SCENE_3:
		for (int i = 0; i < 2; i++)
		{
			hidenObj = new CHidenObject();
			hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
			hidenObj->SetPosition(i * 64.0f + 1535.0f, 65.0f);
			hidenObj->SetSize(64.0f, 15.0f);
			cells->InitCells(hidenObj);
		}

		for (int i = 0; i < 4; i++)
		{
			hidenObj = new CHidenObject();
			hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
			hidenObj->SetPosition(i * 64.0f + 1600.0f, 160.0f);
			hidenObj->SetSize(64.0f, 15.0f);
			cells->InitCells(hidenObj);
		}

		for (int i = 0; i < 2; i++)
		{
			hidenObj = new CHidenObject();
			hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
			hidenObj->SetPosition(i * 64.0f + 1922.0f, 160.0f);
			hidenObj->SetSize(64.0f, 15.0f);
			cells->InitCells(hidenObj);
		}

		for (int i = 0; i < 2; i++)
		{
			hidenObj = new CHidenObject();
			hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
			hidenObj->SetPosition(i * 48.0f + 1953.0f, 160.0f);
			hidenObj->SetSize(48.0f, 15.0f);
			cells->InitCells(hidenObj);
		}

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(1665.0f, 97.0f);
		hidenObj->SetSize(48.0f, 15.0f);
		cells->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(1857.0f, 160.0f);
		hidenObj->SetSize(48.0f, 15.0f);
		cells->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(1889.0f, 97.0f);
		hidenObj->SetSize(48.0f, 15.0f);
		cells->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(1857, 81);
		hidenObj->SetSize(32.0f, 15.0f);
		cells->InitCells(hidenObj);

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
		textures->Add(ID_MAP_LEVEL_1, LEVEL_1_STAGE2B_PATH, D3DCOLOR_XRGB(255, 255, 255));
		texture_map = textures->Get(ID_MAP_LEVEL_1);

		tilemap = new CTileMap();
		tilemap->LoadTileMap(STAGE_2B_MAP_DATA, texture_map);

		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cells = new CCells(column, row);

		for (int i = 0; i < 7; i++)
		{
			candle = new CCandle(SMALL_CANDLE);
			candle->SetState(CANDLE_STATE_NORMAL);
			candle->SetPosition(i * 66.0f + 26.0f, 16.0f);
			cells->InitCells(candle);
		}

		for (int i = 0; i < 7; i++)
		{
			hidenObj = new CHidenObject();
			hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
			hidenObj->SetPosition(i * 32.0f, 82.0f);
			hidenObj->SetSize(32.0f, 15.0f);
			cells->InitCells(hidenObj);
		}

		for (int i = 0; i < 5; i++)
		{
			hidenObj = new CHidenObject();
			hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
			hidenObj->SetPosition(i * 32.0f + 320.0f, 82.0f);
			hidenObj->SetSize(32.0f, 15.0f);
			cells->InitCells(hidenObj);
		}

		for (int i = 0; i < 7; i++)
		{
			hidenObj = new CHidenObject();
			hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
			hidenObj->SetPosition(504.0f, i * 16.0f);
			hidenObj->SetSize(8.0f, 16.0f);
			cells->InitCells(hidenObj);
		}

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(97.0f, 50.0f);
		hidenObj->SetSize(32.0f, 15.0f);
		cells->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(257.0f, 82.0f);
		hidenObj->SetSize(32.0f, 15.0f);
		cells->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(481.0f, 114.0f);
		hidenObj->SetSize(32.0f, 15.0f);
		cells->InitCells(hidenObj);

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(449.0f, 146.0f);
		hidenObj->SetSize(32.0f, 15.0f);
		cells->InitCells(hidenObj);

		break;
	}
}

void CEntranceLevel::Update()
{
	if (prev_scene != scene)
	{
		LoadMap();
		prev_scene = scene;
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
	else if(scene == SCENE_2)
	{
		min = MIN_MAP_2;
		max = MAX_MAP_2;
	}
	else if (scene == SCENE_3)
	{
		min = MIN_MAP_3;
		max = MAX_MAP_3;
	}
}

CEntranceLevel * CEntranceLevel::GetInstance()
{
	if (__instance == NULL) __instance = new CEntranceLevel();
	return __instance;
}
