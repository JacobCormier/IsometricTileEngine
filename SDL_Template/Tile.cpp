#include "Tile.h"



Tile::Tile() {
	mOnTileEntity = nullptr;

	mTileTexture = new GLTexture("Tile.png");
	mTileTexture->Scale(mTileTexture->Scale() * 4.0f);
	mTileTexture->Parent(this);
	mTileTexture->Position(Vec2_Zero);
}
Tile::~Tile() {
	delete mTileTexture;
	mTileTexture = nullptr;

	if (mOnTileEntity != nullptr) {
		delete mOnTileEntity;
		mOnTileEntity = nullptr;
	}
}

void Tile::Update() {
	// Update GameEntity
	if (mOnTileEntity != nullptr) {
		mOnTileEntity->Update();
	}
}
void Tile::Render() {
	mTileTexture->Render();

	if (mOnTileEntity != nullptr) {
		mOnTileEntity->Render();
	}
}