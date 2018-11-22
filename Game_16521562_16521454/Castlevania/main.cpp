

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
#include "InputImage.h"
using namespace std;

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"Castlevania"

#define BRICK_TEXTURE_PATH L"brick.png"
#define SIMON_TEXTURE_PATH L"castlevania_texture\\Simon\\Simon.png"
#define BBOX_TEXTURE_PATH L"bbox.png"
#define CANDLE_TEXTURE_PATH L"castlevania_texture\\Weapon\\Candle.png"
#define TITLE_SCREEN_PATH L"castlevania_texture\\Background\\Title Screen.png"
#define INTRO_SCREEN_PATH L"castlevania_texture\\Background\\Intro Screen.png"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 224

#define MAX_FRAME_RATE 120

#define ID_SIMON			2
#define ID_BRICK			3
#define ID_GHOUL			4
#define ID_BAT				5
#define ID_TITLE_SCREEN		7
#define ID_INTRO_SCREEN		8
CGame *game;
CSimon *simon;
CBrick *brick;
CGhoul *ghoul;
CBat *bat;
CMap *map1;

vector<LPGAMEOBJECT> objects;
CHidenObject *hidenObject;
CEntranceLevel *level_1;
LPDIRECT3DTEXTURE9 texture_title;
LPDIRECT3DTEXTURE9 texture_intro;
int screen = 1;
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
		if (simon->GetStair() == 1)
		{
			simon->state_auto = 1;
		}
		break;
	case DIK_RETURN:
		screen = 2;
		break;
	case DIK_D:
		if (simon->GetFight() == false)
		{
			if (!game->IsKeyDown(DIK_DOWN) && simon->GetJump() == true)
			{
				simon->SetState(SIMON_STATE_JUMP);
				simon->SetJump(false);
			}
		}
		break;
	case DIK_DOWN:
		if (simon->GetStair() == 3)
		{
			simon->state_auto = 1;
		}
		else if (simon->GetStair() != 2)
		{
			float tx, ty;
			simon->GetPosition(tx, ty);
			simon->SetPosition(tx, ty - 5);
		}
		break;
	case DIK_F:
		DWORD t = GetTickCount() - simon->GetWhip()->GetFrameWhip();
		if (t >= 450)
		{
			if (game->IsKeyDown(DIK_UP) && t >= 450)
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
					if (game->IsKeyDown(DIK_LEFT) || game->IsKeyDown(DIK_RIGHT))
						simon->SetState(SIMON_STATE_IDLE);
					if (game->IsKeyDown(DIK_DOWN))
						simon->SetState(SIMON_STATE_KNEE);
				}
				else
					simon->SetState(SIMON_STATE_IDLE);
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
		if (simon->GetStair() == 3)
		{
		}
		else if (simon->GetStair() != 2)
		{
			float tx, ty;
			simon->GetPosition(tx, ty);
			simon->SetPosition(tx, ty - 4);
			simon->SetState(SIMON_STATE_IDLE);
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
				if (now - simon->GetFrameStair() > 400)
				{
					if (simon->IsUp == 2)
					{
						simon->IsUp = 0;
						simon->SetStair(0);
					}
					if (simon->IsDown == 2)
					{
						simon->IsDown = 0;
						simon->SetStair(0);
					}
					if (game->IsKeyDown(DIK_UP) || game->IsKeyDown(DIK_RIGHT))
					{
						if (simon->IsUp == 1)
						{
							simon->IsUp = 2;
						}
						if (simon->IsDown == 1)
						{
							simon->IsDown = 0;
						}
						simon->SetState(SIMON_STATE_STAIR);
						simon->nx = 1;
						simon->SetFrameStair();
						simon->GetPosition(simon->simon_x, simon->simon_y);
					}
					else if (game->IsKeyDown(DIK_DOWN) || game->IsKeyDown(DIK_LEFT))
					{
						if (simon->IsDown == 1)
						{
							simon->IsDown = 2;
						}
						if (simon->IsUp == 1)
						{
							simon->IsUp = 0;
						}
						simon->SetState(SIMON_STATE_STAIR);
						simon->nx = -1;
						simon->SetFrameStair();
						simon->GetPosition(simon->simon_x, simon->simon_y);
					}
					else
					{
						simon->SetState(SIMON_STATE_IDLE);
					}
				}
			}
		}
	}
	else
	{
		if (simon->GetJump() != false)
		{
			if (!simon->GetSkill())
			{
				if (simon->GetFight() == false)
				{
					if (game->IsKeyDown(DIK_DOWN) && simon->GetStair() != 3)
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
	texture->Add(ID_SIMON, SIMON_TEXTURE_PATH, D3DCOLOR_XRGB(0, 128, 128));
	texture->Add(ID_BRICK, BBOX_TEXTURE_PATH, D3DCOLOR_XRGB(237, 28, 36));
	texture->Add(ID_BBOX, BBOX_TEXTURE_PATH, D3DCOLOR_XRGB(0, 128, 128));
	texture->Add(ID_CANDLE, CANDLE_TEXTURE_PATH, D3DCOLOR_XRGB(34, 177, 76));
	texture->Add(ID_ITEM, ITEM_TEXTURE_PATH, D3DCOLOR_XRGB(128, 0, 0));
	texture->Add(ID_TITLE_SCREEN, TITLE_SCREEN_PATH, D3DCOLOR_XRGB(255, 255, 255));
	texture->Add(ID_INTRO_SCREEN, INTRO_SCREEN_PATH, D3DCOLOR_XRGB(255, 255, 255));

	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();


	LPDIRECT3DTEXTURE9 texsimon = texture->Get(ID_SIMON);
	LPANIMATION ani;




	ifstream in("Data\\Simon.txt");
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
	in.close();

	simon = new CSimon();
	simon->AddAnimation(101);
	simon->AddAnimation(102);
	simon->AddAnimation(201);
	simon->AddAnimation(202);
	simon->AddAnimation(301);
	simon->AddAnimation(302);
	simon->AddAnimation(401);
	simon->AddAnimation(402);
	simon->AddAnimation(501);
	simon->AddAnimation(502);
	simon->AddAnimation(601);
	simon->AddAnimation(602);
	simon->AddAnimation(603);
	simon->AddAnimation(604);
	simon->AddAnimation(605);
	simon->AddAnimation(606);
	//simon->SetPosition(10.0f, 80.0f); 
	simon->SetPosition(615.0f, 80.0f);
	//simon->SetState(SIMON_STATE_IDLE);

	texture_title = texture->Get(ID_TITLE_SCREEN);
	texture_intro = texture->Get(ID_INTRO_SCREEN);
	/*LPDIRECT3DTEXTURE9 texbrick = texture->Get(ID_BRICK);

	sprites->Add(20011, 0, 0, 15, 15, texbrick);
	ani = new CAnimation(100);
	ani->Add(20011);
	animations->Add(601, ani);

	for (int i = 0; i < 30; i++)
	{
		brick = new CBrick();
		brick->AddAnimation(601);
		brick->SetPosition(i * 15, 150.0f);
		objects.push_back(brick);
	}*/

	/*hidenObject = new CHidenObject();
	hidenObject->SetPosition(0.0f, 146.0f);
	hidenObject->SetSize(769.0f, 15.0f);
	objects.push_back(hidenObject);

	LPDIRECT3DTEXTURE9 texcandle = texture->Get(ID_CANDLE);
	in.open("Data\\Candle.txt");
	AddAnimation(in, sprites, ani, texcandle, 2);
	in.close();
	animations->Add(701, ani);


	CCandle *candle = new CCandle();
	candle->AddAnimation(701);
	candle->SetPosition(80.0f, 113.0f);
	candle->SetState(CANDLE_STATE_NORMAL);
	objects.push_back(candle);*/



	/*texture->Add(ID_MAP_LEVEL1, MAP_LEVEL1_TEXTURE_PATH, D3DCOLOR_XRGB(255, 255, 255));
	LPDIRECT3DTEXTURE9 texmap = texture->Get(ID_MAP_LEVEL1);
	sprites->Add(20001, 0, 0, 768, 184, texmap);
	ani = new CAnimation(100);
	ani->Add(20001);
	animations->Add(801, ani);

	map1 = new CMap();
	map1->AddAnimation(801);
	map1->SetPosition(0.0f, 0.0f);*/

	//LPDIRECT3DTEXTURE9 texfishman = texture->Get(ID_FISHMAN);
	//AddAnimation(in_fish, sprites, ani, texfishman, 1);//fire left
	//animations->Add(601, ani);
	//AddAnimation(in_fish, sprites, ani, texfishman, 1);//jump left
	//animations->Add(701, ani);
	//AddAnimation(in_fish, sprites, ani, texfishman, 2);//walk left
	//animations->Add(801, ani);
	//AddAnimation(in_fish, sprites, ani, texfishman, 1);//fire right
	//animations->Add(901, ani);
	//AddAnimation(in_fish, sprites, ani, texfishman, 1);//jump right
	//animations->Add(1001, ani);
	//AddAnimation(in_fish, sprites, ani, texfishman, 2);//walk right
	//animations->Add(1101, ani);
	//in_fish.close();
	//fishman = new CFishman();
	//fishman->AddAnimation(601);
	//fishman->AddAnimation(701);
	//fishman->AddAnimation(801);
	//fishman->AddAnimation(901);
	//fishman->AddAnimation(1001);
	//fishman->AddAnimation(1101);
	//fishman->SetPosition(100.f, 170.f);
	//fishman->SetState(FISHMAN_STATE_JUMP);
	//objects.push_back(fishman);

	level_1 = CEntranceLevel::GetInstance();
	level_1->SetScene(SCENE_1);
	level_1->LoadMap();
	objects = level_1->GetUpdateObjects();
	objects.push_back(simon);
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
	case 2:
		level_1->Update();
		vector<LPGAMEOBJECT> coObjects;
		objects.clear();
		objects = level_1->GetUpdateObjects();
		objects.push_back(simon);

		for (int i = 0; i < objects.size() - 1; i++)
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
		switch (screen)
		{
		case 1:
			game->Draw(0, 0, texture_title, 0, 0, 258, 225);
			break;
		case 2:
			level_1->Render();
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
				if (simon->state_auto == 0)
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

