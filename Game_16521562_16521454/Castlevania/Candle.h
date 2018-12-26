#pragma once
#include <cstdlib>
#include <time.h>
#include "GameObject.h"
#include "Items.h"
#define DAGGER		0
#define HEART		1
#define WHIP_UPDATE	2
#define MONEY_BAG   3
#define AXE         4
#define BOOMERANG	5
#define HOLLYWATER	6
#define INVINCIBILITY_POTION	7

#define BIG_CANDLE		100
#define SMALL_CANDLE	200

#define CANDLE_STATE_DELETE     20
#define CANDLE_STATE_NORMAL 0
#define CANDLE_STATE_DISAPPEAR	10

#define BIG_CANDLE_BBOX_WIDTH	18
#define BIG_CANDLE_BBOX_HEIGHT	34

#define SMALL_CANDLE_BBOX_WIDTH	8
#define SMALL_CANDLE_BBOX_HEIGHT 14

#define FrameTime 200

class CCandle :
	public CGameObject
{
	int size;
	CItems *items;
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject);
	void Render();
	void GetBoundingBox(float & left, float & top, float &right, float & bottom);
	void SetState(int state);
	CItems *GetItems() { return items; }
	CCandle(int size);
	CCandle(int size, int item);
};

