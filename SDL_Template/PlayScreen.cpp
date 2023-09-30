#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mInput = InputManager::Instance();






	//mTileMap = new TileMap();
	//mTileMap->Parent(this);
	//mTileMap->Position(Vector2(Vec2_Zero));

	mTestDungeon = new Dungeon();
	mTestDungeon->Parent(this);
	mTestDungeon->Position(Vec2_Zero);
}
PlayScreen::~PlayScreen() {
	//delete mTileMap;
	//mTileMap = nullptr;

	delete mTestDungeon;
	mTestDungeon = nullptr;

	mInput = nullptr;
}

void PlayScreen::Update() {
	
	mTestDungeon->Update();
	
	//mTileMap->Update();

	//if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE)) {
	//	delete mTileMap;
	//	Tile::ResetTileCreatedCount();
	//	mTileMap = new TileMap();
	//	mTileMap->Parent(this);
	//	mTileMap->Position(Vec2_Zero);
	//}
}
void PlayScreen::Render() {
	//mTileMap->Render();
	mTestDungeon->Render();
}
