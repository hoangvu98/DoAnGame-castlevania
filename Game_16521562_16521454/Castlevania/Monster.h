#pragma once
#include "GameObject.h"
#include "Items.h"
#include <vector>
using namespace std;
#define MONSTER_STATE_DISAPPEAR 100
#define MONSTER_STATE_DELETE    200
#define MONSTER_STATE_SLEEPING  1000
#define FrameTime 200
#define TIME_INJURE 1000
class CMonster : public CGameObject
{
protected:
	CItems *items;
	int health;
	int score;
	int damage;
	bool IsInjure = true;
	DWORD time_injure;
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
	void SetIsInjure(int IsInjure) { this->IsInjure = IsInjure; }
	int GetIsInjure() { return IsInjure; }
	void SetTimeInjure() { time_injure = GetTickCount(); }
	CMonster();
};
