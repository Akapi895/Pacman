#include "CommonFunction.h"

bool checkCollision(const SDL_Rect& a, const SDL_Rect& b)
{
	int leftA, rightA, topA, bottomA;
	int leftB, rightB, topB, bottomB;

	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;


//	if (topA > bottomB) {
//        if (rightA - leftB >= 4) return false;
//        else if (leftA - rightB >= 4) return false;
//        else return true;
//	}
//
//	if (topB > bottomA) {
//        if (rightB - leftA >= 4) return false;
//        else if (leftB - rightA >= 4) return false;
//        else return true;
//	}

	if (bottomA < topB)
	{
		return false;
	}

	if (topA > bottomB)
	{
		return false;
	}

	if (rightA < leftB)
	{
		return false;
	}

	else if (leftA > rightB)
	{
		return false;
	}


	return true;
}
