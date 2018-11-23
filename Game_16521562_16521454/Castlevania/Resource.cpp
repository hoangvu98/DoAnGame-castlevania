#include "Resource.h"
#include "Textures.h"
#include "InputImage.h"
#include "debug.h"
void CResource::LoadSimon()
{
	CTextures *texture = CTextures::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();
	texture->Add(ID_SIMON, SIMON_TEXTURE_PATH, D3DCOLOR_XRGB(0, 128, 128));
	LPDIRECT3DTEXTURE9 texsimon = texture->Get(ID_SIMON);
	ifstream in("Data\\Simon.txt");

	LPANIMATION ani;
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 3);//walk left
	animations->Add(101, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 3);//walk right
	animations->Add(102, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 1);//idle left
	animations->Add(201, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 1);//idle right
	animations->Add(202, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 1);//jump left
	animations->Add(301, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 1);//jump right
	animations->Add(302, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 3, 150); //fight left
	animations->Add(401, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 3, 150); //fight right
	animations->Add(402, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 3, 150);//knee fight left
	animations->Add(501, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 3, 150); //knee fight right
	animations->Add(502, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 2, 200); //stair walk left
	animations->Add(601, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 2, 200); //stair walk right
	animations->Add(602, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 1); //stair left
	animations->Add(603, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 1); //stair right
	animations->Add(604, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 3, 150); //stair fight left
	animations->Add(605, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 3, 150); //stair fight right
	animations->Add(606, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 1); //collusion monster left 
	animations->Add(701, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 1);//collusion monster right
	animations->Add(702, ani);
	in.close();
}

void CResource::LoadWhip()
{
	CTextures *texture = CTextures::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();
	texture->Add(ID_WHIP, WHIP_TEXTURE_PATH, D3DCOLOR_XRGB(0, 128, 128));

	ifstream in("Data\\Whip.txt");
	LPANIMATION ani;
	LPDIRECT3DTEXTURE9 texwhip = texture->Get(ID_WHIP);
	CInputImage::AddAnimation(in, sprites, ani, texwhip, 3, 150);
	animations->Add(2000, ani);
	CInputImage::AddAnimation(in, sprites, ani, texwhip, 3, 150);
	animations->Add(2001, ani);

	CInputImage::AddAnimation(in, sprites, ani, texwhip, 3, 150);
	animations->Add(2002, ani);
	CInputImage::AddAnimation(in, sprites, ani, texwhip, 3, 150);
	animations->Add(2003, ani);

	CInputImage::AddAnimation(in, sprites, ani, texwhip, 3, 150);
	animations->Add(2004, ani);
	CInputImage::AddAnimation(in, sprites, ani, texwhip, 3, 150);
	animations->Add(2005, ani);

	CInputImage::AddAnimation(in, sprites, ani, texwhip, 3, 150);
	animations->Add(2006, ani);
	CInputImage::AddAnimation(in, sprites, ani, texwhip, 3, 150);
	animations->Add(2007, ani);
	in.close();
}

void CResource::LoadPanther()
{
	CTextures *texture = CTextures::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();
	texture->Add(ID_PANTHER, PANTHER_TEXTURE_PATH, D3DCOLOR_XRGB(96, 68, 106));
	ifstream in;
	in.open("Data\\Panther.txt");
	if (!in) DebugOut(L"Can't open file");
	LPANIMATION ani;
	LPDIRECT3DTEXTURE9 texpanther = texture->Get(ID_PANTHER);
	

	CInputImage::AddAnimation(in, sprites, ani, texpanther, 1);
	animations->Add(4000, ani);
	CInputImage::AddAnimation(in, sprites, ani, texpanther, 1);
	animations->Add(4001, ani);
	CInputImage::AddAnimation(in, sprites, ani, texpanther, 3);
	animations->Add(4002, ani);
	CInputImage::AddAnimation(in, sprites, ani, texpanther, 3);
	animations->Add(4003, ani);
	CInputImage::AddAnimation(in, sprites, ani, texpanther, 1);
	animations->Add(4004, ani);
	CInputImage::AddAnimation(in, sprites, ani, texpanther, 1);
	animations->Add(4005, ani);
	in.close();
}

