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
	bool IsNext=false;
	bool IsFall = false;
	int NextScene;
public:
	CMap();
	~CMap();

	//void GetSence(int &prev_scene, int &scene) { prev_scene = this->prev_scene; scene = this->scene; }
	void SetScene(int scene) { this->scene = scene; }
	int GetScene() { return scene; }
	void SetIsNext(bool IsNext) { this->IsNext = IsNext; };
	void SetIsFall(bool IsFall) { this->IsFall = IsFall; };
	bool GetIsNext() {return IsNext;}
	bool GetIsFall() { return IsFall; }
	void SetNextScene(int NextScene) { this->NextScene = NextScene; }
	int GetNextScene() { return NextScene; }
	void GetUpdateObjects(vector<LPGAMEOBJECT>* object);
	void GetSizeOfMap(float &width, float &height);
	virtual void LoadMap();
	virtual void Update() = 0;
	virtual void Render();
	virtual void GetSizeMap(float &min, float &max)=0;
	virtual void NextScece(float &x, float &y) = 0;
};

