#ifndef __TILE_H_
#define __TILE_H_

#include "GameEntity.h"
#include "GLTexture.h"

using namespace SDLFramework;

class Tile : public GameEntity {
private:
	static int sTileCount;
	GLTexture* mTileTexture;

	// pointer to GameEntity?
public:
	Tile();
	~Tile();

	void Update() override;
	void Render() override;
private:
};

#endif //__TILE_H_