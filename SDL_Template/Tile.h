#ifndef __TILE_H_
#define __TILE_H_

#include "GameEntity.h"
#include "GLTexture.h"
#include "InputManager.h"
#include <map>

using namespace SDLFramework;

class Tile : public GameEntity {
private:
	static int sTilesCreated;

	enum class TileState { DEFAULT, ALT, SELECTED, WATER };
	TileState mCurrentState;
	std::map<TileState, GLTexture*> mTileTextures;

	GameEntity* mOnTileEntity;

	InputManager* mInput;
public:
	Tile();
	~Tile();

	static int GetTilesCreatedNumber();
	static void ResetTileCreatedCount();

	// Just a start
	void PlaceEntityOnTile(GameEntity* entity);

	void Update() override;
	void Render() override;
private:
	void CreateTileTextures();
	void DeleteTileTextures();
};

#endif //__TILE_H_