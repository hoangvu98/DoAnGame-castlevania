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
	
	CCandle *candle;
	CDoor *door;
	CPanther *panther;
	CGhoul *ghoul;
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

		candle = new CCandle(DAGGER);
		candle->SetPosition(85.0f, 111.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle, 1, 2);

		candle = new CCandle(HEART_SMALL);
		candle->SetPosition(222.0f, 111.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle, 3, 2);

		candle = new CCandle();
		candle->SetPosition(343.0f, 111.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle, 5, 2);

		candle = new CCandle();
		candle->SetPosition(475.0f, 111.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle, 7, 2);

		candle = new CCandle(DAGGER);
		candle->SetPosition(600.0f, 111.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle, 9 ,2);

		for (int i = 0; i < 13; i++)
		{
			CHidenObject *hidenObj = new CHidenObject();
			hidenObj->SetSize(64.0f, 15.0f);
			hidenObj->SetPosition(i * 64.0f, 145.0f);
			cells->InitCells(hidenObj, i, 2);
		}

		door = new CDoor();
		door->SetPosition(672.0f, 105.0f);
		cells->InitCells(door, 11, 2);

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
			CHidenObject *hidenObj = new CHidenObject();
			hidenObj->SetSize(64.0f, 15.0f);
			hidenObj->SetPosition(i * 64.0f, 160.0f);
			cells->InitCells(hidenObj, i, 2);
		}
		CHidenObject *hidenObj = new CHidenObject();
		/*hidenObj->SetState(HIDENOBJECT_STATE_STAIR_UP);
		hidenObj->SetSize(40.0f, 12.0f);
		hidenObj->SetPosition(607.0f, 148.0f);
		cells->InitCells(hidenObj, 2, 9);
*/
		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetSize(55.0f, 17.0f);
		hidenObj->SetPosition(681.0f, 97.0f);
		cells->InitCells(hidenObj, 10, 1);

		/*hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR_DOWN);
		hidenObj->SetSize(30.0f, 17.0f);
		hidenObj->SetPosition(681.0f, 81.0f);
		cells->InitCells(hidenObj, 1, 10);*/

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_JUMP);
		hidenObj->SetPosition(681.0f, 84.0f);
		hidenObj->SetSize(5.0f, 14.0f);
		cells->InitCells(hidenObj, 10, 1);

		

		panther = new CPanther();
		
		CSimon *simon = CSimon::GetInstance();

		panther->SetState(PANTHER_STATE_IDLE);
		panther->Setnx(-simon->Getnx());
		panther->SetTurn(0);
		panther->SetPosition(690.0f, 80.0f);
		panther->SetJump(false);
		panther->InitMovingArea();
		cells->InitCells(panther, 10, 1);

		ghoul = new CGhoul();
		ghoul->SetPosition(250.0f, 127.0f);
		ghoul->SetState(GHOUL_STATE_RIGHT);
		cells->InitCells(ghoul, 3, 2);
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
	switch(scene)
	{
	case SCENE_1:
		tilemap->Render(0.0f, 0.0f);
		break;
	case SCENE_2:
		tilemap->Render(0.0f, 0.0f);
		break;
	}
	//tilemap->Render(0.0f, 0.0f);
}

CEntranceLevel * CEntranceLevel::GetInstance()
{
	if (__instance == NULL) __instance = new CEntranceLevel();
	return __instance;
}
