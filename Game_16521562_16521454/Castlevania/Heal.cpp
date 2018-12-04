#include "Heal.h"
#include "Game.h"


CHeal::CHeal(int type)
{
	this->type = type;
	CTextures *textures = CTextures::GetInstance();
	textures->Add(ID_HEAL, HEAL_TEXTURE_PATH, D3DCOLOR_XRGB(0, 0, 0));
	texheal = textures->Get(ID_HEAL);
}

void CHeal::Render(float x, float y)
{
	CGame *game = CGame::GetInstance();
	float cx, cy;
	game->GetCamera(cx, cy);
	switch (type)
	{
	case PLAYER:
		game->Draw(cx + x, -OFFSET + y, texheal, 0, 0, 5, 10);
		break;
	case ENEMY:
		game->Draw(cx + x, -OFFSET + y, texheal, 14, 0, 19, 10);
		break;
	case EMPTY:
		game->Draw(cx + x, -OFFSET + y, texheal, 8, 0, 12, 10);
		break;
	}
}

