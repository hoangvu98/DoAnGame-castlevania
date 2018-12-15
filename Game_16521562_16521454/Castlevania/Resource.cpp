#include "Resource.h"
#include "Textures.h"
#include "InputImage.h"
#include "debug.h"
#include "Simon.h"
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
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 3, FRAME_TIME_WHIP); //fight left
	animations->Add(401, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 3, FRAME_TIME_WHIP); //fight right
	animations->Add(402, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 3, FRAME_TIME_WHIP);//knee fight left
	animations->Add(501, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 3, FRAME_TIME_WHIP); //knee fight right
	animations->Add(502, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 2, TIME_STAIR/2); //stair walk up left
	animations->Add(601, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 2, TIME_STAIR/2); //stair walk up right
	animations->Add(602, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 2, TIME_STAIR / 2); //stair walk down left
	animations->Add(603, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 2, TIME_STAIR / 2); //stair walk down right
	animations->Add(604, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 1); //stair up left
	animations->Add(701, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 1); //stair up right
	animations->Add(702, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 1); //stair down left
	animations->Add(703, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 1); //stair down right
	animations->Add(704, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 3, FRAME_TIME_WHIP); //stair fight up left
	animations->Add(801, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 3, FRAME_TIME_WHIP); //stair fight up right
	animations->Add(802, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 3, FRAME_TIME_WHIP); //stair fight down left
	animations->Add(803, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 3, FRAME_TIME_WHIP); //stair fight down right
	animations->Add(804, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 1); //collusion monster left 
	animations->Add(901, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 1);//collusion monster right
	animations->Add(902, ani);
	CInputImage::AddAnimation(in, sprites, ani, texsimon, 1);//collusion monster right
	animations->Add(1000, ani);
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
	CInputImage::AddAnimation(in, sprites, ani, texwhip, 3, FRAME_TIME_WHIP);
	animations->Add(2000, ani);
	CInputImage::AddAnimation(in, sprites, ani, texwhip, 3, FRAME_TIME_WHIP);
	animations->Add(2001, ani);

	CInputImage::AddAnimation(in, sprites, ani, texwhip, 3, FRAME_TIME_WHIP);
	animations->Add(2002, ani);
	CInputImage::AddAnimation(in, sprites, ani, texwhip, 3, FRAME_TIME_WHIP);
	animations->Add(2003, ani);

	CInputImage::AddAnimation(in, sprites, ani, texwhip, 3, FRAME_TIME_WHIP);
	animations->Add(2004, ani);
	CInputImage::AddAnimation(in, sprites, ani, texwhip, 3, FRAME_TIME_WHIP);
	animations->Add(2005, ani);
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

void CResource::LoadDoor()
{
	CTextures *texture = CTextures::GetInstance();
	texture->Add(ID_DOOR, DOOR_TEXTURE_PATH, D3DCOLOR_XRGB(34, 177, 76));

	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();

	ifstream in("Data\\Door.txt");
	LPANIMATION ani;
	LPDIRECT3DTEXTURE9 texdoor = texture->Get(ID_DOOR);
	ani = new CAnimation(100);
	CInputImage::AddAnimation(in, sprites, ani, texdoor, 1);
	animations->Add(11000, ani);
	ani = new CAnimation(1000);
	CInputImage::AddAnimation(in, sprites, ani, texdoor, 2);
	animations->Add(11001, ani);
	ani = new CAnimation(100);
	CInputImage::AddAnimation(in, sprites, ani, texdoor, 1);
	animations->Add(11002, ani);
	in.close();
}

void CResource::LoadBat()
{
	CTextures *texture = CTextures::GetInstance();
	texture->Add(ID_BAT, BAT_TEXTURE_PATH, D3DCOLOR_XRGB(96, 68, 106));

	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();

	ifstream in("Data\\Bat.txt");
	LPANIMATION ani;
	LPDIRECT3DTEXTURE9 texbat = texture->Get(ID_BAT);
	ani = new CAnimation(100);
	CInputImage::AddAnimation(in, sprites, ani, texbat, 1);
	animations->Add(12000, ani);
	ani = new CAnimation(100);
	CInputImage::AddAnimation(in, sprites, ani, texbat, 3);
	animations->Add(12001, ani);
	ani = new CAnimation(100);
	CInputImage::AddAnimation(in, sprites, ani, texbat, 3);
	animations->Add(12002, ani);
	in.close();
}

