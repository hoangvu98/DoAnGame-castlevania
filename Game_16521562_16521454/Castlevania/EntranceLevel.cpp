#include "EntranceLevel.h"

CEntranceLevel *CEntranceLevel::__instance = NULL;

void CEntranceLevel::LoadMap()
{
	ifstream in;
	LPDIRECT3DTEXTURE9 texture_map;
	LPANIMATION ani = new CAnimation(100);
	LPDIRECT3DTEXTURE9 texture_candle = textures->Get(ID_CANDLE);
	CCandle *candle;
	CDoor *door;
	switch (scene)
	{
	case SCENE_1:
		textures->Add(ID_MAP_LEVEL_1, LEVEL_1_STAGE1A_PATH, D3DCOLOR_XRGB(255, 255, 255));
		texture_map = textures->Get(ID_MAP_LEVEL_1);
		textures->Add(ID_CANDLE, CANDLE_TEXTURE_PATH, D3DCOLOR_XRGB(34, 177, 76));
		tilemap->LoadTileMap(STAGE_1A_MAP_DATA, texture_map);
		
		int column, row;

		float width, height;
		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cells = new CCells(row, column);

		
		in.open("Data\\Candle.txt");

		CInputImage::AddAnimation(in, sprites, ani, texture_candle, 2);
		animations->Add(100, ani);
		in.close();

		candle = new CCandle(DAGGER);
		candle->AddAnimation(100);
		candle->SetPosition(85.0f, 111.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle, 2, 1);

		candle = new CCandle(HEART_SMALL);
		candle->AddAnimation(100);
		candle->SetPosition(222.0f, 111.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle, 2, 3);

		candle = new CCandle();
		candle->AddAnimation(100);
		candle->SetPosition(343.0f, 111.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle, 2, 5);

		candle = new CCandle();
		candle->AddAnimation(100);
		candle->SetPosition(475.0f, 111.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle, 2, 7);

		candle = new CCandle(DAGGER);
		candle->AddAnimation(100);
		candle->SetPosition(600.0f, 111.0f);
		candle->SetState(CANDLE_STATE_NORMAL);
		cells->InitCells(candle, 2, 9);

		for (int i = 0; i < 13; i++)
		{
			CHidenObject *hidenObj = new CHidenObject();
			hidenObj->SetSize(64.0f, 15.0f);
			hidenObj->SetPosition(i * 64.0f, 145.0f);
			cells->InitCells(hidenObj, 2, i);
		}

		door = new CDoor();
		door->SetPosition(672.0f, 105.0f);
		cells->InitCells(door, 2, 11);

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

		cells = new CCells(row, column);

		for (int i = 0; i < 25; i++)
		{
			CHidenObject *hidenObj = new CHidenObject();
			hidenObj->SetSize(64.0f, 15.0f);
			hidenObj->SetPosition(i * 64.0f, 160.0f);
			cells->InitCells(hidenObj, 2, i);
		}
		CHidenObject *hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_STAIR);
		hidenObj->SetSize(20.0f, 20.0f);
		hidenObj->SetPosition(607.0f, 140.0f);
		cells->InitCells(hidenObj, 2, 9);
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
