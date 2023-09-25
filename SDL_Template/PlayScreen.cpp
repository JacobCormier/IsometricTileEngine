#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mTileMap = new TileMap();
	mTileMap->Parent(this);
	mTileMap->Position(Vector2(Vec2_Zero));
}
PlayScreen::~PlayScreen() {
	delete mTileMap;
	mTileMap = nullptr;
}

void PlayScreen::Update() {

}
void PlayScreen::Render() {
	mTileMap->Render();
}