void CResource::LoadMoneyBag()
{
	CTextures *texture = CTextures::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();
	texture->Add(ID_ITEM, ITEM_TEXTURE_PATH, D3DCOLOR_XRGB(128, 0, 0));
	LPANIMATION ani = new CAnimation(100);
	LPDIRECT3DTEXTURE9 texitem;
	texitem = texture->Get(ID_ITEM);
	ifstream in("Data\\MoneyBag.txt");
	CInputImage::AddAnimation(in, sprites, ani, texitem, 1);
	animations->Add(13001, ani);
	CInputImage::AddAnimation(in, sprites, ani, texitem, 1);
	animations->Add(13002, ani);
	CInputImage::AddAnimation(in, sprites, ani, texitem, 1);
	animations->Add(13003, ani);
	in.close();
}

void CResource::LoadAxe()
{
	CTextures *texture = CTextures::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();
	texture->Add(ID_ITEM, ITEM_TEXTURE_PATH, D3DCOLOR_XRGB(128, 0, 0));
	LPANIMATION ani = new CAnimation(100);
	LPDIRECT3DTEXTURE9 texitem;
	texitem = texture->Get(ID_ITEM);
	ifstream in("Data\\Axe.txt");
	CInputImage::AddAnimation(in, sprites, ani, texitem, 1);
	animations->Add(14001, ani);
	in.close();
}

void CResource::LoadAxe_animation()
{
	CTextures *texture = CTextures::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();
	texture->Add(ID_ITEM, ITEM_TEXTURE_PATH, D3DCOLOR_XRGB(128, 0, 0));
	LPANIMATION ani = new CAnimation(100);
	LPDIRECT3DTEXTURE9 texitem;
	texitem = texture->Get(ID_ITEM);
	ifstream in("Data\\Axe.txt");
	CInputImage::AddAnimation(in, sprites, ani, texitem, 4);
	animations->Add(14002, ani);
	in.close();
}

void CResource::LoadBoomerang()
{
	CTextures *textures = CTextures::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texboomerang;
	texboomerang = textures->Get(ID_ITEM);

	LPANIMATION ani;
	ani = new CAnimation(100);

	ifstream in("Data\\Boomerang.txt");
	CInputImage::AddAnimation(in, sprites, ani, texboomerang, 1);
	animations->Add(15000, ani);
	in.close();
	in.open("Data\\Boomerang.txt");
	ani = new CAnimation(100);
	CInputImage::AddAnimation(in, sprites, ani, texboomerang, 3);
	animations->Add(15001, ani);
	in.close();
}

void CResource::LoadHollyWater()
{
	CTextures *textures = CTextures::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texhollywater;
	texhollywater = textures->Get(ID_ITEM);

	LPANIMATION ani;
	ani = new CAnimation(100);

	ifstream in("Data\\Holly_water.txt");
	CInputImage::AddAnimation(in, sprites, ani, texhollywater, 1);
	animations->Add(16000, ani);
	ani = new CAnimation(100);
	CInputImage::AddAnimation(in, sprites, ani, texhollywater, 1);
	animations->Add(16001, ani);
	CInputImage::AddAnimation(in, sprites, ani, texhollywater, 2);
	animations->Add(16002, ani);
	in.close();
}

void CResource::LoadBrick()
{
	CTextures *textures = CTextures::GetInstance();
	textures->Add(ID_BRICK, BRICK_TEXTURE_PATH, D3DCOLOR_XRGB(255, 255, 255));

	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texbrick;
	texbrick = textures->Get(ID_BRICK);

	LPANIMATION ani;
	ani = new CAnimation(100);

	ifstream in("Data\\Brick.txt");
	CInputImage::AddAnimation(in, sprites, ani, texbrick, 1);
	animations->Add(17000, ani);

	ani = new CAnimation(100);
	CInputImage::AddAnimation(in, sprites, ani, texbrick, 1);
	animations->Add(17001, ani);
	in.close();
}

