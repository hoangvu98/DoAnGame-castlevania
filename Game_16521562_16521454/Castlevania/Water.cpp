#include "Water.h"
#include "Fishman.h"


CWater::CWater()
{
	splasheffect.push_back(new CSplashEffect(0.0f, SPLASH_EFFECT_SPEED_Y, 100.0f));
	splasheffect.push_back(new CSplashEffect(SPLASH_EFFECT_SPEED_X, SPLASH_EFFECT_SPEED_Y, 130.0f));
	splasheffect.push_back(new CSplashEffect(SPLASH_EFFECT_SPEED_X, SPLASH_EFFECT_SPEED_Y, 130.0f));
	splasheffect[0]->Setnx(1);
	splasheffect[1]->Setnx(1);
	splasheffect[2]->Setnx(-1);
	for (int i = 0; i < 3; i++)
		splasheffect[i]->SetState(SPLASH_EFFECT_STATE_FLY);
}

CWater::CWater(float x, float y)
{
	wait = false;
	splasheffect.push_back(new CSplashEffect(0.0f, SPLASH_EFFECT_SPEED_Y, 100.0f));
	splasheffect.push_back(new CSplashEffect(SPLASH_EFFECT_SPEED_X, SPLASH_EFFECT_SPEED_Y, 130.0f));
	splasheffect.push_back(new CSplashEffect(SPLASH_EFFECT_SPEED_X, SPLASH_EFFECT_SPEED_Y, 130.0f));
	splasheffect[0]->Setnx(1);
	splasheffect[1]->Setnx(-1);
	splasheffect[2]->Setnx(1);
	
	for (int i = 0; i < 3;i++)
	{
		splasheffect[i]->SetPosition(x + 17.0f, y + 17.0f);
		splasheffect[i]->SetState(SPLASH_EFFECT_STATE_FLY);
	}
}


CWater::~CWater()
{
	
}

void CWater::Reset()
{
	splasheffect[0]->SetSpeed(0.0f, SPLASH_EFFECT_SPEED_Y);
	splasheffect[1]->SetSpeed(SPLASH_EFFECT_SPEED_X, SPLASH_EFFECT_SPEED_Y);
	splasheffect[2]->SetSpeed(SPLASH_EFFECT_SPEED_X, SPLASH_EFFECT_SPEED_Y);
}

void CWater::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{	
	if (isUpdateSplashEffect)
	{
		for (int i = 0; i < 3; i++)
			splasheffect[i]->Update(dt);
	}

	if (wait)
		StartWait(wait, start);
	if (GetTickCount() - start > TIME_SPLASH_EFFECT)
	{
		start = 0;
		isUpdateSplashEffect = false;
		Reset();
	}
	//DebugOut(L"dang update water\n");
}

void CWater::Render()
{
	if (isUpdateSplashEffect)
	{
		for (int i = 0; i < 3; i++)
			splasheffect[i]->Render();
	}
	//RenderBoundingBox(150);
}

void CWater::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + WATER_BBOX_WIDHT;
	bottom = y + WATER_BBOX_HEIGHT;
}

void CWater::StartWait(bool & wait, DWORD & start)
{
	wait = false;
	start = GetTickCount();
}
