#pragma once
#include "Map.h"
#include "Skeleton.h"
#define LEVEL6_STAGE16_PATH L"castlevania_texture\\Background\\tileset_map6_stage16.png"
#define LEVEL6_STAGE17A_PATH L"castlevania_texture\\Background\\tileset_map6_stage_17A.png"
#define LEVEL6_STAGE17B_PATH L"castlevania_texture\\Background\\tileset_map6_stage17B.png"
#define LEVEL6_STAGE18A_PATH L"castlevania_texture\\Background\\tileset_map6_stage18A.png"
#define LEVEL6_STAGE18B_PATH L"castlevania_texture\\Background\\tileset_map6_stage18B.png"

#define STAGE_16_MAP_DATA "Data\\TileMap6Stage16.txt"
#define STAGE_17A_MAP_DATA "Data\\TileMap6Stage17A.txt"
#define STAGE_17B_MAP_DATA "Data\\TileMap6Stage17B.txt"
#define STAGE_18A_MAP_DATA "Data\\TileMap6Stage18A.txt"
#define STAGE_18B_MAP_DATA "Data\\TileMap6Stage18B.txt"

//#define ID_MAP_LEVEL_6	20

#define SCENE_1		1
#define SCENE_2		2
#define SCENE_3		3
#define SCENE_4		4
#define SCENE_5		5

#define MIN_MAP_1 0
#define MAX_MAP_1 1550
#define MIN_MAP_2 0
#define MAX_MAP_2 783
#define MIN_MAP_3 0
#define MAX_MAP_3 781
#define MIN_MAP_4 0
#define MAX_MAP_4 294 
#define MIN_MAP_5 0
#define MAX_MAP_5 751

class CClockTowerLevel :
	public CMap
{
	static CClockTowerLevel * __instance;
public:
	CClockTowerLevel();
	void LoadMap();
	void Update();
	void Render();
	~CClockTowerLevel();
	static CClockTowerLevel *GetInstance();
	void GetSizeMap(float &min, float &max);
	void NextScece(float &x, float &y);
};

