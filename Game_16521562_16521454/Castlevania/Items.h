#pragma once
#include "GameObject.h"
#include "Textures.h"
#include "Sprites.h"


#define ITEM_GRAVITY	0.01f

#define ITEM_STATE_ITEM 0
#define ITEM_STATE_WEAPON_RIGHT 1
#define ITEM_STATE_WEAPON_LEFT 2
#define ITEM_STATE_DELETE 3
class CItems :
	public CGameObject
{
public:
	CItems();
	~CItems();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
};

#define DAGGER_BBOX_WIDTH	19
#define DAGGER_BBOX_HEIGHT	10
#define SPEED_DAGGER 0.15f
class CDagger : public CItems
{
	int damage=2;
public:
	CDagger() :CItems() {AddAnimation(6000); AddAnimation(6001); }
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void SetState(int state);
};

#define HEART_BIG		0
#define HEART_SMALL		1

#define HEART_BBOX_BIG_WIDTH	12
#define HEART_BBOX_BIG_HEIGHT	11

#define HEART_BBOX_SMALL_WIDTH	8
#define HEART_BBOX_SMALL_HEIGHT	9

class CHeart:public CItems
{
	int hearts;
	int size;
public:
	CHeart() :CItems() { size = HEART_SMALL; AddAnimation(7000); AddAnimation(8000); }

	CHeart(int size) :CItems()
	{
		this->size = size;
		switch (size)
		{
		case HEART_BIG:
			hearts = 1;
			break;
		case HEART_SMALL:
			hearts = 2;
			break;
		}
		AddAnimation(7000);
		AddAnimation(8000);
	}

	void SetHearts(int hearts) { this->hearts = hearts; }
	int GetHearts() { return hearts; }

	void SetSize(int size) { this->size = size; }
	int GetSize() { return size; }

	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);

};

#define WHIP_UPDATE_BBOX_WIDTH 18
#define WHIP_UPDATE_BBOX_HEIGHT 16


class CWhipUpdate : public CItems
{
public:
	CWhipUpdate() :CItems() { AddAnimation(9000); }
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

#define MONEY_BAG_BBOX_WIDTH 13
#define MONEY_BAG_BBOX_HEIGHT 14
#define MONEY_BAG_SMALL 0
#define MONEY_BAG_BIG 1

#define MONEY_BAG_RED   0
#define MONEY_BAG_BLUE  1
#define MONEY_BAG_WHITE 2

class CMoneyBag : public CItems
{
	int size;
public:
	CMoneyBag(int size, int state);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

#define AXE_BBOX_WIDTH 15
#define AXE_BBOX_HEIGHT 14

#define SPEED_AXE_X 0.15f
#define SPEED_AXE_Y 0.3f
#define AXE_GRAVITY	0.001f
class CAxe : public CItems
{
	int damage=2;
public:
	CAxe() :CItems() { AddAnimation(14001); AddAnimation(14002); }
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void SetState(int state);
};