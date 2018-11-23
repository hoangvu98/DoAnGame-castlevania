#pragma once
#include <cstdlib>
#include <time.h>
#include "GameObject.h"
#include "Items.h"
#define DAGGER		0
#define HEART		1
#define WHIP_UPDATE	2

#define BIG_CANDLE		100
#define SMALL_CANDLE	200

#define CANDLE_STATE_DELETE     20
#define CANDLE_STATE_NORMAL 0
#define CANDLE_STATE_DISAPPEAR	10
#define CANDLE_BBOX_WIDTH	18
#define CANDLE_BBOX_HEIGHT	34
#define FrameTime 200

class CCandle :
	public CGameObject
{
	int size;
	Chiteffect *hiteffect;
	CItems *items;
	int Time;
public:
	void Render();
	void GetBoundingBox(float & left, float & top, float &right, float & bottom);
	void SetState(int state);
	CItems *GetItems() { return items; }
	CCandle(int size);
	CCandle(int size, int item);
};

