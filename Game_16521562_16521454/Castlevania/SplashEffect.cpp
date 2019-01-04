#include "SplashEffect.h"



CSplashEffect::CSplashEffect()
{
	AddAnimation(270001);
}

CSplashEffect::CSplashEffect(float vx, float vy, float height)
{
	SetSpeed(vx, vy);
	this->height = height;
	AddAnimation(270001);
}


CSplashEffect::~CSplashEffect()
{
}

void CSplashEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt);
	x += dx;
	y += dy;
	if (y <= height)
		vy = -vy;
}

void CSplashEffect::Render()
{
	animations[0]->Render(x, y);
}

void CSplashEffect::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
}

void CSplashEffect::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SPLASH_EFFECT_STATE_FLY:
		if (nx < 0) vx = -vx;
		break;
	case SPLASH_EFFECT_STATE_FALL:
		vx = 0;
		break;
	}
}
