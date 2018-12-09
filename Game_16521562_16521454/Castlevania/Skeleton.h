#pragma once
#include "Monster.h"
#include "Bone.h"
#define SKELETON_WALKING_SPEED	0.03f
#define SKELETON_GRAVITY		0.002f

#define SKELETON_STATE_WALKING_LEFT		0
#define SKELETON_STATE_WALKING_RIGHT	300
#define SKELETON_STATE_THROW_BONE		400
#define SKELETION_STATE_JUMP			500

#define SKELETON_ANI_WALKING_LEFT		0
#define SKELETON_ANI_WALKING_RIGHT		1

#define DISTANCE		30
#define DISTANCE_WITH_SIMON	5
#define TIME_TO_THROW_BONES		2000

#define SKELETON_BBOX_WIDTH		17
#define SKELETON_BBOX_HEIGHT	31

class CSkeleton :
	public CMonster
{
	CBone *bone;
	float min, max;
	DWORD start_to_throw;
	bool fire;
public:
	CSkeleton();
	CSkeleton(float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	CBone *GetBone() { return bone; }
	void SetState(int state);
	void SetMinMax();
	~CSkeleton();
};

