#include "BlackBoard.h"
#include "Game.h"


CBlackBoard::CBlackBoard()
{
	CTextures *textures = CTextures::GetInstance();
	textures->Add(ID_BLACKBOARD, BLACKBOARD_TEXTURE_PATH, D3DCOLOR_XRGB(255, 255, 255));
	texblackboard = textures->Get(ID_BLACKBOARD);
}

void CBlackBoard::Render()
{
	CGame *game = CGame::GetInstance();
	float cx, cy;
	game->GetCamera(cx, cy);

	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = 200;
	rect.bottom = 80;

	game->Draw(cx, -40.0f, texblackboard, 0, 0, 256, 40);
	game->GetFont()->DrawTextW(game->GetSpriteHandler(), L"SCORE- ", -1, &rect, DT_LEFT,
		D3DCOLOR_XRGB(255, 255, 255));

	game->GetFont()->DrawTextW(game->GetSpriteHandler(), L"\nPLAYER ", -1, &rect, DT_LEFT,
		D3DCOLOR_XRGB(255, 255, 255));

	game->GetFont()->DrawTextW(game->GetSpriteHandler(), L"\n\nENEMY ", -1, &rect, DT_EXPANDTABS,
		D3DCOLOR_XRGB(255, 255, 255));

	game->GetFont()->DrawTextW(game->GetSpriteHandler(), L"\t\t\tTIME ", -1, &rect, DT_EXPANDTABS,
		D3DCOLOR_XRGB(255, 255, 255));

	game->GetFont()->DrawTextW(game->GetSpriteHandler(), L"\t\t\t\t\tSTAGE ", -1, &rect, DT_EXPANDTABS,
		D3DCOLOR_XRGB(255, 255, 255));
}

