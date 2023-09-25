#ifndef __TILE_H_
#define __TILE_H_

#include "GameEntity.h"
#include "GLTexture.h"

using namespace SDLFramework;

class Tile : public GameEntity {
private:

	GLTexture* mTileTexture;

	GameEntity* mOnTileEntity;

	// pointer to GameEntity?
public:
	Tile();
	~Tile();

	void Update() override;
	void Render() override;
private:
};

#endif //__TILE_H_