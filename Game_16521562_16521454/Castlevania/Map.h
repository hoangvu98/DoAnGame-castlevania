#pragma once
#include "GameObject.h"
#include "Textures.h"
#include "Sprites.h"
#include "Cell.h"
#include "Game.h"
#include "TileMap.h"
#include <vector>
using namespace std;


class CMap
{
protected:
	int prev_scene, scene;

	CCells *cells;

	CTextures *textures;
	CSprites *sprites;
	CAnimations *animations;
	
	CTileMap *tilemap;
public:
	CMap();
	~CMap();

	//void GetSence(int &prev_scene, int &scene) { prev_scene = this->prev_scene; scene = this->scene; }
	void SetScene(int scene) { this->scene = scene; }
	
	vector<LPGAMEOBJECT> GetUpdateObjects();
	void GetSizeOfMap(float &width, float &height);
	virtual void LoadMap();
	virtual void Update() = 0;
	virtual void Render();
};

