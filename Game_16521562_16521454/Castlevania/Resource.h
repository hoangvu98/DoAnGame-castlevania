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

#define ID_HITEFFECT 10
#define ID_CANDLE	1
#define ID_ITEM 3
#define ID_SIMON 2
#define ID_WHIP	 6
#define ID_PANTHER 9
#define ID_GHOUL	100
#define ID_DOOR		4
#define ID_BAT		5
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
};