#pragma once
#include "GameObject.h"
#include "Items.h"
#include <vector>
using namespace std;
#define MONSTER_STATE_DISAPPEAR 100
#define MONSTER_STATE_DELETE    200

#define FrameTime 200
class CMonster : public CGameObject
{
protected:
	Chiteffect *hiteffect;
	CItems *items;
	int health;
	int score;
	int damage;
	DWORD Time_HitEffect;
public:
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual void SetState(int state);
	CItems *GetItems() { return items; }
	void SetHealth(int health) { this->health = health; }
	int GetHealth() { return health; }
	int GetScore() { return score; }
	int GetDamage() { return damage; }
	CMonster();
};
