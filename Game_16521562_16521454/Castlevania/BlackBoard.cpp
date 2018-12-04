#include "BlackBoard.h "
#include "Game.h"
#include <string>
#include <string.h>
#include "Simon.h"
void CBlackBoard::ConversionToString(long number, wstring strFormat, wstring & text)
{
	wstring tmp;
	tmp.append(to_wstring(number));

	strFormat.replace(strFormat.length() - tmp.length(), tmp.length(), tmp);

	text.append(strFormat);
}

void CBlackBoard::ConversionToString(int number, wstring strFormat, wstring & text)
{
	wstring tmp;
	tmp.append(to_wstring(number));

	strFormat.replace(strFormat.length() - tmp.length(), tmp.length(), tmp);

	text.append(strFormat);
}

CBlackBoard::CBlackBoard()
{
	CTextures *textures = CTextures::GetInstance();
	textures->Add(ID_BLACKBOARD, BLACKBOARD_TEXTURE_PATH, D3DCOLOR_XRGB(255, 255, 255));
	texblackboard = textures->Get(ID_BLACKBOARD);

	/*simonHP = new CHeal(PLAYER);*/
	for (int i = 0; i < 16; i++)
		simonHP.push_back(CHeal(PLAYER));
}

void CBlackBoard::Render()
{
	CGame *game = CGame::GetInstance();
	float cx, cy;
	game->GetCamera(cx, cy);

	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = 256;
	rect.bottom = 80;

	CSimon *simon = CSimon::GetInstance();

	/*wstring strtmp;
	strtmp.append(to_wstring(simon->GetScore()));

	wstring strscore = L"000000";
	strscore.replace(strscore.length() - strtmp.length(), strtmp.length(), strtmp);*/
	wstring textscore = L"SCORE - ";
	ConversionToString(simon->GetScore(), L"000000", textscore);

	wstring textheart = L"\n\t\t\t\t    - ";
	ConversionToString(simon->GetHeart(), L"00", textheart);

	wstring textstage = L"\t\t\t\tSTAGE ";
	ConversionToString(simon->GetStage(), L"00", textstage);

	game->Draw(cx, -40.0f, texblackboard, 0, 0, 256, 40);

	game->GetFont()->DrawTextW(game->GetSpriteHandler(), textscore.c_str(), -1, &rect, DT_LEFT,
		D3DCOLOR_XRGB(255, 255, 255));

	game->GetFont()->DrawTextW(game->GetSpriteHandler(), L"\nPLAYER ", -1, &rect, DT_LEFT,
		D3DCOLOR_XRGB(255, 255, 255));

	/*simonHP->Render(32.0f, 10.0f - 40.0f);*/
	for (int i = 0; i < simonHP.size(); i++)
		simonHP[i].Render(i * 6.0f + 32.0f, 10.0f/* - 40.0f*/);
	int k = simonHP.size() - simon->GetHealth();

	int j;
	if (k != 0)
		for (j = simonHP.size() - 1; j >= simonHP.size() - k; j--)
			simonHP[j].SetType(EMPTY);
	/*DebugOut(L"k = %d\n", k);*/

	game->GetFont()->DrawTextW(game->GetSpriteHandler(), textheart.c_str(), -1, &rect, DT_EXPANDTABS,
		D3DCOLOR_XRGB(255, 255, 255));

	game->GetFont()->DrawTextW(game->GetSpriteHandler(), L"\n\nENEMY ", -1, &rect, DT_LEFT,
		D3DCOLOR_XRGB(255, 255, 255));

	game->GetFont()->DrawTextW(game->GetSpriteHandler(), L"\t\tTIME ", -1, &rect, DT_EXPANDTABS,
		D3DCOLOR_XRGB(255, 255, 255));

	game->GetFont()->DrawTextW(game->GetSpriteHandler(), textstage.c_str(), -1, &rect, DT_EXPANDTABS,
		D3DCOLOR_XRGB(255, 255, 255));
}

