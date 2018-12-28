#include "EntranceLevel.h"
#include "Resource.h"
CEntranceLevel *CEntranceLevel::__instance = NULL;

void CEntranceLevel::LoadMap()
{
	float c_x, c_y;
	CCandle *candle;
	CPanther *panther;
	CGhoul *ghoul;
	CSimon *simon = CSimon::GetInstance();
	CBrick *brick;
	CBat *bat;
	CFishman *fishman;
	CBossBat* bossbat;
	ifstream in;
	LPGAMEOBJECT object;
	int i;
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
		
		in.open("Data\\EntranceLevel_Scene1.txt");
		for (i = 0; i < 8; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cells->InitCells(object);
		}
		in.close();
		break;
	case SCENE_2:

		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cells = new CCells(column, row);

		in.open("Data\\EntranceLevel_Scene2.txt");
		for (i = 0; i < 24; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cells->InitCells(object);
		}

		for (i = 0; i < 14; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cells->InitCells(object);
		}

		for (i = 0; i < 8; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cells->InitCells(object);
		}

		for (i = 0; i < 3; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cells->InitCells(object);
		}

		for (i = 0; i < 3; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cells->InitCells(object);
		}
		in.close();
		
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

		in.open("Data\\EntranceLevel_Scene3.txt");
		for (i = 0; i < 8; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cells->InitCells(object);
		}
		DebugOut(L"ok\n");
		for (i = 0; i < 15; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cells->InitCells(object);
		}
		DebugOut(L"ok\n");
		for (i = 0; i < 6; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cells->InitCells(object);
		}
		DebugOut(L"ok\n");
		for (i = 0; i < 4; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cells->InitCells(object);
		}
		DebugOut(L"ok\n");
		in.close();
		

		break;

	case SCENE_4:

		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cells = new CCells(column, row);

		in.open("Data\\EntranceLevel_Scene4.txt");
		for (i = 0; i < 8; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cells->InitCells(object);
		}

		for (i = 0; i < 7; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cells->InitCells(object);
		}

		for (i = 0; i < 2; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cells->InitCells(object);
		}

		for (i = 0; i < 5; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cells->InitCells(object);
		}

		in.close();

		break;
	case SCENE_5:
		simon->SetStage(3);
		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cells = new CCells(column, row);

		in.open("Data\\EntranceLevel_Scene5.txt");

		for (i = 0; i < 12; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cells->InitCells(object);
		}

		for (i = 0; i < 5; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cells->InitCells(object);
		}

		for (i = 0; i < 6; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cells->InitCells(object);
		}

		for (i = 0; i < 2; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			CGhoul *ghoul = (CGhoul *)object;
			ghoul->SetLimitArea(2050, 2352);
			cells->InitCells(ghoul);
		}

		CInputImage::LoadObjectFromFile(in, object);
		cells->InitCells(object);

		in.close();
		break;
	}
}

void CEntranceLevel::LoadObject()
{
	LPDIRECT3DTEXTURE9 texture_map;
	CHidenObject *hidenObj;
	CDoor *door;
	CSimon *simon = CSimon::GetInstance();
	int i;
	ifstream in;
	LPGAMEOBJECT object;
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
		
		/*in.open("Data\\door_scene1_Etrance.txt");
		CInputImage::LoadDoorFromFile(in, door);*/

		door = new CDoor();
		door->SetPosition(672.0f, 105.0f);
		door->size = 30;
		door->SetIsHiDen(true);
		door->SetScene(2);
		cellsobject->InitCells(door);

		in.close();
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

		/*in.open("Data\\door_scene2_Etrance.txt");
		CInputImage::LoadDoorFromFile(in, door);
		door->SetState(DOOR_STATE_NORMAL);*/
		door = new CDoor();
		door->SetState(DOOR_STATE_NORMAL);
		door->SetPosition(1530.0f, 15.0f);
		door->SetIsHiDen(false);
		door->SetScene(3);
		cellsobject->InitCells(door);
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
		in.open("Data\\door_scene3_Etrance.txt");
		//CInputImage::LoadDoorFromFile(in, door);

	/*	for (i = 0; i < 2; i++)
		{
			CInputImage::LoadDoorFromFile(in, door);
			door->IsGo = true;
			door->SetIsStair(true);
			cellsobject->InitCells(door);
		}
		CInputImage::LoadDoorFromFile(in, door);
		door->IsGo = true;
		cellsobject->InitCells(door);*/
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
		/*in.open("Data\\door_scene4_Etrance.txt");
		for (i = 0; i < 2; i++)
		{
			CInputImage::LoadDoorFromFile(in, door);
			door->IsGo = true;
			door->SetIsStair(true);
			cellsobject->InitCells(door);

		}*/
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
		x = 2062.1;
		y = 34.6;
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
		scene = SCENE_4;
	}
	else if (scene == SCENE_5)
	{
		scene == SCENE_5;
	}
}
