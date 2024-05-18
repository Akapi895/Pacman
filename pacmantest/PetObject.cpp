#include "PetObject.h"
#include <algorithm>

PetObject::PetObject() {
	current_frame_ = 0;
	width_frame_   = 0;
	height_frame_  = 0;

	x_pos_ = 0;
	y_pos_ = 0;

	direction_current_ = GO_NONE;
	direction_auto_    = GO_NONE; //GO_RIGHT

	pet_number_ = 0;
}

void PetObject::setStartPet(SDL_Renderer* renderer, SDL_Color* colorKey) {
	current_frame_ = PET_FRAME_;

	x_pos_ = START_PET_X_ * PIXEL_CLIP_;
	y_pos_ = START_PET_Y_ * PIXEL_CLIP_;

	direction_current_ = GO_DOWN;
	direction_auto_ = GO_DOWN;

	loadImage("image//pet_" + to_string(pet_number_) + "_down.png", renderer, colorKey);
}

void PetObject::setPetNumber(const int petNumber) {
	pet_number_ = petNumber;
}

void PetObject::render(SDL_Renderer* renderer) {
	current_frame_++;

	if (current_frame_ >= PET_FRAME_)
		current_frame_ = 0;

	SDL_Rect posScreen = { x_pos_, y_pos_, width_frame_, height_frame_ };
	SDL_RenderCopy(renderer, texture_, &clip_rect_[current_frame_], &posScreen);
}

bool PetObject::loadImage(string path, SDL_Renderer* renderer, SDL_Color* colorKey) {
	bool success = BaseObject::loadImage(path, renderer, colorKey);

	if (success == true) {
		width_frame_ = rect_.w / PET_FRAME_;
		height_frame_ = rect_.h;
		setClips();
	}

	return success;
}

void PetObject::setClips() {
	for (int i = 0; i < PET_FRAME_; i++)
	{
		clip_rect_[i].x = width_frame_ * i;
		clip_rect_[i].y = 0;
		clip_rect_[i].w = width_frame_;
		clip_rect_[i].h = height_frame_;
	}
}

SDL_Rect PetObject::getRect() const {
	SDL_Rect posPet;
	posPet.x = x_pos_;
	posPet.y = y_pos_;
	posPet.h = height_frame_;
	posPet.w = width_frame_;
	return posPet;
}

void PetObject::updateImageDirect(SDL_Renderer* renderer) {
	if (direction_current_ == GO_DOWN)
		loadImage("image//pet_" + to_string(pet_number_) + "_down.png", renderer, &COLOR_KEY_BLACK_);
	else if (direction_current_ == GO_UP)
		loadImage("image//pet_" + to_string(pet_number_) + "_up.png", renderer, &COLOR_KEY_BLACK_);
	else if (direction_current_ == GO_LEFT)
		loadImage("image//pet_" + to_string(pet_number_) + "_left.png", renderer, &COLOR_KEY_BLACK_);
	else if (direction_current_ == GO_RIGHT)
		loadImage("image//pet_" + to_string(pet_number_) + "_right.png", renderer, &COLOR_KEY_BLACK_);
}

void PetObject::autoInputDirect(GameMap& checkMap) {
	vector<int> candidatesDir;
	if (direction_current_ != GO_LEFT) {
		x_pos_ += VEL_PACMAN_;
		if (!checkToMap(checkMap))
		{
			candidatesDir.push_back(GO_RIGHT);
		}
		x_pos_ -= VEL_PACMAN_;
	}

	if (direction_current_ != GO_RIGHT) {
		x_pos_ -= VEL_PACMAN_;
		if (!checkToMap(checkMap))
		{
			candidatesDir.push_back(GO_LEFT);
		}
		x_pos_ += VEL_PACMAN_;
	}

	if (direction_current_ != GO_UP) {
		y_pos_ += VEL_PACMAN_;
		if (!checkToMap(checkMap))
		{
			candidatesDir.push_back(GO_DOWN);
		}
		y_pos_ -= VEL_PACMAN_;

	}

	if (direction_current_ != GO_DOWN) {
		y_pos_ -= VEL_PACMAN_;
		if (!checkToMap(checkMap))
		{
			candidatesDir.push_back(GO_UP);
		}
		y_pos_ += VEL_PACMAN_;
	}

	if (candidatesDir.size() == 0) {
		switch (direction_current_) {
            case GO_UP: direction_auto_ = GO_DOWN; break;
            case GO_DOWN: direction_auto_ = GO_UP; break;
            case GO_RIGHT: direction_auto_ = GO_LEFT; break;
            case GO_LEFT: direction_auto_ = GO_RIGHT; break;
		}
	}
	else {
		int randomDirect = rand() % candidatesDir.size();
		direction_auto_ = candidatesDir[randomDirect];
	}
}


