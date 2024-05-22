#include "PetObjectASTAR.h"

int dd_x[] = {-1, +0, +1, +0};
int dd_y[] = {+0, +1, +0, -1};

bool isCellValid(int row, int col)
{
	return ((row >= 0) && (row < ROW) && (col >= 0) && (col < COL));
}

bool isUnBlocked(int grid[][COL], int row, int col)
{
	if (grid[row][col] == 0 || grid[row][col] == 8)
		return (true);
	else
		return (false);
}

bool isDestination(int row, int col, pair<int, int> dest)
{
	if (row == dest.first && col == dest.second)
		return (true);
	else
		return (false);
}

int calculateHValue(int row, int col, pair<int, int> dest)
{
	return abs(row - dest.first) + abs(col - dest.second);
}

pair<int, int> tracePath(cell cellDetails[][COL], pair<int, int> dest)
{
	int row = dest.first;
	int col = dest.second;

	stack<pair<int, int>> Path;

	while (!(cellDetails[row][col].parent_i == row
			&& cellDetails[row][col].parent_j == col)) {
		Path.push(make_pair(row, col));
		int temp_row = cellDetails[row][col].parent_i;
		int temp_col = cellDetails[row][col].parent_j;
		row = temp_row;
		col = temp_col;
	}

	Path.push(make_pair(row, col));
	int cnt = 2;
	while (!Path.empty() && cnt) {
		pair<int, int> p = Path.top();
		Path.pop();

		if (cnt == 1) return p;
		cnt--;
	}

	return make_pair(0, 0);
}

