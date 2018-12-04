#pragma once

#include <d3dx9.h>
#include "GameObject.h"
#include "TileMap.h"
#include "Textures.h"
#include <vector>
using namespace std;

#define BLACKBOARD_TEXTURE_PATH L"castlevania_texture\\Background\\blackboard.png"

#define ID_BLACKBOARD 14

#define TILE_BLACKBOARD_WIDTH	16
#define TILE_BLACKBOARD_HEIGHT	16

#define ID_HEARTBLACKBOARD		15
#define ID_RECTANGLE			16

class CBlackBoard
{
	LPDIRECT3DTEXTURE9 texblackboard;

	vector<CSprite> *simonHP;
	vector<CSprite> *enemyHP;

public:
	CBlackBoard();
	void Render();
};

