#pragma once
#define SIMON_TEXTURE_PATH L"castlevania_texture\\Simon\\Simon.png"
#define WHIP_TEXTURE_PATH L"castlevania_texture\\Weapon\\Whip.png"
#define PANTHER_TEXTURE_PATH L"castlevania_texture\\Enemy\\Panther.png"
#define GHOUL_TEXTURE_PATH L"castlevania_texture\\Enemy\\Ghoul.png"
#define ITEM_TEXTURE_PATH L"castlevania_texture\\Weapon\\Items.png"
#define CANDLE_TEXTURE_PATH L"castlevania_texture\\Weapon\\Candle.png"
#define HITEFFECT_TEXTURE_PATH L"Hit effect.png"
#define DOOR_TEXTURE_PATH L"castlevania_texture\\Weapon\\Door.png"
#define BAT_TEXTURE_PATH L"castlevania_texture\\Enemy\\Bat.png"
#define BRICK_TEXTURE_PATH L"castlevania_texture\\Weapon\\Brick.png"
#define FISHMAN_TEXTURE_PATH L"castlevania_texture\\Enemy\\Fishman.png"
#define BULLET_TEXTURE_PATH L"castlevania_texture\\Weapon\\Bullet.png"
#define BOSS_BAT_TEXTURE_PATH L"castlevania_texture\\Enemy\\BossBat.png"
#define BREAKINGWALL_TEXTEURE_PATH L"castlevania_texture\\Weapon\\BreakingWall.png"
#define CASTLEGATE_TEXTEURE_PATH L"castlevania_texture\\Background\\Castle_Gate.png"
#define SKELETON_TEXTURE_PATH	L"castlevania_texture\\Enemy\\Skeleton.png"
#define EAGLE_TEXTURE_PATH	L"castlevania_texture\\Enemy\\Eagle.png"
#define HUNCHBACK_TEXTURE_PATH	L"castlevania_texture\\Enemy\\Monkey.png"
#define DRACULA_TEXTURE_PATH	L"castlevania_texture\\Enemy\\Dracula.png"
#define OTHER_STUFF_TEXTURE_PATH	L"castlevania_texture\\Weapon\\Items.png"
#define SPLASH_EFFECT_TEXTURE_PATH L"castlevania_texture\\Weapon\\Objects & Effects.png"

#define ID_HITEFFECT 10
#define ID_CANDLE	1
#define ID_ITEM 3
#define ID_SIMON 2
#define ID_WHIP	 6
#define ID_PANTHER 9
#define ID_GHOUL	100
#define ID_DOOR		4
#define ID_BAT		5
#define ID_BRICK	8
#define ID_FISHMAN	11
#define ID_BULLET	12
#define ID_BOSS_BAT	13
#define ID_BREAKINGWALL	14
#define ID_CASTLEGATE	17
//#define ID_TITLE_SCREEN		15
//#define ID_INTRO_SCREEN		16
//#define ID_HEAL			18
//#define ID_BLACKBOARD 19
#define ID_MAP_LEVEL_6	20
#define ID_SKELETON		21
#define ID_EAGLE		22
#define ID_HUNCHBACK	23
#define ID_DRACULA		24
#define ID_OTHER_STUFF	25
#define ID_SPLASH_EFFECT	26

class CResource
{
public:
	void LoadSimon();
	void LoadWhip();
	void LoadPanther();
	void LoadGhoul();
	void LoadDagger();
	void LoadHeart();
	void LoadWhipUpdate();
	void LoadCandle();
	void LoadHitEffect();
	void LoadDoor();
	void LoadBat();
	void LoadMoneyBag();
	void LoadAxe();
	void LoadAxe_animation();
	void LoadBoomerang();
	void LoadHollyWater();
	void LoadBrick();
	void LoadFishman();
	void LoadBullet();
	void LoadBossBat();
	void LoadBreakingWall();
	void LoadCastleGate();
	void LoadSkeleton();
	void LoadBone();
	void LoadEagle();
	void LoadHunchback();
	void LoadDracula();
	void LoadSpiritDracula();
	void LoadOtherStuff();
	void LoadPotRoast();
	void LoadSplashEffect();
};