#include "EntranceLevel.h"
#include "Resource.h"
CEntranceLevel *CEntranceLevel::__instance = NULL;

void CEntranceLevel::LoadMap()
{
	CSimon *simon = CSimon::GetInstance();
	int i;
	ifstream in;
	LPGAMEOBJECT object;
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
		for (i = 0; i < 5; i++)
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
		for (i = 0; i < 30; i++)
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

		in.open("Data\\EntranceLevel_Scene3.txt");
		for (i = 0; i < 9; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cells->InitCells(object);
		}

		for (i = 0; i < 2; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			CBat *bat = (CBat *)object;
			bat->SetStateAppear(BAT_STATE_FLY_LEFT);
			cells->InitCells(bat);
		}

		for (i = 0; i < 3; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			CBat *bat = (CBat *)object;
			bat->SetStateAppear(BAT_STATE_FLY_RIGHT);
			cells->InitCells(bat);
		}
		in.close();

		break;

	case SCENE_4:

		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cells = new CCells(column, row);

		in.open("Data\\EntranceLevel_Scene4.txt");
		for (i = 0; i < 22; i++)
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
		for (i = 0; i < 15; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cells->InitCells(object);
		}

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

	ifstream in;
	LPGAMEOBJECT object;
	int i;

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

		in.open("Data\\hobj_EL_Scene1.txt");

		for (i = 0; i < 3; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cellsobject->InitCells(object);
		}
		in.close();

		in.open("Data\\door_scene1_Etrance.txt");
		CInputImage::LoadDoorFromFile(in, door);
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

		in.open("Data\\hobj_EL_Scene2.txt");

		for (i = 0; i < 22; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cellsobject->InitCells(object);
		}
		in.close();

		in.open("Data\\door_scene2_Etrance.txt");
		CInputImage::LoadDoorFromFile(in, door);
		cellsobject->InitCells(door);
		in.close();

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

		in.open("Data\\hobj_EL_Scene3.txt");

		for (i = 0; i < 21; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cellsobject->InitCells(object);
		}
		in.close();

		in.open("Data\\door_scene3_Etrance.txt");
		for (i = 0; i < 2; i++)
		{
			CInputImage::LoadDoorFromFile(in, door);
			door->IsGo = true;
			door->SetIsStair(true);
			cellsobject->InitCells(door);
		}

		CInputImage::LoadDoorFromFile(in, door);
		door->IsGo = true;
		cellsobject->InitCells(door);

		in.close();

		break;
	case SCENE_4:

		textures->Add(ID_MAP_LEVEL_1, LEVEL_1_STAGE2B_PATH, D3DCOLOR_XRGB(255, 255, 255));
		texture_map = textures->Get(ID_MAP_LEVEL_1);

		tilemap->LoadTileMap(STAGE_2B_MAP_DATA, texture_map);

		tilemap->GetSize(width, height);

		column = (int)width / CELL_WIDTH + 1;
		row = (int)height / CELL_HEIGHT + 1;

		cellsobject = new CCells(column, row);

		in.open("Data\\hobj_EL_Scene4.txt");

		for (i = 0; i < 9; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cellsobject->InitCells(object);
		}

		in.close();

		in.open("Data\\door_scene4_Etrance.txt");
		for (i = 0; i < 2; i++)
		{
			CInputImage::LoadDoorFromFile(in, door);
			door->IsGo = true;
			door->SetIsStair(true);
			cellsobject->InitCells(door);
		}
		in.close();

		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(0.0f, 83.0f);
		hidenObj->SetSize(224.0f, 15.0f);
		cellsobject->InitCells(hidenObj);
		
		hidenObj = new CHidenObject();
		hidenObj->SetState(HIDENOBJECT_STATE_NORMAL);
		hidenObj->SetPosition(320.0f, 83.0f);
		hidenObj->SetSize(161.0f, 14.0f);
		cellsobject->InitCells(hidenObj);

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

		in.open("Data\\hobj_EL_Scene5.txt");

		for (i = 0; i < 13; i++)
		{
			CInputImage::LoadObjectFromFile(in, object);
			cellsobject->InitCells(object);
		}

		in.close();
	
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
		scene = SCENE_5;
	}
}
