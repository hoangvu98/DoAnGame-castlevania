

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include <string>
#include <fstream>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Simon.h"
#include "Brick.h"
#include "Ghoul.h"
#include "Bat.h"
#include "Candle.h"
#include "Map.h"
#include "HidenObject.h"
#include "EntranceLevel.h"
#include "ClockTowerLevel.h"
#include "InputImage.h"
#include "Resource.h"
#include "BlackBoard.h"
using namespace std;

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"Castlevania"

#define BRICK_TEXTURE_PATH L"brick.png"
#define BBOX_TEXTURE_PATH L"bbox.png"
#define CANDLE_TEXTURE_PATH L"castlevania_texture\\Weapon\\Candle.png"
#define TITLE_SCREEN_PATH L"castlevania_texture\\Background\\Title Screen.png"
#define INTRO_SCREEN_PATH L"castlevania_texture\\Background\\introscreen.png"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 262

#define MAX_FRAME_RATE 120

#define ID_BRICK			3
#define ID_BAT				5
#define ID_TITLE_SCREEN		15
#define ID_INTRO_SCREEN		16
CGame *game;
CSimon *simon;
CBrick *brick;
CGhoul *ghoul;
CBat *bat;
CResource *resource;
CBlackBoard * blackboard;

vector<LPGAMEOBJECT> objects;
CHidenObject *hidenObject;
LPDIRECT3DTEXTURE9 texture_title;
LPDIRECT3DTEXTURE9 texture_intro;
int screen = 0;
DWORD Time_screen;
class CSampleKeyHander : public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler;
void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_UP:
		break;
	case DIK_RETURN:
		if (screen == 0)
		{
			screen = 1;
			Time_screen = GetTickCount();
		}
		break;
	case DIK_D:
		if (simon->GetFight() == false)
		{
			if (!game->IsKeyDown(DIK_DOWN) && simon->GetJump() == 0)
			{
				simon->SetState(SIMON_STATE_JUMP);
				simon->SetJump(1);
			}
		}
		break;
	case DIK_DOWN:
		break;
	case DIK_F:
		DWORD t = GetTickCount() - simon->GetWhip()->GetFrameWhip();
		if (t >= 3 * FRAME_TIME_WHIP)
		{
			if (game->IsKeyDown(DIK_UP) && t >= 3 * FRAME_TIME_WHIP)
			{
				if (simon->GetOnSkill())
				{
					if (simon->nx > 0)
						simon->GetWeapon()->SetState(ITEM_STATE_WEAPON_RIGHT);
					else
						simon->GetWeapon()->SetState(ITEM_STATE_WEAPON_LEFT);
					simon->SetFrameWeapon();
					simon->SetSkill(true);
					float temp_x, temp_y;
					simon->GetPosition(temp_x, temp_y);
					simon->GetWeapon()->SetPosition(temp_x, temp_y + 5);
					if (simon->state == SIMON_STATE_STAIR_UP || simon->state == SIMON_STATE_STAIR_UP_IDLE)
						simon->SetState(SIMON_STATE_STAIR_UP_IDLE);
					else if (simon->state == SIMON_STATE_STAIR_DOWN || simon->state == SIMON_STATE_STAIR_DOWN_IDLE)
						simon->SetState(SIMON_STATE_STAIR_DOWN_IDLE);
					else if (simon->state != SIMON_STATE_JUMP)
						simon->SetState(SIMON_STATE_IDLE);
				}
			}
			else
			{
				if (simon->nx > 0)
					simon->GetWhip()->SetStateWhip(WHIP_STATE_RIGHT);
				else
					simon->GetWhip()->SetStateWhip(WHIP_STATE_LEFT);
				simon->SetFight(true);
				if (simon->GetStair() != 2)
				{
					if (game->IsKeyDown(DIK_DOWN))
						simon->SetState(SIMON_STATE_KNEE);
					else if (simon->state != SIMON_STATE_JUMP)
						simon->SetState(SIMON_STATE_IDLE);
				}
			}
			DWORD time = GetTickCount();
			simon->GetWhip()->SetFrameWhip(time);
		}
		break;
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_DOWN:
		if (simon->GetFight() == false)
		{
			if (simon->GetStair() != 2 && simon->GetStair() != 6)
			{
				simon->SetState(SIMON_STATE_IDLE);
			}
		}
		break;
	}
}