vector<pair<int, int>> PetObject::findShortestPathBFS(GameMap& checkMap, Map* checkTileNumber, vector<vector<int>>& map1, pair<int, int> startPos, pair<int, int> endPos) {
    int rows = map1.size();
    int cols = map1[0].size();

    // Khởi tạo biến visited để theo dõi các vị trí đã được khám phá
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    // Khởi tạo hàng đợi để lưu trữ các vị trí cần khám phá
    queue<pair<int, int>> q;
    q.push(startPos);

    // Khởi tạo biến parent để lưu trữ thông tin về vị trí cha của mỗi vị trí
    vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, {-1, -1}));

    // Duyệt tìm đường đi
    while (!q.empty()) {
        // Lấy vị trí hiện tại ra khỏi hàng đợi
        pair<int, int> currPos = q.front();
        q.pop();

        // Xác định vị trí x, y hiện tại
        int x = currPos.first;
        int y = currPos.second;

        // Kiểm tra xem vị trí hiện tại có phải là vị trí kết thúc hay không
        if (x == endPos.first && y == endPos.second) {
            // Tìm đường đi từ vị trí kết thúc về vị trí bắt đầu
            vector<pair<int, int>> path;
            pair<int, int> curr = endPos;
            while (curr != startPos) {
                path.push_back(curr);
                curr = parent[curr.first][curr.second];
            }
            path.push_back(startPos);
            reverse(path.begin(), path.end());
            return path;
        }

        // Duyệt qua các vị trí lân cận
        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};
        for (int i = 0; i < 4; ++i) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            // Kiểm tra xem vị trí lân cận có hợp lệ hay không
            if (checkToMap(checkMap, newX, newY) && !visited[newX][newY]) {
                // Đánh dấu vị trí lân cận là đã được khám phá
                visited[newX][newY] = true;

                // Lưu trữ thông tin vị trí cha
                parent[newX][newY] = {x, y};

                // Thêm vị trí lân cận vào hàng đợi
                q.push({newX, newY});
            }
        }
    }

    // Không tìm thấy đường đi
    return {};
}

int PetObject::getDirectionToPos(int targetX, int targetY) {
    int currentX = getRect().x;
    int currentY = getRect().y;

    int dx = targetX - currentX;
    int dy = targetY - currentY;

    if (dx == 0 && dy > 0) {
        return GO_UP;
    } else if (dx > 0 && dy == 0) {
        return GO_RIGHT;
    } else if (dx == 0 && dy < 0) {
        return GO_DOWN;
    } else if (dx < 0 && dy == 0) {
        return GO_LEFT;
    }
}

void PetObject::autoAiInputDirect(GameMap& checkMap, PacmanObject& pacman) {
//    // Get the ghost's current position
//    SDL_Rect ghostPos = getRect();
//
//    // Retrieve the map pointer
//    Map* checkTileNumber = checkMap.getMap();
//    vector<vector<int>> map1;
//    for (int i = 1; i <= 20; ++i) {
//        vector<int> tmp;
//        for (int j = 1; j <= 35; ++j) tmp.push_back(checkTileNumber->tiles_number_[i][j]);
//        map1.push_back(tmp);
//    }
//
//    // Find the shortest path to Pacman using BFS
//    vector<pair<int, int>> path = findShortestPathBFS(checkMap, checkTileNumber, map1, {ghostPos.x, ghostPos.y}, {pacman.getPos().x, pacman.getPos().y});

    SDL_Rect ghostPos = getRect();

    // Retrieve the map pointer
    Map* checkTileNumber = checkMap.getMap();
    vector<vector<int>> map1;
    for (int i = 1; i <= 20; ++i) {
        vector<int> tmp;
        for (int j = 1; j <= 35; ++j) tmp.push_back(checkTileNumber->tiles_number_[i][j]);
        map1.push_back(tmp);
    }

    // Find the shortest path to Pacman using Dijkstra
    vector<pair<int, int>> path = findShortestPathDijkstra(checkMap, checkTileNumber, map1, {ghostPos.x, ghostPos.y}, {pacman.getPos().x, pacman.getPos().y});

    // If a path is found, follow the next step in the path
    if (!path.empty()) {
        int nextX = path[0].first;
        int nextY = path[0].second;

        // Check if the next step is a valid move
        if (checkToMap(checkMap, nextX, nextY)) {
            // Update the ghost's direction based on the next step
            switch (getDirectionToPos(nextX, nextY)) {
                case GO_UP: direction_auto_ = GO_UP; break;
                case GO_DOWN: direction_auto_ = GO_DOWN; break;
                case GO_LEFT: direction_auto_ = GO_LEFT; break;
                case GO_RIGHT: direction_auto_ = GO_RIGHT; break;
            }

            // Remove the followed step from the path
            //path.erase(path.begin());
        }
    }
    return;
}


