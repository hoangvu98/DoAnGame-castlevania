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
	CCells *cellsobject;

	CTextures *textures;
	CSprites *sprites;
	CAnimations *animations;
	
	CTileMap *tilemap;
	bool IsNext=false;
	int NextScene;
public:
	CMap();
	~CMap();

	//void GetSence(int &prev_scene, int &scene) { prev_scene = this->prev_scene; scene = this->scene; }
	void SetScene(int scene) { this->scene = scene; }
	int GetScene() { return scene; }
	void SetIsNext(bool IsNext) { this->IsNext = IsNext; };
	bool GetIsNext() {return IsNext;}
	void SetNextScene(int NextScene) { this->NextScene = NextScene; }
	int GetNextScene() { return NextScene; }
	void GetUpdateObjects(vector<LPGAMEOBJECT>* object);
	void ChangeCellOfObject(float cam_x, float cam_y);
	void GetSizeOfMap(float &width, float &height);
	virtual void LoadMap();
	virtual void LoadObject() = 0;
	virtual void Update() = 0;
	virtual void Render();
	virtual void GetSizeMap(float &min, float &max)=0;
	virtual void NextScece(float &x, float &y) = 0;
	virtual void ResetScene() = 0;
	CCells* GetCell() { return cells; }
	void SetCell(CCells *cells) {this->cells= cells;}
	CTileMap* GetTileMap() { return tilemap; }
	void SetPrevScene(int prev_scene) { this->prev_scene = prev_scene; }
};
