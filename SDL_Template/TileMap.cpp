#include "TileMap.h"
int TileMap::sTileCount = 0;

TileMap::TileMap() {
	for (int i = 0; i < TILE_MAP_SIZE; i++) {
		for (int j = 0; j < TILE_MAP_SIZE; j++) {
				mTileMap[i][j] = new Tile();
				mTileMap[i][j]->Parent(this);
				mTileMap[i][j]->Position(Vector2(((i * -TILE_MOVE_X) + (j * TILE_MOVE_X)), ((i * TILE_MOVE_Y) + (j * TILE_MOVE_Y))));
		}
	}
}
TileMap::~TileMap() {
	for (int i = 0; i < TILE_MAP_SIZE; i++) {
		for (int j = 0; j < TILE_MAP_SIZE; j++) {
			delete mTileMap[i][j];
			mTileMap[i][j] = nullptr;
		}
	}
}

void TileMap::Update() {
	 std::cout << "Tile Count! " << sTileCount << std::endl;
	for (int i = 0; i < TILE_MAP_SIZE; i++) {
		for (int j = 0; j < TILE_MAP_SIZE; j++) {
			if (mTileMap[i][j] != nullptr) {
				mTileMap[i][j]->Update();
			}
		}
	}
	sTileCount = Tile::GetTilesCreatedNumber();
}
void TileMap::Render() {
	for (int i = 0; i < TILE_MAP_SIZE; i++) {
		for (int j = 0; j < TILE_MAP_SIZE; j++) {
			if (mTileMap[i][j] != nullptr) {
				mTileMap[i][j]->Render();
			}
		}
	}
}