void CSampleKeyHander::KeyState(BYTE *states)
{
	if (simon->GetStair() == 2)
	{
		if (!simon->GetSkill())
		{
			if (simon->GetFight() == false)
			{
				DWORD now = GetTickCount();

				if (now - simon->GetFrameStair() > TIME_STAIR)
				{
					if (simon->IsUp == 2)
					{
						simon->y -= 3.0f;
						simon->IsUp = 0;
						simon->SetStair(0);
					}
					if (simon->IsDown == 2)
					{
						simon->y -= 3.0f;
						simon->IsDown = 0;
						simon->SetStair(0);
					}
					if (game->IsKeyDown(DIK_UP))
					{
						if (simon->IsUp == 1)
						{
							simon->IsUp = 2;
						}

						if (simon->GetState() == SIMON_STATE_STAIR_DOWN ||
							simon->GetState() == SIMON_STATE_STAIR_DOWN_IDLE)
							simon->nx = -simon->nx;
						simon->SetState(SIMON_STATE_STAIR_UP);
						simon->SetFrameStair();
					}
					else if (game->IsKeyDown(DIK_DOWN))
					{
						if (simon->IsDown == 1)
						{
							simon->IsDown = 2;
						}
						if (simon->GetState() == SIMON_STATE_STAIR_UP ||
							simon->GetState() == SIMON_STATE_STAIR_UP_IDLE)
							simon->nx = -simon->nx;
						simon->SetState(SIMON_STATE_STAIR_DOWN);
						simon->SetFrameStair();
					}
					else
					{
						if (simon->GetState() == SIMON_STATE_STAIR_UP || simon->GetState() == SIMON_STATE_STAIR_UP_IDLE)
							simon->SetState(SIMON_STATE_STAIR_UP_IDLE);
						else
							simon->SetState(SIMON_STATE_STAIR_DOWN_IDLE);
					}
				}
			}
		}
	}
	else
	{
		if (simon->GetJump() == 0)
		{
			if (!simon->GetSkill())
			{
				if (simon->GetFight() == false)
				{
					if (game->IsKeyDown(DIK_UP)
						&& (simon->GetStair() == 1 || simon->GetStair() == 4))
					{
						simon->SetStateAuto(1);
						simon->SetStair(5);
					}
					else if (game->IsKeyDown(DIK_DOWN) &&
						(simon->GetStair() == 3 || simon->GetStair() == 4))
					{
						simon->SetStateAuto(1);
						simon->SetStair(6);
					}
					else if (game->IsKeyDown(DIK_DOWN) && simon->GetStair() != 3 && simon->GetStair() != 4)
					{
						if (game->IsKeyDown(DIK_UP))
							simon->SetState(SIMON_STATE_IDLE);
						else
						{
							simon->SetState(SIMON_STATE_KNEE);
							if (game->IsKeyDown(DIK_LEFT)) simon->nx = -1;
							else if (game->IsKeyDown(DIK_RIGHT))  simon->nx = 1;
						}
					}
					else
					{
						if (game->IsKeyDown(DIK_LEFT))
							simon->SetState(SIMON_STATE_WALKING_LEFT);
						else if (game->IsKeyDown(DIK_RIGHT))
							simon->SetState(SIMON_STATE_WALKING_RIGHT);
						else simon->SetState(SIMON_STATE_IDLE);
					}
				}
			}
		}
	}

}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources
	In this example: load textures, sprites, animations and mario object

	TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/

