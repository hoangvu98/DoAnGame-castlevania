#include "InputImage.h"
#include "Candle.h"
#include "Panther.h"
#include "BossBat.h"
#include "Ghoul.h"
#include "Skeleton.h"
#include "Fishman.h"
#include "Eagle.h"
#include "Dracula.h"
#include "Hunchback.h"
#include "Water.h"


void CInputImage::LoadDataFromFile(ifstream & in, int & id, int & left, int & top, int & right, int & bottom, int & aniID)
{
	in >> id;
	in >> left;
	in >> top;
	in >> right;
	in >> bottom;
	in >> aniID;
}

void CInputImage::LoadTexture(ifstream & in, CSprites * sprites, LPANIMATION & ani, LPDIRECT3DTEXTURE9 texture, CAnimations * animations, int & tempaniID, int time)
{
	int aniID, id, left, top, right, bottom;
	LoadDataFromFile(in, id, left, top, right, bottom, aniID);
	if (tempaniID != aniID)
	{
		tempaniID = aniID;
		ani = new CAnimation(time);
	}

	sprites->Add(id, left, top, right, bottom, texture);
	ani->Add(id);
	animations->Add(aniID, ani);
}

void CInputImage::LoadObjectFromFile(ifstream & in, LPGAMEOBJECT & object)
{
	int id, type, item, state;
	float x, y, width, height, height_fly, nx;
	float stair_x, stair_y, a_x, a_y;
	in >> id;
	in >> x;
	in >> y;
	in >> width;
	in >> height;
	in >> type;
	in >> item;
	in >> height_fly;
	in >> state;
	in >> stair_x;
	in >> stair_y;
	in >> nx;
	in >> a_x;
	in >> a_y;

	switch (id)
	{
	case CANDLE:
		if (item >= 0)
			object = new CCandle(type, item);
		else object = new CCandle(type);

		object->SetPosition(x, y);
		object->SetState(state);
		break;
	case HIDENOBJECT:
		switch (state)
		{
		case HIDENOBJECT_STATE_STAIR_DOWN:
		case HIDENOBJECT_STATE_STAIR_UP:
		case HIDENOBJECT_STATE_STAIR_UP_DOWN:
			object = new CHidenObject(width, height, stair_x, stair_y);
			object->Setnx((int)nx);
			break;
		default:
			object = new CHidenObject(width, height);
			break;
		}
		object->SetState(state);
		object->SetPosition(x, y);
		break;
	case GHOUL:
		CGhoul* ghoul;
		ghoul = new CGhoul();
		ghoul->SetPosition(x, y);
		ghoul->SetState(state);
		ghoul->SetLimitArea(a_x, a_y);
		object = (CGameObject *)ghoul;
		break;
	case PANTHER:
		object = new CPanther(x, y);
		object->Setnx(-1);
		object->SetState(state);
		break;
	case FISHMAN:
		object = new CFishman(width, height, a_x, a_y);
		object->SetState(state);
		object->SetPosition(x, y);
		object->Setnx((int)nx);
		break;
	case BOSSBAT:
		object = CBossBat::GetInstance();
		object->SetPosition(x, y);
		break;
	case SKELETON:
		object = new CSkeleton(x, y);
		object->SetState(SKELETON_STATE_WALKING_RIGHT);
		break;
	case EAGLE:
		object = new CEagle(width, height, a_x, a_y);
		object->SetPosition(x, y);
		object->SetState(state);
		break;
	case DRACULA:
		object = CDracula::GetInstance();
		object->Setnx(-1);
		object->SetState(state);
		break;
	case BAT:
		object = new CBat(type, width, height, a_x, a_y, height_fly);
		object->SetPosition(x, y);
		object->SetState(state);
		break;
	case BRICK:
		object = new CBrick(x, y);
		object->SetState(state);
		break;
	case WATER:
		object = new CWater(x, y);
		object->SetPosition(x, y);
		break;
	}
}

void CInputImage::LoadDoorFromFile(ifstream & in, CDoor *& door)
{
	int state, ishiden, scene;
	float x, y, cx, cy, size;
	in >> state;
	in >> x;
	in >> y;
	in >> ishiden;
	in >> cx;
	in >> cy;
	in >> scene;
	in >> size;
	if (state < 0)
	{
		door = new CDoor();
		door->SetPosition(x, y);
		door->size = size;
		door->SetIsHiDen(ishiden);
		door->SetScene(scene);
	}
	else
	{
		door = new CDoor();
		door->SetState(state);
		door->SetPosition(x, y);
		//if (cx != -1)
		door->cx = cx;
		//if (cy != -1);
		door->cy = cy;
		door->SetIsHiDen(ishiden);
		door->SetScene(scene);
	}
}
