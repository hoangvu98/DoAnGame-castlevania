#pragma once
#include "GameObject.h"
#include "SplashEffect.h"

#define TIME_SPLASH_EFFECT 2000

#define SPLASH_EFFECT_SPEED_X 0.1f
#define SPLASH_EFFECT_SPEED_Y -0.2f

#define WATER_BBOX_WIDHT	50.0f
#define WATER_BBOX_HEIGHT	10.0f

class CWater :
	public CGameObject
{
	vector<CSplashEffect *> splasheffect;
	bool isUpdateSplashEffect;

	bool wait;
	DWORD start;
public:
	CWater();
	CWater(float x, float y);
	~CWater();

	void Reset();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void GetBoundingBox(float & left, float &top, float &right, float &bottom);
	void StartWait(bool &wait, DWORD &start);
	void SetIsUpEffect(bool isUpdateSplashEffect) { this->isUpdateSplashEffect = isUpdateSplashEffect;}
	void SetWait(bool wait) { this->wait = wait; }

	vector<CSplashEffect *> GetSplashEffect() { return splasheffect; }
	void SetSplashEffect(vector<CSplashEffect *> spEffect) { this->splasheffect = spEffect; }
};

