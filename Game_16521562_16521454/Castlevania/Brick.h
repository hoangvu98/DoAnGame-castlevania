#pragma once
#include "GameObject.h"
#include "BreakingWall.h"

#define BRICK_BBOX_WIDTH	17
#define BRICK_BBOX_HEIGHT	32

#define BRICK_STATE_FULL	0
#define BRICK_STATE_HALF	100
#define BRICK_STATE_DELETE	200

#define BRICK_ANI_FULL		0
#define BRICK_ANI_HALF		1

class CBrick :public CGameObject
{
	int del;
	bool render;
	int loop;
	CBreakingWall *breakingwall;
public:
	CBrick(float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void GetBoundingBox(float & left, float & top, float & right, float & bottom);
	void SetDel(int del) { this->del = del; }
	CBreakingWall GetBreakWall(int i) { return breakingwall[i]; }
	int GetDel() { return del; }
};