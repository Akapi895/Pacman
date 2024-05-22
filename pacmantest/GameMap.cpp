#include "GameMap.h"

void GameMap::loadMap(string nameMap) {
    ifstream file(nameMap);
    if (!file.is_open()) {
        return;
    }

    game_map_.tiles_number_.resize(MAX_MAP_Y, std::vector<int>(MAX_MAP_X));
    number_items_ = 0;
    for (int i = 0; i < MAX_MAP_Y; ++i) {
        for (int j = 0; j < MAX_MAP_X; ++j) {
            int numberTile;
            file >> numberTile;
            game_map_.tiles_number_[i][j] = numberTile;
            if (numberTile != 0 && numberTile != 9 && numberTile != 5) {
                number_items_++;
            }
        }
    }

    // Calculate map dimensions
    game_map_.max_x = MAX_MAP_X * TILE_SIZE;
    game_map_.max_y = MAX_MAP_Y * TILE_SIZE;

	game_map_.file_name_ = nameMap;
	file.close();
}

void GameMap::loadTiles(SDL_Renderer* renderer) {
    for (int i = 0; i < MAP_TILES_IMAGE_; i++) {
        std::string fileNameImage = "map//0" + std::to_string(i) + ".png";
        tiles_image_[i].loadImage(fileNameImage, renderer);
    }
}

void GameMap::drawMap(SDL_Renderer* renderer) {
    for (int i = 0; i < MAX_MAP_Y; ++i) {
        for (int j = 0; j < MAX_MAP_X; ++j) {
            int numberTile = game_map_.tiles_number_[i][j];
            if (numberTile > 0) {
                int tileX = j * TILE_SIZE;
                int tileY = i * TILE_SIZE;

                tiles_image_[numberTile].setRect(tileX, tileY);
                tiles_image_[numberTile].render(renderer);
            }
        }
    }
}

int GameMap::getNumberItems() const
{
	return number_items_;
}

Map* GameMap::getMap()
{
	return &game_map_;
}

void GameMap::setMap(const Map& mapData)
{
	game_map_ = mapData;
}