vector<pair<int, int>> PetObject::findShortestPathDijkstra(GameMap& checkMap, Map* checkTileNumber,
                                                           vector<vector<int>>& map1, pair<int, int> startPos, pair<int, int> endPos) {
    int rows = map1.size();
    int cols = map1[0].size();

    // Data structures for Dijkstra's algorithm
    vector<vector<int>> distance(rows, vector<int>(cols, numeric_limits<int>::max())); // Distances from start
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));// Visited nodes
//    vector<vector<bool>> visited(rows, vector<bool>(cols));
//    std::fill(visited.begin(), visited.end(), vector<bool>(cols, false));
    vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, {-1, -1}));

 // Parent nodes for path reconstruction

    // Priority queue for efficient exploration (sorted by distance)
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    distance[startPos.first][startPos.second] = 0; // Set starting distance to 0
    pq.push({0, startPos});

    // Dijkstra's algorithm loop
    while (!pq.empty()) {
      // Get node with the minimum distance
      pair<int, pair<int, int>> curr = pq.top();
      pq.pop();
      int currDist = curr.first;
      int currX = curr.second.first;
      int currY = curr.second.second;

      // Check if we reached the end goal
      if (currX == endPos.first && currY == endPos.second) {
        // Reconstruct path from end to start
        vector<pair<int, int>> path;
        pair<int, int> currNode = endPos;
        while (currNode != startPos) {
          path.push_back(currNode);
          currNode = parent[currNode.first][currNode.second];
        }
        path.push_back(startPos);
        reverse(path.begin(), path.end());
        return path;
      }

      // Mark current node as visited
      visited[currX][currY] = true;

      // Explore neighbors
      int dx[] = {-1, 0, 1, 0};
      int dy[] = {0, 1, 0, -1};
      for (int i = 0; i < 4; ++i) {
        int newX = currX + dx[i];
        int newY = currY + dy[i];

        // Check if neighbor is valid and not visited
        if (checkToMap(checkMap, newX, newY) && !visited[newX][newY]) {
          int newDist = currDist + getCost(map1[newX][newY]); // Calculate tentative distance

          // Update distance if new path is shorter
          if (newDist < distance[newX][newY]) {
            distance[newX][newY] = newDist;
            parent[newX][newY] = {currX, currY};
            pq.push({newDist, {newX, newY}}); // Add neighbor to priority queue with updated distance
          }
        }
      }
    }

    // No path found
    return {};
  }

int PetObject::getCost(int tileType) {
    // Example: Assign different costs for different tile types
    switch (tileType) {
      case 0: // Open space
        return 1;
      case 1: // Wall
        return numeric_limits<int>::max();
      case 2: // Water (high cost)
        return 5;
      default:
        return 3; // Default cost
    }
  }