void LoadResources()
{
	CTextures *texture = CTextures::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();
	texture->Add(ID_BRICK, BBOX_TEXTURE_PATH, D3DCOLOR_XRGB(237, 28, 36));
	texture->Add(ID_BBOX, BBOX_TEXTURE_PATH, D3DCOLOR_XRGB(0, 128, 128));
	texture->Add(ID_CANDLE, CANDLE_TEXTURE_PATH, D3DCOLOR_XRGB(34, 177, 76));
	texture->Add(ID_ITEM, ITEM_TEXTURE_PATH, D3DCOLOR_XRGB(128, 0, 0));
	texture->Add(ID_TITLE_SCREEN, TITLE_SCREEN_PATH, D3DCOLOR_XRGB(255, 255, 255));
	texture->Add(ID_INTRO_SCREEN, INTRO_SCREEN_PATH, D3DCOLOR_XRGB(255, 255, 255));
	resource = new CResource();
	resource->LoadSimon();
	resource->LoadWhip();
	resource->LoadPanther();
	resource->LoadGhoul();
	resource->LoadDagger();
	resource->LoadHeart();
	resource->LoadWhipUpdate();
	resource->LoadCandle();
	resource->LoadHitEffect();
	resource->LoadDoor();
	resource->LoadBat();
	resource->LoadMoneyBag();
	resource->LoadAxe();
	resource->LoadAxe_animation();
	resource->LoadBoomerang();
	resource->LoadHollyWater();
	resource->LoadBrick();
	resource->LoadFishman();
	resource->LoadBullet();
	resource->LoadBossBat();
	resource->LoadBreakingWall();
	resource->LoadCastleGate();
	resource->LoadBone();
	resource->LoadSkeleton();
	resource->LoadEagle();
	resource->LoadHunchback();
	resource->LoadDracula();
	resource->LoadSpiritDracula();
	simon = CSimon::GetInstance();
	simon->SetPosition(2053.0f, 28.0f);
	//simon->SetPosition(906.0f, 34.0f);
	//simon->SetPosition(1378.0f, 34.0f);
	//simon->SetPosition(618.4f, 129.0f);
	simon->SetPosition(100.0f, 20.0f);
	//simon->SetPosition(226.0f, 130.0f); 
	simon->SetState(SIMON_STATE_WALKING_LEFT);
	simon->SetPosition(1460.0f, 30.0f);//map 1
	simon->SetPosition(550.0f, 80.0f);//map 2
	//simon->SetPosition(267.0f, 0.0f);//map 2
	//simon->SetPosition(629.0f, 10.0f);//map 3
	//simon->SetPosition(450.0f, 10.0f);//map 3
	//simon->SetPosition(40.0f, 10.0f);//map 3
	simon->SetPosition(180.0f, 30.0f);//map 4
	//simon->SetPosition(190.0f, 30.0f);//map 5
	simon->SetPosition(448.0f, 76.0f);//map 5
	//simon->SetPosition(190.0f, 30.0f   /*719.0f, 45.0f*/);
	//simon->SetPosition(49.0f, 104.0f);
	simon->SetPosition(50.0f, 0.0f);
	texture_title = texture->Get(ID_TITLE_SCREEN);
	texture_intro = texture->Get(ID_INTRO_SCREEN);
	simon->map->SetScene(SCENE_4);
	screen = 2;
	simon->map->LoadObject();
	simon->map->LoadMap();
	blackboard = new CBlackBoard();
}


