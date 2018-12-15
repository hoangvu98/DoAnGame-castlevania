#pragma once
#include <fstream>
#include "Map.h"
#include "Textures.h"
#include "Candle.h"
#include "InputImage.h"
#include "HidenObject.h"
#include "TileMap.h"
#include "Door.h"
#include "Simon.h"
#include "Panther.h"
#include "debug.h"
#include "Ghoul.h"
#include "Brick.h"
#include "Bat.h"
#include "Fishman.h"
#include "BossBat.h"

using namespace std;
#define LEVEL_1_STAGE1A_PATH L"castlevania_texture\\Background\\tileset_map1_stage1A.png"/*Level 1 Entrance.png"*/
#define LEVEL_1_STAGE1B_PATH L"castlevania_texture\\Background\\tileset_map1_stage1B.png"
#define LEVEL_1_STAGE2B_PATH L"castlevania_texture\\Background\\tileset_map1_stage2B.png"

#define STAGE_1A_MAP_DATA "Data\\TileMap1Stage1A.txt"
#define STAGE_1B_MAP_DATA "Data\\TileMap1Stage1B.txt"
#define STAGE_2B_MAP_DATA "Data\\TileMap1Stage2B.txt"

#define SCENE_0		0
#define SCENE_1		1
#define SCENE_2		2
#define SCENE_3		3
#define SCENE_4		4
#define SCENE_5		5

#define ID_MAP_LEVEL_1	0

#define MIN_MAP_1 0
#define MAX_MAP_1 769
#define MIN_MAP_2 0
#define MAX_MAP_2 1555
#define MIN_MAP_3 1535
#define MAX_MAP_3 2062
#define MIN_MAP_4 0
#define MAX_MAP_4 512 
#define MIN_MAP_5 2042.0f
#define MAX_MAP_5 2832.0f
class CEntranceLevel :
	public CMap
{
	static CEntranceLevel *__instance;
public:
	void LoadMap();
	void Update();
	void Render();
	void GetSizeMap(float &min,float &max);
	static CEntranceLevel * GetInstance();
	void NextScece(float &x, float &y);
};

