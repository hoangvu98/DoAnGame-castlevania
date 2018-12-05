#pragma once
#include "GameObject.h"
#include "Simon.h"
#include "HidenObject.h"
#include "Monster.h"
#define PANTHER_TEXTURE_PATH L"castlevania_texture\\Enemy\\Panther.png"
#define ID_PANTHER 9

#define PANTHER_WALKING_SPEED 0.3f

#define PANTHER_JUMP_SPEED_X  0.2f
#define PANTHER_JUMP_SPEED_Y  0.02f
#define PANTHER_GRAVITY       0.002f

#define PANTHER_BBOX_WIDTH 24
#define PANTHER_BBOX_HEIGHT 16

#define PANTHER_STATE_IDLE          0     
#define PANTHER_STATE_WALKING_RIGHT 100
#define PANTHER_STATE_WALKING_LEFT  200
#define PANTHER_STATE_JUMP_RIGHT    300
#define PANTHER_STATE_JUMP_LEFT     400
#define PANTHER_STATE_DIE			500
#define PANTHER_STATE_DELETE		600

#define PANTHER_ANI_IDLE_RIGHT    0
#define PANTHER_ANI_IDLE_LEFT     1
#define PANTHER_ANI_WALKING_RIGHT 2
#define PANTHER_ANI_WALKING_LEFT  3
#define PANTHER_ANI_JUMP_RIGHT    4
#define PANTHER_ANI_JUMP_LEFT     5

#define MOVING_AREA_WIDTH		50
#define MOVING_AREA_HEIGHT		100
#define DISTANCE				67
class CPanther : public CMonster
{
	float left, top, right, bottom;

	float temp_x, temp_y;

	bool jump;

	bool run;

	bool reset;

	int turn; //0- left, 1- right
public:
	void InitMovingArea();
	CPanther();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Reset();
	virtual void Render();
	void SetState(int state);
	void SetJump(bool jump) { this->jump = jump; }
	void SetTurn(int turn) { this->turn = turn; }
	void SetTmpPosition(float tmp_x, float tmp_y) { this->temp_x = tmp_x; this->temp_y = tmp_y; }

	void GetMovingArea(float &left, float &top, float &right, float &bottom);
};