void LoadDataFromFile(ifstream &in,
	int &id,
	int &left, int &top,
	int &right, int &bottom)
{
	in >> id;
	in >> left;
	in >> top;
	in >> right;
	in >> bottom;

}
/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	vector<LPGAMEOBJECT> coObjects;
	switch (screen)
	{
	case 1:
		objects.clear();
		objects.push_back(simon);
		for (int i = 0; i < objects.size() - 1; i++)
			coObjects.push_back(objects[i]);
		for (int i = 0; i < objects.size(); i++)
			objects[i]->Update(dt, &coObjects);
		break;
	case 2:
		if (simon->GetReset())
		{
			int live = simon->GetLive();
			if (live >= 1)
			{
				simon->SetLive(live-1);
				simon->SetHeart(5);
				simon->SetHealth(16);
				simon->SetReset(false);
				simon->map->ResetScene();
				float x, y;
				simon->map->NextScece(x, y);
				if (x != 0 || y != 0)
					simon->SetPosition(x, y);
				simon->Camera();
				simon->map->LoadMap();
			}
			else
			{
				LoadResources();
			}
		}
		if (simon->map->GetIsNext())
		{
			int scene;
			scene = simon->map->GetNextScene();
			simon->map->SetScene(scene);
			float x, y;
			if (simon->simon_x != 0 || simon->simon_y != 0)
				simon->SetPosition(simon->simon_x, simon->simon_y);
			else
			{
				simon->map->NextScece(x, y);
				if (x != 0 || y != 0)
					simon->SetPosition(x, y);
			}
			simon->map->SetIsNext(false);
			simon->SetCameraAuto(0);
			simon->SetStateAuto(0);
			simon->Camera();
		}
		else if (simon->map->GetIsFall())
		{
			int scene;
			scene = simon->map->GetNextScene();
			simon->map->SetScene(scene);
			float x, y;
			if (simon->simon_x != 0 || simon->simon_y != 0)
				simon->SetPosition(simon->simon_x, simon->simon_y);
			else
			{
				simon->map->NextScece(x, y);
				if (x != 0 || y != 0)
					simon->SetPosition(x, y);
			}
			simon->map->SetIsFall(false);
			simon->SetCameraAuto(0);
			simon->SetStateAuto(0);
			simon->Camera();
		}
		simon->map->Update();
		objects.clear();
		simon->map->GetUpdateObjects(&objects);
		objects.push_back(simon);
		//vector<LPGAMEOBJECT> coObjects;
		for (int i = 0; i < objects.size(); i++)
			coObjects.push_back(objects[i]);
		for (int i = 0; i < objects.size(); i++)
			objects[i]->Update(dt, &coObjects);
		break;
	}
}

/*
	Render a frame
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		DWORD now = GetTickCount();
		switch (screen)
		{
		case 0:
			game->Draw(0.0f, -40.0f, texture_title, 0, 0, 258, 225);
			break;
		case 1:
			if (now - Time_screen > 3000)
			{
				screen = 2;
				simon->map->SetIsNext(true);
				simon->map->SetNextScene(1);
				simon->SetStateAuto(0);
				simon->SetCameraAuto(0);
				simon->nx = 1;
			}
			blackboard->Render();
			if (now - Time_screen < 2100)
			{
				simon->vx = -SIMON_WALKING_SPEED / 2;
			}
			else
			{
				simon->SetState(SIMON_STATE_BEHIND);
			}
			simon->SetStateAuto(-1);
			simon->SetCameraAuto(-1);
			game->SetCamera(0, 0);
			game->Draw(0.0f, 0.0f, texture_intro, 0, 0, 256.0f, 185.0f);
			for (int i = 0; i < objects.size(); i++)
				objects[i]->Render();
			break;
		case 2:
			simon->map->Render();
			blackboard->Render();
			for (int i = 0; i < objects.size(); i++)
				objects[i]->Render();
			break;
		}

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			if (game->GetPause())
			{

				if (simon->GetStateAuto() == 0 && simon->GetCollusion() != 1)
					game->ProcessKeyboard();
				Update(dt);
			}
			DWORD now = GetTickCount();
			if (simon->GetState() == SIMON_STATE_UPDATE)
			{
				game->SetPause(false);
			}
			if (now - simon->GetFrameUpdate() > 1000)
			{
				game->SetPause(true);
			}
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}

