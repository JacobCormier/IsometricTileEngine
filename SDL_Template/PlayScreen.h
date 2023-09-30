#ifndef __PLAYSCREEN_H
#define __PLAYSCREEN_H

#include "TileMap.h"
#include "Dungeon.h"

using namespace SDLFramework;

class PlayScreen : public GameEntity {
private:
	InputManager* mInput;

	//TileMap* mTileMap;
	Dungeon* mTestDungeon;



public:
	PlayScreen();
	~PlayScreen();

	void Update() override;
	void Render() override;

};
#endif