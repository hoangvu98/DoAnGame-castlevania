#pragma once
#include "GameObject.h"

#define SPLASH_EFFECT_STATE_FLY	0
#define SPLASH_EFFECT_STATE_FALL	1
#define SPLASH_EFFECT_GRAVITY 0.01f

class CSplashEffect :
	public CGameObject
{
	float height;
public:
	CSplashEffect();
	CSplashEffect(float vx, float vy, float height);
	~CSplashEffect();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void SetState(int state);
};

