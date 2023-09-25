#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mInput = InputManager::Instance();

	mTileMap = new TileMap();
	mTileMap->Parent(this);
	mTileMap->Position(Vector2(Vec2_Zero));
}
PlayScreen::~PlayScreen() {
	delete mTileMap;
	mTileMap = nullptr;

	mInput = nullptr;
}

void PlayScreen::Update() {
	mTileMap->Update();

	if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE)) {
		delete mTileMap;
		Tile::ResetTileCreatedCount();
		mTileMap = new TileMap();
		mTileMap->Parent(this);
		mTileMap->Position(Vec2_Zero);
	}
}
void PlayScreen::Render() {
	mTileMap->Render();
}
