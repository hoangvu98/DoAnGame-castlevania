#include "Brick.h"



CBrick::CBrick()
{
	AddAnimation(17000);
	AddAnimation(17001);
	del = 0;
}

void CBrick::Render()
{
	if (state == BRICK_STATE_FULL)
		animations[BRICK_ANI_FULL]->Render(x, y);
	else if (state == BRICK_STATE_HALF)
		animations[BRICK_ANI_HALF]->Render(x, y + 16.0f);
}

void CBrick::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BRICK_BBOX_WIDTH;
	bottom = y + BRICK_BBOX_HEIGHT;

}