//void PetObject::autoAiInputDirect(GameMap& checkMap, PacmanObject& pacman) {
//	map<int, int> candidatesGoType;
//	SDL_Rect pacmanPos = pacman.getPos();
//	//int distanceMin = (pacmanPos.x - x_pos_) * (pacmanPos.x - x_pos_) + (pacmanPos.y - y_pos_) * (pacmanPos.y - y_pos_);
//    if (direction_current_ != GO_UP)
//    {
//        y_pos_ += VEL_PACMAN_;
//        if (!checkToMap(checkMap))
//        {
//            int distance_ = (pacmanPos.x - x_pos_) * (pacmanPos.x - x_pos_) + (pacmanPos.y - y_pos_) * (pacmanPos.y - y_pos_);
////            candidatesGoType.insert({ distance_, GO_DOWN });
//            candidatesGoType[distance_] = GO_DOWN;
//        }
//        y_pos_ -= VEL_PACMAN_;
//    }
//
//	if (direction_current_ != GO_LEFT)
//	{
//		x_pos_ += VEL_PACMAN_;
//		if (!checkToMap(checkMap))
//		{
//			int distance_ = (pacmanPos.x - x_pos_) * (pacmanPos.x - x_pos_) + (pacmanPos.y - y_pos_) * (pacmanPos.y - y_pos_);
////			candidatesGoType.insert({ distance_, GO_RIGHT });
//			candidatesGoType[distance_] = GO_RIGHT;
//		}
//		x_pos_ -= VEL_PACMAN_;
//	}
//
//	if (direction_current_ != GO_RIGHT)
//	{
//		x_pos_ -= VEL_PACMAN_;
//		if (!checkToMap(checkMap))
//		{
//			int distance_ = (pacmanPos.x - x_pos_) * (pacmanPos.x - x_pos_) + (pacmanPos.y - y_pos_) * (pacmanPos.y - y_pos_);
////			candidatesGoType.insert({ distance_, GO_LEFT });
//			candidatesGoType[distance_] = GO_LEFT;
//		}
//		x_pos_ += VEL_PACMAN_;
//	}
//
//	if (direction_current_ != GO_DOWN)
//	{
//		y_pos_ -= VEL_PACMAN_;
//		if (!checkToMap(checkMap))
//		{
//			int distance_ = (pacmanPos.x - x_pos_) * (pacmanPos.x - x_pos_) + (pacmanPos.y - y_pos_) * (pacmanPos.y - y_pos_);
////			candidatesGoType.insert({ distance_, GO_UP });
//			candidatesGoType[distance_] = GO_UP;
//		}
//		y_pos_ += VEL_PACMAN_;
//	}
//
//	if (candidatesGoType.size() == 0)
//	{
//		switch (direction_current_)
//		{
//            case GO_UP: direction_auto_ = GO_DOWN; break;
//            case GO_DOWN: direction_auto_ = GO_UP; break;
//            case GO_RIGHT: direction_auto_ = GO_LEFT; break;
//            case GO_LEFT: direction_auto_ = GO_RIGHT; break;
//		}
//	}
//	else
//	{
//		for (auto i : candidatesGoType)
//		{
//			direction_auto_ = i.second;
//			break;
//		}
//	}
//}

void PetObject::setDirection(GameMap& checkMap, SDL_Renderer* renderer) {
	if (x_pos_ % TILE_SIZE != 0 || y_pos_ % TILE_SIZE != 0)
	{
		return;
	}

	if (direction_current_ != GO_DOWN && direction_auto_ == GO_DOWN)
	{
		y_pos_ += VEL_PACMAN_;
		if (!checkToMap(checkMap))
		{
			direction_current_ = GO_DOWN;
			updateImageDirect(renderer);
		}
		y_pos_ -= VEL_PACMAN_;
		return;
	}
	if (direction_current_ != GO_UP && direction_auto_ == GO_UP)
	{
		y_pos_ -= VEL_PACMAN_;
		if (!checkToMap(checkMap))
		{
			direction_current_ = GO_UP;
			updateImageDirect(renderer);
		}
		y_pos_ += VEL_PACMAN_;
		return;
	}
	if (direction_current_ != GO_LEFT && direction_auto_ == GO_LEFT)
	{
		x_pos_ -= VEL_PACMAN_;
		if (!checkToMap(checkMap))
		{
			direction_current_ = GO_LEFT;
			updateImageDirect(renderer);
		}
		x_pos_ += VEL_PACMAN_;
		return;
	}
	if (direction_current_ != GO_RIGHT && direction_auto_ == GO_RIGHT)
	{
		x_pos_ += VEL_PACMAN_;
		if (!checkToMap(checkMap))
		{
			direction_current_ = GO_RIGHT;
			updateImageDirect(renderer);
		}
		x_pos_ -= VEL_PACMAN_;
		return;
	}
}


