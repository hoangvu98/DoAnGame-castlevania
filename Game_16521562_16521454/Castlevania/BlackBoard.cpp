#include "BlackBoard.h "
#include "Game.h"
#include <string>
#include <string.h>
#include "Simon.h"
#include "BossBat.h"

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
	for (int i = 0; i < 16; i++)
		enemyHP.push_back(CHeal(ENEMY));
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
	CBossBat *bossbat = CBossBat::GetInstance();

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

	wstring texttime = L"\t\tTIME ";
	ConversionToString(simon->GetTime(), L"0000", texttime);

	wstring textlive = L"\n\n\t\t\t\t  P - ";
	ConversionToString(simon->GetLive(), L"00", textlive);

	game->Draw(cx, -40.0f, texblackboard, 0, 0, 256, 40);

	game->GetFont()->DrawTextW(game->GetSpriteHandler(), textscore.c_str(), -1, &rect, DT_LEFT,
		D3DCOLOR_XRGB(255, 255, 255));

	game->GetFont()->DrawTextW(game->GetSpriteHandler(), L"\nPLAYER ", -1, &rect, DT_LEFT,
		D3DCOLOR_XRGB(255, 255, 255));

	int k;
	int j;
	if (simon->GetReset() == true)
	{
		k = -1;
		for (int i = 0; i < 16; i++)
			simonHP[i].SetType(PLAYER);
	}
	else
	{
	
		for (int i = 0; i < 16; i++)
			simonHP[i].Render(i * 6.0f + 32.0f, 10.0f/* - 40.0f*/);

		if (simon->GetHealth() >= 0)
			k = simonHP.size() - simon->GetHealth();

		
		if (k >= 0)
			for (j = simonHP.size() - 1; j >= 16 - k; j--)
				simonHP[j].SetType(EMPTY);

		for (int i = 0; i < enemyHP.size(); i++)
			enemyHP[i].Render(i * 6.0f + 32.0f, 20.0f);
	}
	int n;
	if (bossbat->GetHealth() >= 0)
		n = enemyHP.size() - bossbat->GetHealth();
	if (n >= 0)
		for (j = enemyHP.size() - 1; j >= enemyHP.size() - n; j--)
			enemyHP[j].SetType(EMPTY);

	game->GetFont()->DrawTextW(game->GetSpriteHandler(), textheart.c_str(), -1, &rect, DT_EXPANDTABS,
		D3DCOLOR_XRGB(255, 255, 255));

	game->GetFont()->DrawTextW(game->GetSpriteHandler(), L"\n\nENEMY ", -1, &rect, DT_LEFT,
		D3DCOLOR_XRGB(255, 255, 255));

	game->GetFont()->DrawTextW(game->GetSpriteHandler(), texttime.c_str(), -1, &rect, DT_EXPANDTABS,
		D3DCOLOR_XRGB(255, 255, 255));

	game->GetFont()->DrawTextW(game->GetSpriteHandler(), textstage.c_str(), -1, &rect, DT_EXPANDTABS,
		D3DCOLOR_XRGB(255, 255, 255));

	game->GetFont()->DrawTextW(game->GetSpriteHandler(), textlive.c_str(), -1, &rect, DT_EXPANDTABS,
		D3DCOLOR_XRGB(255, 255, 255));
}

