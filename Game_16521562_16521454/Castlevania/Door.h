#pragma once
#include "GameObject.h"
#define DOOR_WIDTH	18
#define DOOR_OPEN_WIDTH	40
#define DOOR_HEIGHT	34

#define DOOR_STATE_NORMAL	0
#define DOOR_STATE_OPEN		1
#define DOOR_STATE_CLOSE	2

#define DOOR_ANI_NORMAL		0
#define DOOR_ANI_OPEN_1		1
#define DOOR_ANI_OPEN_2		2

class CDoor :
	public CGameObject
{
	bool IsHiden;
	bool stop;
	int i;
	int scene;
	bool IsStair;
	bool IsAuto;
	DWORD time_open;
public:
	int size=0;
	bool IsGo = true;
	float cx, cy;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render();
	void SetState(int state);
	void SetStop(bool stop) { this->stop = stop; }
	void SetIsHiDen(bool IsHiden) {this->IsHiden= IsHiden;}
	bool GetIsHiden() { return IsHiden; }
	void SetIsAuto(bool IsAuto) { this->IsAuto = IsAuto; }
	bool GetIsAuto() { return IsAuto; }
	void SetScene(int scene) { this->scene = scene; }
	int GetScene() { return scene; }
	void SetIsStair(bool IsStair) {this->IsStair = IsStair;}
	bool GetIsStair() { return IsStair; }
	DWORD GetTimeOpen() { return time_open; }
	CDoor();
};

