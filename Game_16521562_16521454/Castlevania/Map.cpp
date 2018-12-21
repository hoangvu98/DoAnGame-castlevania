#include "Map.h"

CMap::CMap()
{

	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();
	animations = CAnimations::GetInstance();
	tilemap = new CTileMap();
	prev_scene = 0;
	scene = 0;
}

CMap::~CMap()
{
}




void CMap::GetUpdateObjects(vector<LPGAMEOBJECT>* objects)
{
	float cam_x, cam_y;
	CGame *game = CGame::GetInstance();
	game->GetCamera(cam_x, cam_y);
	cells->GetListOfObjects(objects, cam_x, cam_y);
	cellsobject->GetListOfObjectsnotchange(objects, cam_x, cam_y);
}

void CMap::GetSizeOfMap(float &width, float &height)
{
	tilemap->GetSize(width, height);
}

void CMap::LoadMap()
{

}

void CMap::Render()
{

}


