#include "Tile.h"

int Tile::sTileCount = 0;

Tile::Tile() {
	sTileCount++;

	mTileTexture = new GLTexture("Tile.png");
	mTileTexture->Scale(mTileTexture->Scale() * 4.0f);
	mTileTexture->Parent(this);
	mTileTexture->Position(Vec2_Zero);
}
Tile::~Tile() {
	delete mTileTexture;
	mTileTexture = nullptr;
}

void Tile::Update() {
	// Update GameEntity
}
void Tile::Render() {
	mTileTexture->Render();
}