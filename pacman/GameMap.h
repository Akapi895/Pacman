#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include "CommonFunction.h"
#include "BaseObject.h"

#define MAP_TILES_IMAGE_ 10

struct Map
{
	int start_x_ = 0;
	int start_y_ = 0;

	int max_x_ = 0;
	int max_y_ = 0;
	int tiles_number_[MAX_MAP_Y][MAX_MAP_X];
	string file_name_ = "";

};

class TileMap : public BaseObject
{
public:
	TileMap() { ; }
	~TileMap() { ; }

private:

};

class GameMap
{
public:
	void loadMap(string nameMap);
	void loadTiles(SDL_Renderer* renderer);
	void drawMap(SDL_Renderer* renderer);

	int getNumberItems() const;

	Map* getMap();
	void setMap(const Map& mapData);
private:
	Map game_map_;
	TileMap tiles_image_[MAP_TILES_IMAGE_];

	int number_items_ = 0;
};
#endif // !GAME_MAP_H_
