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
	int i;
	int tempaniID;
	LPANIMATION ani;

	for (i = 0; i < 10; i++)
		CInputImage::LoadTexture(in, sprites, ani, texsimon, animations, tempaniID);

	for (i = 0; i < 12; i++)
		CInputImage::LoadTexture(in, sprites, ani, texsimon, animations, tempaniID, FRAME_TIME_WHIP);

	for (i = 0; i < 8; i++)
		CInputImage::LoadTexture(in, sprites, ani, texsimon, animations, tempaniID, TIME_STAIR / 2);

	for (i = 0; i < 4; i++)
		CInputImage::LoadTexture(in, sprites, ani, texsimon, animations, tempaniID);

	for (i = 0; i < 12; i++)
		CInputImage::LoadTexture(in, sprites, ani, texsimon, animations, tempaniID, FRAME_TIME_WHIP);

	
	for (i = 0; i < 5; i++)
		CInputImage::LoadTexture(in, sprites, ani, texsimon, animations, tempaniID);
	
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
	int i;
	int tempaniID = 0;
	
	for (i = 0; i < 18; i++)
		CInputImage::LoadTexture(in, sprites, ani, texwhip, animations, tempaniID, FRAME_TIME_WHIP);

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
	int i;
	int tempaniID;

	for (i = 0; i < 10; i++)
		CInputImage::LoadTexture(in, sprites, ani, texpanther, animations, tempaniID);

	in.close();
}

void CResource::LoadGhoul()
{
	CTextures *texture = CTextures::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();
	texture->Add(ID_GHOUL, GHOUL_TEXTURE_PATH, D3DCOLOR_XRGB(96, 68, 106));
	int i;
	int tempaniID = 0; 

	ifstream in("Data\\Ghoul.txt");
	LPANIMATION ani;
	LPDIRECT3DTEXTURE9 texghoul = texture->Get(ID_GHOUL);
	for (i = 0; i < 4; i++)
		CInputImage::LoadTexture(in, sprites, ani, texghoul, animations, tempaniID);
	
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

	int i;
	int tempaniID = 0;

	ifstream in("Data\\Dagger.txt");
	for (i = 0; i < 2; i++)
		CInputImage::LoadTexture(in, sprites, ani, texitem, animations, tempaniID);

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
	int i;
	int tempaniID;

	ifstream in("Data\\Heart.txt");

	for (i = 0; i < 2; i++)
		CInputImage::LoadTexture(in, sprites, ani, texitem, animations, tempaniID);

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
	int tempaniID;
	ifstream in("Data\\WhipUpdate.txt");
	CInputImage::LoadTexture(in, sprites, ani, texitem, animations, tempaniID);


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

	int i;
	int tempaniID = 0;

	for (i = 0; i < 4; i++)
		CInputImage::LoadTexture(in, sprites, ani, texcandle, animations, tempaniID);

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
	int i;
	int tempaniID = 0;

	for (i = 0; i < 4; i++)
		CInputImage::LoadTexture(in, sprites, ani, texhiteffect, animations, tempaniID);
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
	int i;
	int tempaniID = 0;
	for (i = 0; i < 3; i++)
		CInputImage::LoadTexture(in, sprites, ani, texdoor, animations, tempaniID);
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
	int i;
	int tempaniID = 0;
	for (i = 0; i < 7; i++)
		CInputImage::LoadTexture(in, sprites, ani, texbat, animations, tempaniID);
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

	int i;
	int tempaniID = 0;
	for (i = 0; i < 3; i++)
		CInputImage::LoadTexture(in, sprites, ani, texitem, animations, tempaniID);
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
	ifstream in("Data\\Axe_item.txt");

	int tempaniID = 0;
	CInputImage::LoadTexture(in, sprites, ani, texitem, animations, tempaniID);

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
	int i;
	int tempaniID;
	for (i = 0; i < 4; i++)
		CInputImage::LoadTexture(in, sprites, ani, texitem, animations, tempaniID);
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
	int i;
	int tempaniID;

	ifstream in("Data\\Boomerang_item.txt");
	CInputImage::LoadTexture(in, sprites, ani, texboomerang, animations, tempaniID);
	in.close();

	in.open("Data\\Boomerang.txt");
	ani = new CAnimation(100);
	for (i = 0; i < 3; i++)
	CInputImage::LoadTexture(in, sprites, ani, texboomerang, animations, tempaniID);
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
	int tempaniID;
	int i;
	for (i = 0; i < 4; i++)
		CInputImage::LoadTexture(in, sprites, ani, texhollywater, animations, tempaniID);
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

	int i;
	int tempaniID;

	for (i = 0; i < 2; i++)
		CInputImage::LoadTexture(in, sprites, ani, texbrick, animations, tempaniID);

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

	int i;
	int tempaniID = 0;
	for (i = 0; i < 8; i++)
		CInputImage::LoadTexture(in, sprites, ani, texfishman, animations, tempaniID);

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
	int i;
	int tempaniID;
	for (i = 0; i < 2; i++)
		CInputImage::LoadTexture(in, sprites, ani, texbullet, animations, tempaniID);
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

	int i;
	int tempaniID = 0;
	for (i = 0; i < 3; i++)
		CInputImage::LoadTexture(in, sprites, ani, texbossbat, animations, tempaniID, 250);
	in.close();
}

