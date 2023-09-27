#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mInput = InputManager::Instance();






	mTileMap = new TileMap();
	mTileMap->Parent(this);
	mTileMap->Position(Vector2(Vec2_Zero));

	//mTestRoom = new DungeonRoom();
	//mTestRoom->Parent(this);
	//mTestRoom->Position(Vec2_Zero);
}
PlayScreen::~PlayScreen() {
	delete mTileMap;
	mTileMap = nullptr;

	//delete mTestRoom;
	//mTestRoom = nullptr;

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
	//mTestRoom->Render();
}
