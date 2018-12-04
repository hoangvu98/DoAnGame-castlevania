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

	long score;
	DWORD time;
	int stage;
	int heart;
	int life;
public:
	CBlackBoard();
	void SetScore(long score) { this->score = score; }
	long GetScore() { return this->score; }

	void SetTime(DWORD time) { this->time = time; }
	DWORD GetTime() { return this->time; }

	void SetStage(int stage) { this->stage = stage; }
	int GetStage() { return this->stage; }

	void SetHeart(int heart) { this->heart = heart; }
	int GetHeart() { return this->heart; }

	void SetLife(int life) { this->life = life; }
	int GetLife() { return this->life; }

	void Render();
};

