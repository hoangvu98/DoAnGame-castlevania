#include "BlackBoard.h "
#include "Game.h"
#include <string>
#include <string.h>
#include "Simon.h"
#include "BossBat.h"
#include "Dracula.h"
#include "SpiritDracula.h"
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
	CDracula *dracula = CDracula::GetInstance();
	CSpiritDracula *spiritdracula = CSpiritDracula::GetInstance();

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
	k = simon->GetHealth();
	if (k < 0) k = 0;
	else if (k > 16) k = 16;

	for (int i = 0; i <= k - 1; i++)
		simonHP[i].SetType(PLAYER);

	for (int i = k; i < 16; i++)
		simonHP[i].SetType(EMPTY);

	for (int i = 0; i < 16; i++)
		simonHP[i].Render(i * 6.0f + 32.0f, 10.0f);

	int n;
	if (simon->GetStage() <= 3)
		n = bossbat->GetHealth();
	else if (simon->GetStage() <= 18)
	{
		CSpiritDracula *spiritdracula = CSpiritDracula::GetInstance();
		n = dracula->GetHealth();
		if (dracula->GetState() == DRACULA_STATE_DIE)
			n = spiritdracula->GetHealth();
	}

	if (n < 0) n = 0;
	else if (n > 16) n = 16;

	for (int i = 0; i <= n - 1; i++)
		enemyHP[i].SetType(ENEMY);

	for (int i = n; i < 16; i++)
		enemyHP[i].SetType(EMPTY);

	for (int i = 0; i < (int)enemyHP.size(); i++)
		enemyHP[i].Render(i * 6.0f + 32.0f, 20.0f);

	CItems *item = simon->GetWeapon();
	if (item != NULL)
	{
		CGame *game = CGame::GetInstance();
		float cx, cy;
		game->GetCamera(cx, cy);
		item->animations[0]->Render(cx + ITEM_POSITION_X, ITEM_POSITION_Y - OFFSET);
	}

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

