#include "CommonFunction.h"


bool checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    return SDL_HasIntersection(&a, &b);
}

//bool checkCollision(const SDL_Rect& a, const SDL_Rect& b)
//{
//	int leftA, rightA, topA, bottomA;
//	int leftB, rightB, topB, bottomB;
//
//	leftA = a.x;
//	rightA = a.x + a.w;
//	topA = a.y;
//	bottomA = a.y + a.h;
//
//	leftB = b.x;
//	rightB = b.x + b.w;
//	topB = b.y;
//	bottomB = b.y + b.h;
//
//	if (topB > bottomA) {
//        if (rightB - leftA > 0 && rightB - leftA < 10) return true;
//        if (rightA - leftB > 0 && rightA - leftB < 10) return true;
//        return false;
//	}
//
////	if (topA > bottomB) {
////        if (rightA - leftB > 0 && rightA - leftB < 10) return true;
////        if (rightB - leftA > 0 && rightB - leftA < 10) return true;
////        return false;
////	}
////    if (bottomA < topB)
////	{
////		return false;
////	}
//
////	if (topA > bottomB) {
////        if (rightA - leftB >= 0 && rightA - leftB < 4) return true;
////        if (leftA - rightB >= 0 && leftA - rightB < 4) return true;
////        return false;
////	}
////
//
//	if (topA > bottomB)
//	{
//		return false;
//	}
//
//	if (rightA < leftB)
//	{
//		return false;
//	}
//
//	else if (leftA > rightB)
//	{
//		return false;
//	}
//
//
//	return true;
//}

