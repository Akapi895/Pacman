#ifndef A_STAR_
#define A_STAR_

#define ROW 20
#define COL 35

#include "CommonFunction.h"
#include <stack>
#include <float.h>
#include <set>

struct cell {
	int parent_i, parent_j;
	double f, g, h;
};

bool isCellValid(int row, int col);

bool isUnBlocked(int grid[][COL], int row, int col);

bool isDestination(int row, int col, pair<int, int> dest);

int calculateHValue(int row, int col, pair<int, int> dest);

pair<int, int> tracePath(cell cellDetails[][COL], pair<int, int> dest);

pair<int, int> aStarSearch(int grid[][COL], pair<int, int> src, pair<int, int> dest);

int WhichDirection(pair<int, int> src, pair<int, int> des);

int findDirectionFrom(int grid[][35], pair<int, int> src, pair<int, int> des);

#endif // A_STAR_


