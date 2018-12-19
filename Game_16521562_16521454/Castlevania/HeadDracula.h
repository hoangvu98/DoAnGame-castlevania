#pragma once
#include "Monster.h"
#include "GameObject.h"
#define HEAD_SPEED_X		0.15f
#define HEAD_SPEED_Y		0.1f

#define HEAD_STATE_FLY			0
#define HEAD_STATE_IDLE			300
#define HEAD_STATE_INVISIBLE	400
#define HEAD_STATE_FLY_AWAY		500

#define HEAD_ANI_LEFT		0
#define HEAD_ANI_RIGHT		1

#define HEAD_BBOX_WIDTH		8
#define HEAD_BBOX_HEIGHT	14

#define HEAD_FLY_HEIGHT		88

#define HEAD_OFFSET_X	8
#define HEAD_OFFSET_Y	10

#define HEAD_OFFSET_X1	11
class CHeadDracula :
	public CGameObject
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void SetState(int state);
	CHeadDracula();
	~CHeadDracula();
};

