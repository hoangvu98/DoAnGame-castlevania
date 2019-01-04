#pragma once
#include "Monster.h"
#include "Bone.h"
#define SKELETON_WALKING_SPEED	0.075f
#define SKELETON_GRAVITY		0.01f
#define SKELETON_JUMP_SPEED_X  0.08f
#define SKELETON_JUMP_SPEED_Y  0.22f

#define SKELETON_STATE_WALKING_LEFT		0
#define SKELETON_STATE_WALKING_RIGHT	300
#define SKELETON_STATE_THROW_BONE		400
#define SKELETON_STATE_JUMP_LEFT		500
#define SKELETON_STATE_JUMP_RIGHT		600
#define SKELETON_STATE_JUMP				700

#define SKELETON_ANI_WALKING_LEFT		0
#define SKELETON_ANI_WALKING_RIGHT		1

#define SKELETON_DISTANCE		50
#define DISTANCE_WITH_SIMON		70
#define DISTANCE_TO_TURN_BACK	100

#define TIME_TO_THROW_BONES		2000

#define SKELETON_BBOX_WIDTH		17
#define SKELETON_BBOX_HEIGHT	31

class CSkeleton :
	public CMonster
{
	vector<CBone *> bone;
	int number;

	float left, right;

	float min, max;

	DWORD start_to_throw;
	DWORD jump_time;

	bool fire;
	bool jump;

	bool isChange;

	bool is_back;
	DWORD time_skeleton_hiteffect;
public:
	CSkeleton();
	CSkeleton(float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	//CBone *GetBone() { return bone; }
	void SetState(int state);
	~CSkeleton();
};

