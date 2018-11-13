#include "Door.h"

void CDoor::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + DOOR_WIDTH;
	bottom = y + DOOR_HEIGHT;
}

void CDoor::Render()
{
}
