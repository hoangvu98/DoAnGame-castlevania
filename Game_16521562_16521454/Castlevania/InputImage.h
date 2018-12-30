#pragma once
#include "Textures.h"
#include "Sprites.h"
#include "GameObject.h"
#include <fstream>
#include "Door.h"

#define CANDLE		1 //roi
#define HIDENOBJECT 2
#define PANTHER		3 //roi
#define GHOUL		4 //roi
#define BAT			5
#define FISHMAN		6 //roi
#define SKELETON	7
#define EAGLE		8
#define HUNCHBACK	9
#define BOSSBAT		10 //roi
#define DRACULA		11
#define BRICK		12
class CInputImage
{
public:
	static void LoadDataFromFile(ifstream &in,
		int &id,
		int &left, int &top,
		int &right, int &bottom);
	static void AddAnimation(ifstream &in, CSprites *sprites,
		LPANIMATION &ani, LPDIRECT3DTEXTURE9 texture,
		int n,int time=100);

	static void LoadObjectFromFile(ifstream &in, LPGAMEOBJECT &object);
	static void LoadDoorFromFile(ifstream &in, CDoor *&door);
};