void CResource::LoadFishman()
{
	CTextures *textures = CTextures::GetInstance();
	textures->Add(ID_FISHMAN, FISHMAN_TEXTURE_PATH, D3DCOLOR_XRGB(96, 68, 106));

	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texfishman;
	texfishman = textures->Get(ID_FISHMAN);

	LPANIMATION ani;
	ani = new CAnimation(100);

	ifstream in("Data\\Fishman.txt");
	CInputImage::AddAnimation(in, sprites, ani, texfishman, 1);
	animations->Add(18000, ani);

	ani = new CAnimation(100);
	CInputImage::AddAnimation(in, sprites, ani, texfishman, 1);
	animations->Add(18001, ani);

	ani = new CAnimation(100);
	CInputImage::AddAnimation(in, sprites, ani, texfishman, 2);
	animations->Add(18002, ani);

	ani = new CAnimation(100);
	CInputImage::AddAnimation(in, sprites, ani, texfishman, 1);
	animations->Add(18003, ani);

	ani = new CAnimation(100);
	CInputImage::AddAnimation(in, sprites, ani, texfishman, 1);
	animations->Add(18004, ani);

	ani = new CAnimation(100);
	CInputImage::AddAnimation(in, sprites, ani, texfishman, 2);
	animations->Add(18005, ani);

	in.close();
}

void CResource::LoadBullet()
{
	CTextures *textures = CTextures::GetInstance();
	textures->Add(ID_BULLET, BULLET_TEXTURE_PATH, D3DCOLOR_XRGB(96, 68, 106));

	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texbullet;
	texbullet = textures->Get(ID_BULLET);

	LPANIMATION ani;
	ani = new CAnimation(100);

	ifstream in("Data\\Bullet.txt");
	CInputImage::AddAnimation(in, sprites, ani, texbullet, 1);
	animations->Add(19000, ani);

	ani = new CAnimation(100);
	CInputImage::AddAnimation(in, sprites, ani, texbullet, 1);
	animations->Add(19001, ani);
	in.close();
}

void CResource::LoadBossBat()
{
	CTextures *textures = CTextures::GetInstance();
	textures->Add(ID_BOSS_BAT, BOSS_BAT_TEXTURE_PATH, D3DCOLOR_XRGB(160, 32, 64));

	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texbossbat;
	texbossbat = textures->Get(ID_BOSS_BAT);

	LPANIMATION ani;
	ani = new CAnimation(100);

	ifstream in("Data\\BossBat.txt");
	CInputImage::AddAnimation(in, sprites, ani, texbossbat, 1,250);
	animations->Add(20000, ani);

	ani = new CAnimation(100);
	CInputImage::AddAnimation(in, sprites, ani, texbossbat, 2,250);
	animations->Add(20001, ani);
	in.close();
}

void CResource::LoadBreakingWall()
{
	CTextures *textures = CTextures::GetInstance();
	textures->Add(ID_BREAKINGWALL, BREAKINGWALL_TEXTEURE_PATH, D3DCOLOR_XRGB(34, 177, 76));

	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texbullet;
	texbullet = textures->Get(ID_BREAKINGWALL);

	LPANIMATION ani;
	ani = new CAnimation(100);

	ifstream in("Data\\BreakingWall.txt");
	CInputImage::AddAnimation(in, sprites, ani, texbullet, 1);
	animations->Add(21000, ani);
}
void CResource::LoadCastleGate()
{
	CTextures *textures = CTextures::GetInstance();
	textures->Add(ID_CASTLEGATE, CASTLEGATE_TEXTEURE_PATH, D3DCOLOR_XRGB(0, 0, 0));

	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texbullet;
	texbullet = textures->Get(ID_CASTLEGATE);

	LPANIMATION ani;
	ani = new CAnimation(100);

	ifstream in("Data\\Castle_Gate.txt");
	CInputImage::AddAnimation(in, sprites, ani, texbullet, 1);
	animations->Add(21001, ani);
}

