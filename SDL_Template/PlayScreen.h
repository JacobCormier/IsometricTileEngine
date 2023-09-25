#ifndef __PLAYSCREEN_H
#define __PLAYSCREEN_H

#include "Tile.h"

using namespace SDLFramework;

class PlayScreen : public GameEntity {
private:
	Tile* mTile;

public:
	PlayScreen();
	~PlayScreen();

	void Update() override;
	void Render() override;

};
#endif