pair<int, int> aStarSearch(int grid[][COL], pair<int, int> src, pair<int, int> dest)
{
	if (isCellValid(src.first, src.second) == false) {
		return make_pair(0, 0);
	}

	if (isCellValid(dest.first, dest.second) == false) {
		return make_pair(0, 0);
	}

	if (isUnBlocked(grid, src.first, src.second) == false
		|| isUnBlocked(grid, dest.first, dest.second)
			== false) {
		return make_pair(0, 0);
	}

	if (isDestination(src.first, src.second, dest)
		== true) {
		return make_pair(0, 0);
	}
	bool closedList[ROW][COL];
	memset(closedList, false, sizeof(closedList));

	cell cellDetails[ROW][COL];

	int i, j;

	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			cellDetails[i][j].f = FLT_MAX;
			cellDetails[i][j].g = FLT_MAX;
			cellDetails[i][j].h = FLT_MAX;
			cellDetails[i][j].parent_i = -1;
			cellDetails[i][j].parent_j = -1;
		}
	}

	i = src.first, j = src.second;
	cellDetails[i][j].f = 0.0;
	cellDetails[i][j].g = 0.0;
	cellDetails[i][j].h = 0.0;
	cellDetails[i][j].parent_i = i;
	cellDetails[i][j].parent_j = j;

	set<pair<double, pair<int, int> >> openList;

	openList.insert(make_pair(0.0, make_pair(i, j)));

	bool foundDest = false;

	while (!openList.empty()) {
		pair<double, pair<int, int> > p = *openList.begin();

		openList.erase(openList.begin());

		i = p.second.first;
		j = p.second.second;
		closedList[i][j] = true;

		double gNew, hNew, fNew;

		if (isCellValid(i - 1, j) == true) {
			if (isDestination(i - 1, j, dest) == true) {
				// Set the Parent of the destination cell
				cellDetails[i - 1][j].parent_i = i;
				cellDetails[i - 1][j].parent_j = j;

				pair<int, int> ans = tracePath(cellDetails, dest);
				foundDest = true;
				return ans;
			}
			else if (closedList[i - 1][j] == false
					&& isUnBlocked(grid, i - 1, j) == true) {
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i - 1, j, dest);
				fNew = gNew + hNew;

				if (cellDetails[i - 1][j].f == FLT_MAX
					|| cellDetails[i - 1][j].f > fNew) {
					openList.insert(make_pair(
						fNew, make_pair(i - 1, j)));

					// Update the details of this cell
					cellDetails[i - 1][j].f = fNew;
					cellDetails[i - 1][j].g = gNew;
					cellDetails[i - 1][j].h = hNew;
					cellDetails[i - 1][j].parent_i = i;
					cellDetails[i - 1][j].parent_j = j;
				}
			}
		}

		if (isCellValid(i + 1, j) == true) {
			if (isDestination(i + 1, j, dest) == true) {
				// Set the Parent of the destination cell
				cellDetails[i + 1][j].parent_i = i;
				cellDetails[i + 1][j].parent_j = j;

				pair<int, int> ans = tracePath(cellDetails, dest);
				foundDest = true;
				return ans;
			}

			else if (closedList[i + 1][j] == false
					&& isUnBlocked(grid, i + 1, j)
							== true) {
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i + 1, j, dest);
				fNew = gNew + hNew;

				if (cellDetails[i + 1][j].f == FLT_MAX
					|| cellDetails[i + 1][j].f > fNew) {
					openList.insert(make_pair(
						fNew, make_pair(i + 1, j)));
					// Update the details of this cell
					cellDetails[i + 1][j].f = fNew;
					cellDetails[i + 1][j].g = gNew;
					cellDetails[i + 1][j].h = hNew;
					cellDetails[i + 1][j].parent_i = i;
					cellDetails[i + 1][j].parent_j = j;
				}
			}
		}

		if (isCellValid(i, j + 1) == true) {
			// If the destination cell is the same as the
			// current successor
			if (isDestination(i, j + 1, dest) == true) {
				// Set the Parent of the destination cell
				cellDetails[i][j + 1].parent_i = i;
				cellDetails[i][j + 1].parent_j = j;

				pair<int, int> ans = tracePath(cellDetails, dest);
				foundDest = true;
				return ans;
			}

			else if (closedList[i][j + 1] == false
					&& isUnBlocked(grid, i, j + 1)
							== true) {
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i, j + 1, dest);
				fNew = gNew + hNew;

				if (cellDetails[i][j + 1].f == FLT_MAX
					|| cellDetails[i][j + 1].f > fNew) {
					openList.insert(make_pair(
						fNew, make_pair(i, j + 1)));

					// Update the details of this cell
					cellDetails[i][j + 1].f = fNew;
					cellDetails[i][j + 1].g = gNew;
					cellDetails[i][j + 1].h = hNew;
					cellDetails[i][j + 1].parent_i = i;
					cellDetails[i][j + 1].parent_j = j;
				}
			}
		}

		if (isCellValid(i, j - 1) == true) {
			if (isDestination(i, j - 1, dest) == true) {
				// Set the Parent of the destination cell
				cellDetails[i][j - 1].parent_i = i;
				cellDetails[i][j - 1].parent_j = j;

				pair<int, int> ans = tracePath(cellDetails, dest);
				foundDest = true;
				return ans;
			}

			else if (closedList[i][j - 1] == false
					&& isUnBlocked(grid, i, j - 1)
							== true) {
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i, j - 1, dest);
				fNew = gNew + hNew;

				if (cellDetails[i][j - 1].f == FLT_MAX
					|| cellDetails[i][j - 1].f > fNew) {
					openList.insert(make_pair(
						fNew, make_pair(i, j - 1)));

					// Update the details of this cell
					cellDetails[i][j - 1].f = fNew;
					cellDetails[i][j - 1].g = gNew;
					cellDetails[i][j - 1].h = hNew;
					cellDetails[i][j - 1].parent_i = i;
					cellDetails[i][j - 1].parent_j = j;
				}
			}
		}

	}
	return make_pair(0, 0);
}

int WhichDirection(pair<int, int> src, pair<int, int> des) {
    for (int i = 0; i < 4; ++i) {
        int x = src.first + dd_x[i];
        int y = src.second + dd_y[i];
        if (x == des.first && y == des.second) {
            switch (i) {
            case 0:
                return GO_UP;
            case 1:
                GO_RIGHT;
            case 2:
                GO_DOWN;
            case 3:
                return GO_LEFT;
            }
        }
        return GO_RIGHT;
    }
}

int findDirectionFrom(int grid[][35], pair<int, int> src, pair<int, int> des) {
    pair<int, int> ans = aStarSearch(grid, src, des);
	return WhichDirection(src, ans);
}
