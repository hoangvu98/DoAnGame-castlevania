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
	bool IsNextScene=false;
	bool IsFallScene = false;
public:
	CMap();
	~CMap();

	//void GetSence(int &prev_scene, int &scene) { prev_scene = this->prev_scene; scene = this->scene; }
	void SetScene(int scene) { this->scene = scene; }
	int GetScene() { return scene; }
	void SetNextScene(bool IsNextScene) { this->IsNextScene = IsNextScene; };
	void SetFallScene(bool IsFallScene) { this->IsFallScene = IsFallScene; };
	bool IsNext() {return IsNextScene;}
	bool IsFall() { return IsFallScene; }
	void NextScece(float &x,float &y);
	vector<LPGAMEOBJECT> GetUpdateObjects();
	void GetSizeOfMap(float &width, float &height);
	virtual void LoadMap();
	virtual void Update() = 0;
	virtual void Render();
};

