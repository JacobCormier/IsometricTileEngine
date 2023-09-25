#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mTile = new Tile();
	mTile->Parent(this);
	mTile->Position(Vec2_Zero);
}
PlayScreen::~PlayScreen() {
	delete mTile;
	mTile = nullptr;
}

void PlayScreen::Update() {

}
void PlayScreen::Render() {
	mTile->Render();
}