void CResource::LoadGhoul()
{
	CTextures *texture = CTextures::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();
	texture->Add(ID_GHOUL, GHOUL_TEXTURE_PATH, D3DCOLOR_XRGB(96, 68, 106));


	ifstream in("Data\\Ghoul.txt");
	LPANIMATION ani;
	LPDIRECT3DTEXTURE9 texghoul = texture->Get(ID_GHOUL);
	CInputImage::AddAnimation(in, sprites, ani, texghoul, 2);//left
	animations->Add(10000, ani);
	CInputImage::AddAnimation(in, sprites, ani, texghoul, 2);//right
	animations->Add(10001, ani);
	in.close();
}

void CResource::LoadDagger()
{
	CTextures *texture = CTextures::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();
	texture->Add(ID_ITEM, ITEM_TEXTURE_PATH, D3DCOLOR_XRGB(128, 0, 0));
	LPANIMATION ani = new CAnimation(100);
	LPDIRECT3DTEXTURE9 texitem;
	texitem = texture->Get(ID_ITEM);
	ifstream in("Data\\Dagger.txt");
	CInputImage::AddAnimation(in, sprites, ani, texitem, 1);
	animations->Add(6000, ani);
	CInputImage::AddAnimation(in, sprites, ani, texitem, 1);
	animations->Add(6001, ani);
	in.close();
}

void CResource::LoadHeart()
{
	CTextures *texture = CTextures::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();
	texture->Add(ID_ITEM, ITEM_TEXTURE_PATH, D3DCOLOR_XRGB(128, 0, 0));
	LPANIMATION ani = new CAnimation(100);
	LPDIRECT3DTEXTURE9 texitem;
	texitem = texture->Get(ID_ITEM);
	ifstream in("Data\\Heart.txt");
	CInputImage::AddAnimation(in, sprites, ani, texitem, 1);
	animations->Add(7000, ani);
	CInputImage::AddAnimation(in, sprites, ani, texitem, 1);
	animations->Add(8000, ani);
	in.close();
}

void CResource::LoadWhipUpdate()
{
	CTextures *texture = CTextures::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();
	texture->Add(ID_ITEM, ITEM_TEXTURE_PATH, D3DCOLOR_XRGB(128, 0, 0));
	LPANIMATION ani = new CAnimation(100);
	LPDIRECT3DTEXTURE9 texitem;
	texitem = texture->Get(ID_ITEM);
	ifstream in("Data\\WhipUpdate.txt");
	CInputImage::AddAnimation(in, sprites, ani, texitem, 1);
	animations->Add(9000, ani);
	in.close();
}

void CResource::LoadCandle()
{
	CTextures *texture = CTextures::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();
	texture->Add(ID_CANDLE, CANDLE_TEXTURE_PATH, D3DCOLOR_XRGB(34, 177, 76));
	LPANIMATION ani = new CAnimation(100);
	LPDIRECT3DTEXTURE9 texcandle;
	texcandle = texture->Get(ID_CANDLE);
	ifstream in("Data\\Candle.txt");
	CInputImage::AddAnimation(in, sprites, ani, texcandle, 2);
	animations->Add(11111, ani);
	CInputImage::AddAnimation(in, sprites, ani, texcandle, 2);
	animations->Add(11112, ani);
	in.close();
}
void CResource::LoadHitEffect()
{
	CTextures *texture = CTextures::GetInstance();
	texture->Add(ID_HITEFFECT, HITEFFECT_TEXTURE_PATH, D3DCOLOR_XRGB(34, 177, 76));

	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();

	ifstream in("Data\\Hit_effect.txt");
	LPANIMATION ani;
	LPDIRECT3DTEXTURE9 texhiteffect = texture->Get(ID_HITEFFECT);
	ani = new CAnimation(50);
	CInputImage::AddAnimation(in, sprites, ani, texhiteffect, 1);
	animations->Add(5000, ani);
	CInputImage::AddAnimation(in, sprites, ani, texhiteffect, 3);
	animations->Add(5001, ani);
	in.close();
}
