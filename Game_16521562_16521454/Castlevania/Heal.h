#pragma once
#include "Textures.h"
#include "Sprites.h"

#define HEAL_TEXTURE_PATH	L"castlevania_texture\\Weapon\\heal.png"	
#define ID_HEAL			18

#define PLAYER_ANI_HEAL	0
#define EMPTY_ANI		1
#define ENEMY_ANI_HEAL	2

#define PLAYER	100
#define ENEMY	200
#define EMPTY   300

class CHeal
{
	int type;

	LPDIRECT3DTEXTURE9 texheal;

public:
	CHeal(int type);
	void SetType(int type) { this->type = type; }
	void Render(float x, float y);
};

