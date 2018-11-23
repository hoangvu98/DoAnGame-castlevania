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
using namespace std;
#define LEVEL_1_STAGE1A_PATH L"castlevania_texture\\Background\\tileset_map1_stage1A.png"/*Level 1 Entrance.png"*/
#define LEVEL_1_STAGE1B_PATH L"castlevania_texture\\Background\\tileset_map1_stage1B.png"
#define STAGE_1A_MAP_DATA "Data\\TileMap1Stage1A.txt"
#define STAGE_1B_MAP_DATA "Data\\TileMap1Stage1B.txt"

#define SCENE_1		1
#define SCENE_2		2
#define SCENE_3		3
#define SCENE_4		4

#define ID_MAP_LEVEL_1	0
class CEntranceLevel :
	public CMap
{
	static CEntranceLevel *__instance;
public:
	void LoadMap();
	void Update();
	void Render();

	static CEntranceLevel * GetInstance();
};

