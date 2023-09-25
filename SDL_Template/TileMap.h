#ifndef __TILE_MAP_H_
#define __TILE_MAP_H_

#include "Tile.h"

class TileMap : public GameEntity {
private:
	static const int TILE_MAP_SIZE = 10;

	static const int TILE_MOVE_X = 32;
	//static const int TILE_MOVE_X = 8;
	static const int TILE_MOVE_Y = 16;
	//static const int TILE_MOVE_Y = 4;

	Tile* mTileMap[TILE_MAP_SIZE][TILE_MAP_SIZE];
public:
	TileMap();
	~TileMap();

	void Update() override;
	void Render() override;
};

#endif //__TILE_MAP_H_