#include "GameMap.h"

void GameMap::loadMap(string nameMap)
{
	ifstream inFile(nameMap);
	for (int i = 0; i < MAX_MAP_Y; i++)
	{
		for (int j = 0; j < MAX_MAP_X; j++)
		{
			int numberTile;
			inFile >> numberTile;
			game_map_.tiles_number_[i][j] = numberTile;
			if (numberTile != 0 && numberTile != 9 && numberTile != 5)
			{
				number_items_++;
			}
		}
	}
	game_map_.start_x_ = 0;
	game_map_.start_y_ = 0;

	game_map_.max_x_ = MAX_MAP_X * TILE_SIZE;
	game_map_.max_y_ = MAX_MAP_Y * TILE_SIZE;

	game_map_.file_name_ = nameMap;
	inFile.close();
}

void GameMap::loadTiles(SDL_Renderer* renderer)
{
	for (int i = 0; i < MAP_TILES_IMAGE_; i++)
	{
		string fileNameImage = "map//0" + to_string(i) + ".png";
		tiles_image_[i].loadImage(fileNameImage, renderer);
	}
}

void GameMap::drawMap(SDL_Renderer* renderer)
{
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	int mapX = 0;
	int mapY = 0;

	for (int i = 0; i < MAX_MAP_Y; i++)
	{
		for (int j = 0; j < MAX_MAP_X; j++)
		{
			int numberTile = game_map_.tiles_number_[i][j];

			if (numberTile > 0)
			{
				tiles_image_[numberTile].setRect(j * TILE_SIZE, i * TILE_SIZE);
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
