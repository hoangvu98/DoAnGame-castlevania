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

void CInputImage::LoadDataFromFile(ifstream & in, int & id, int & left, int & top, int & right, int & bottom)
{
	in >> id;
	in >> left;
	in >> top;
	in >> right;
	in >> bottom;
}

void CInputImage::AddAnimation(ifstream & in, CSprites * sprites, LPANIMATION & ani, LPDIRECT3DTEXTURE9 texture, int n,int time)
{
	int id, left, top, right, bottom;
	int i;
	ani = new CAnimation(time);
	for (i = 0; i < n; i++)
	{
		LoadDataFromFile(in, id, left, top, right, bottom);
		sprites->Add(id, left, top, right, bottom, texture);
		ani->Add(id);
	}
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
			object->Setnx(nx);
			break;
		default:
			object = new CHidenObject(width, height);
			break;
		}
		object->SetState(state);
		object->SetPosition(x, y);
		break;
	case GHOUL:
		object = new CGhoul();
		object->SetPosition(x, y);
		object->SetState(state);
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
		object->Setnx(nx);
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