void CResource::LoadSkeleton()
{
	CTextures *textures = CTextures::GetInstance();
	textures->Add(ID_SKELETON, SKELETON_TEXTURE_PATH, D3DCOLOR_XRGB(96, 68, 106));

	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texskeleton;
	texskeleton = textures->Get(ID_SKELETON);

	LPANIMATION ani;
	ani = new CAnimation(100);

	ifstream in("Data\\Skeleton.txt");
	CInputImage::AddAnimation(in, sprites, ani, texskeleton, 2);
	animations->Add(220011, ani);

	CInputImage::AddAnimation(in, sprites, ani, texskeleton, 2);
	animations->Add(220012, ani);
	in.close();
}

void CResource::LoadBone()
{
	CTextures *textures = CTextures::GetInstance();
	textures->Add(ID_SKELETON, SKELETON_TEXTURE_PATH, D3DCOLOR_XRGB(96, 68, 106));

	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texbone;
	texbone = textures->Get(ID_SKELETON);

	LPANIMATION ani;
	ani = new CAnimation(100);

	ifstream in("Data\\Bone.txt");
	CInputImage::AddAnimation(in, sprites, ani, texbone, 2);
	animations->Add(220001, ani);

	CInputImage::AddAnimation(in, sprites, ani, texbone, 2);
	animations->Add(220002, ani);
	in.close();
}

void CResource::LoadEagle()
{
	CTextures *textures = CTextures::GetInstance();
	textures->Add(ID_EAGLE, EAGLE_TEXTURE_PATH, D3DCOLOR_XRGB(96, 68, 106));

	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texeagle;
	texeagle = textures->Get(ID_EAGLE);

	LPANIMATION ani;
	ani = new CAnimation(100);

	ifstream in("Data\\Eagle.txt");
	CInputImage::AddAnimation(in, sprites, ani, texeagle, 2,300);
	animations->Add(220003, ani);
	CInputImage::AddAnimation(in, sprites, ani, texeagle, 2, 300);
	animations->Add(220004, ani);
	CInputImage::AddAnimation(in, sprites, ani, texeagle, 1);
	animations->Add(220005, ani);
	CInputImage::AddAnimation(in, sprites, ani, texeagle, 1);
	animations->Add(220006, ani);
	in.close();
}

void CResource::LoadHunchback()
{
	CTextures *textures = CTextures::GetInstance();
	textures->Add(ID_HUNCHBACK, HUNCHBACK_TEXTURE_PATH, D3DCOLOR_XRGB(96, 68, 106));

	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texhunchback;
	texhunchback = textures->Get(ID_HUNCHBACK);

	LPANIMATION ani;
	ani = new CAnimation(100);

	ifstream in("Data\\Hunchback.txt");
	CInputImage::AddAnimation(in, sprites, ani, texhunchback, 1);
	animations->Add(230001, ani);
	CInputImage::AddAnimation(in, sprites, ani, texhunchback, 1);
	animations->Add(230002, ani);
	CInputImage::AddAnimation(in, sprites, ani, texhunchback, 1);
	animations->Add(230003, ani);
	CInputImage::AddAnimation(in, sprites, ani, texhunchback, 1);
	animations->Add(230004, ani);
	in.close();
}

void CResource::LoadDracula()
{
	CTextures *textures = CTextures::GetInstance();
	textures->Add(ID_DRACULA, DRACULA_TEXTURE_PATH, D3DCOLOR_XRGB(160, 32, 64));

	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texdracula;
	texdracula = textures->Get(ID_DRACULA);

	LPANIMATION ani;
	ani = new CAnimation(100);

	ifstream in("Data\\BodyDracula.txt");
	CInputImage::AddAnimation(in, sprites, ani, texdracula, 1);
	animations->Add(240001, ani);
	CInputImage::AddAnimation(in, sprites, ani, texdracula, 1);
	animations->Add(240002, ani);
	CInputImage::AddAnimation(in, sprites, ani, texdracula, 1);
	animations->Add(240003, ani);
	CInputImage::AddAnimation(in, sprites, ani, texdracula, 1);
	animations->Add(240004, ani);
	CInputImage::AddAnimation(in, sprites, ani, texdracula, 1);
	animations->Add(240005, ani);
	in.close();

	in.open("Data\\HeadDracula.txt");
	CInputImage::AddAnimation(in, sprites, ani, texdracula, 1);
	animations->Add(240011, ani);
	CInputImage::AddAnimation(in, sprites, ani, texdracula, 1);
	animations->Add(240012, ani);
	in.close();
}