void PetObject::petMove(GameMap& checkMap) {
	if (direction_current_ == GO_DOWN)
	{
		y_pos_ += VEL_PACMAN_;
		if (checkToMap(checkMap))
			y_pos_ -= VEL_PACMAN_;
	}
	if (direction_current_ == GO_LEFT)
	{
		x_pos_ -= VEL_PACMAN_;
		if (checkToMap(checkMap))
			x_pos_ += VEL_PACMAN_;
	}
	if (direction_current_ == GO_RIGHT)
	{
		x_pos_ += VEL_PACMAN_;
		if (checkToMap(checkMap))
			x_pos_ -= VEL_PACMAN_;
	}
	if (direction_current_ == GO_UP)
	{
		y_pos_ -= VEL_PACMAN_;
		if (checkToMap(checkMap))
			y_pos_ += VEL_PACMAN_;
	}
}

bool PetObject::checkToMap(GameMap& checkMap)
{
	int xPosImage1 = x_pos_ / TILE_SIZE;
	int yPosImage1 = y_pos_ / TILE_SIZE;

	int xPosImage2 = (x_pos_ + TILE_SIZE - 1) / TILE_SIZE;
	int yPosImage2 = y_pos_ / TILE_SIZE;

	int xPosImage3 = x_pos_ / TILE_SIZE;
	int yPosImage3 = (y_pos_ + TILE_SIZE - 1) / TILE_SIZE;

	int xPosImage4 = (x_pos_ + TILE_SIZE - 1) / TILE_SIZE;
	int yPosImage4 = (y_pos_ + TILE_SIZE - 1) / TILE_SIZE;

	Map* checkTileNumber = checkMap.getMap();

	if (checkTileNumber->tiles_number_[yPosImage1][xPosImage1] == TILE_WALL_
		|| checkTileNumber->tiles_number_[yPosImage2][xPosImage2] == TILE_WALL_
		|| checkTileNumber->tiles_number_[yPosImage3][xPosImage3] == TILE_WALL_
		|| checkTileNumber->tiles_number_[yPosImage4][xPosImage4] == TILE_WALL_
		|| checkTileNumber->tiles_number_[yPosImage1][xPosImage1] == TILE_WALL_2_
		|| checkTileNumber->tiles_number_[yPosImage2][xPosImage2] == TILE_WALL_2_
		|| checkTileNumber->tiles_number_[yPosImage3][xPosImage3] == TILE_WALL_2_
		|| checkTileNumber->tiles_number_[yPosImage4][xPosImage4] == TILE_WALL_2_)
	{
		return true;
	}

	return false;
}

bool PetObject::checkToMap(GameMap& checkMap, int newx, int newy)
{
	int xPosImage1 = newx / TILE_SIZE;
	int yPosImage1 = newy / TILE_SIZE;

	int xPosImage2 = (newx + TILE_SIZE - 1) / TILE_SIZE;
	int yPosImage2 = newy / TILE_SIZE;

	int xPosImage3 = newx / TILE_SIZE;
	int yPosImage3 = (newy + TILE_SIZE - 1) / TILE_SIZE;

	int xPosImage4 = (newx + TILE_SIZE - 1) / TILE_SIZE;
	int yPosImage4 = (newy + TILE_SIZE - 1) / TILE_SIZE;

	Map* checkTileNumber = checkMap.getMap();

	if (checkTileNumber->tiles_number_[yPosImage1][xPosImage1] == TILE_WALL_
		|| checkTileNumber->tiles_number_[yPosImage2][xPosImage2] == TILE_WALL_
		|| checkTileNumber->tiles_number_[yPosImage3][xPosImage3] == TILE_WALL_
		|| checkTileNumber->tiles_number_[yPosImage4][xPosImage4] == TILE_WALL_
		|| checkTileNumber->tiles_number_[yPosImage1][xPosImage1] == TILE_WALL_2_
		|| checkTileNumber->tiles_number_[yPosImage2][xPosImage2] == TILE_WALL_2_
		|| checkTileNumber->tiles_number_[yPosImage3][xPosImage3] == TILE_WALL_2_
		|| checkTileNumber->tiles_number_[yPosImage4][xPosImage4] == TILE_WALL_2_)
	{
		return true;
	}

	return false;
}




