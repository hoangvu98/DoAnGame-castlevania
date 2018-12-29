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
	float x, y, width, height, height_fly;
	in >> id;
	in >> x;
	in >> y; 
	in >> width;
	in >> height;
	in >> type; 
	in >> item;
	in >> height_fly;
	in >> state;

	switch (id)
	{
	case CANDLE:
		if (item >= 0)
			object = new CCandle(type, item);
		else object = new CCandle(type);

		object->SetPosition(x, y);
		object->SetState(0);
		break;
	case HIDENOBJECT:
		object = new CHidenObject(width, height);
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
		object = new CFishman();
		object->SetState(state);
		object->SetPosition(x, y);
		object->Setnx(-1);
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
		break;
	case HUNCHBACK:
		break;
	case DRACULA:
		object = CDracula::GetInstance();
		object->Setnx(-1);
		object->SetState(state);
		break;
	}
}