void CResource::LoadBreakingWall()
{
	CTextures *textures = CTextures::GetInstance();
	textures->Add(ID_BREAKINGWALL, BREAKINGWALL_TEXTEURE_PATH, D3DCOLOR_XRGB(34, 177, 76));

	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texbreakingwall;
	texbreakingwall = textures->Get(ID_BREAKINGWALL);

	LPANIMATION ani;
	ani = new CAnimation(100);

	ifstream in("Data\\BreakingWall.txt");
	int tempaniID = 0;
	CInputImage::LoadTexture(in, sprites, ani, texbreakingwall, animations, tempaniID);

}
void CResource::LoadCastleGate()
{
	CTextures *textures = CTextures::GetInstance();
	textures->Add(ID_CASTLEGATE, CASTLEGATE_TEXTEURE_PATH, D3DCOLOR_XRGB(0, 0, 0));

	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texcastlegate;
	texcastlegate = textures->Get(ID_CASTLEGATE);

	LPANIMATION ani;
	ani = new CAnimation(100);

	ifstream in("Data\\Castle_Gate.txt");
	int tempaniID = 0;
	CInputImage::LoadTexture(in, sprites, ani, texcastlegate, animations, tempaniID);
	in.close();

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
	int tempaniID = 0;
	int i;
	for (i = 0; i < 4; i++)
		CInputImage::LoadTexture(in, sprites, ani, texskeleton, animations, tempaniID);
	
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

	int tempaniID = 0;
	int i;
	for (i = 0; i < 4; i++)
		CInputImage::LoadTexture(in, sprites, ani, texbone, animations, tempaniID);

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
	int tempaniID = 0;
	int i;
	for (i = 0; i < 6; i++)
		CInputImage::LoadTexture(in, sprites, ani, texeagle, animations, tempaniID);

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
	int tempaniID = 0;
	int i;
	for (i = 0; i < 4; i++)
		CInputImage::LoadTexture(in, sprites, ani, texhunchback, animations, tempaniID);

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
	int tempaniID = 0;
	int i;
	for (i = 0; i < 5; i++)
		CInputImage::LoadTexture(in, sprites, ani, texdracula, animations, tempaniID);

	in.close();

	in.open("Data\\HeadDracula.txt");
	for (i = 0; i < 2; i++)
		CInputImage::LoadTexture(in, sprites, ani, texdracula, animations, tempaniID);


	in.close();
}

void CResource::LoadSpiritDracula()
{
	CTextures *textures = CTextures::GetInstance();

	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texspiritdracula;
	texspiritdracula = textures->Get(ID_DRACULA);

	LPANIMATION ani;
	ani = new CAnimation(100);

	ifstream in("Data\\SpiritDracula.txt");
	int tempaniID = 0;
	int i;
	for (i = 0; i < 10; i++)
		CInputImage::LoadTexture(in, sprites, ani, texspiritdracula, animations, tempaniID);

	in.close();
}

void CResource::LoadOtherStuff()
{
	CTextures *textures = CTextures::GetInstance();
	textures->Add(ID_OTHER_STUFF,OTHER_STUFF_TEXTURE_PATH, D3DCOLOR_XRGB(128, 0, 0));

	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texspiritdracula;
	texspiritdracula = textures->Get(ID_OTHER_STUFF);

	LPANIMATION ani;
	ani = new CAnimation(100);

	ifstream in("Data\\Other_stuff.txt");
	int tempaniID = 0;
	CInputImage::LoadTexture(in, sprites, ani, texspiritdracula, animations, tempaniID);

	in.close();
}

void CResource::LoadPotRoast()
{
	CTextures *textures = CTextures::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();

	LPANIMATION ani = new CAnimation(100);
	ifstream in("Data\\PotRoast.txt");
	LPDIRECT3DTEXTURE9 texpotroast = textures->Get(ID_ITEM);
	int tempaniID = 0;
	CInputImage::LoadTexture(in, sprites, ani, texpotroast, animations, tempaniID);

	in.close();
}

void CResource::LoadSplashEffect()
{
	CTextures *textures = CTextures::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();

	textures->Add(ID_SPLASH_EFFECT, SPLASH_EFFECT_TEXTURE_PATH, D3DCOLOR_XRGB(34, 177, 76));

	LPANIMATION ani = new CAnimation(100);
	ifstream in("Data\\SplashEffect.txt");
	LPDIRECT3DTEXTURE9 texspeffect = textures->Get(ID_SPLASH_EFFECT);
	int tempaniID = 0;
	CInputImage::LoadTexture(in, sprites, ani, texspeffect, animations, tempaniID);

	in.close();
}
