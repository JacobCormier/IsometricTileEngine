#include "Tile.h"

int Tile::sTilesCreated = 0;

// PUBLIC FUNCTIONS

Tile::Tile() {
	sTilesCreated++;
	
	mInput = InputManager::Instance();
	
	mOnTileEntity = nullptr;
	mCurrentState = TileState::DEFAULT;

	CreateTileTextures();
}
Tile::~Tile() {

	if (mOnTileEntity != nullptr) {
		delete mOnTileEntity;
		mOnTileEntity = nullptr;
	}

	DeleteTileTextures();

	mInput = nullptr;
}

int Tile::GetTilesCreatedNumber() {
	return sTilesCreated;
}
void Tile::ResetTileCreatedCount() {
	sTilesCreated = 0;
}

void Tile::PlaceEntityOnTile(GameEntity* entity) {
	if (mOnTileEntity == nullptr) {
		mOnTileEntity = entity;
		mOnTileEntity->Parent(this);
		mOnTileEntity->Position(Vector2((0.0f), (-32.0f)));
	}
	else {
		// Code for if entity can't be placed here
	}
}

void Tile::Update() {
	// Update GameEntity
	if (mOnTileEntity != nullptr) {
		mOnTileEntity->Update();
	}
	else {	
		if (
		(mInput->MousePosition().x >= Position().x - 15) &&
		(mInput->MousePosition().x <= Position().x + 15) &&
		(mInput->MousePosition().y >= Position().y - 30) &&
		(mInput->MousePosition().y <= Position().y + 0)) {			
			
			if (mCurrentState == TileState::DEFAULT) {
				mCurrentState = TileState::ALT;
			}
			if (mCurrentState == TileState::WATER) {
				mCurrentState = TileState::SELECTED;
			}

			if (mInput->MouseButtonPressed(InputManager::MouseButton::Left)) {
				PlaceEntityOnTile(new Tile());			
				if (mCurrentState == TileState::ALT) {
					mCurrentState = TileState::DEFAULT;
				}
				if (mCurrentState == TileState::SELECTED) {
					mCurrentState = TileState::WATER;
				}
			}
			else if (mInput->MouseButtonPressed(InputManager::MouseButton::Right)) {
				TileState test = mCurrentState;
				if (mCurrentState == TileState::ALT || mCurrentState == TileState::DEFAULT) {
					mCurrentState = TileState::WATER;
				}
				else if (mCurrentState == TileState::WATER || mCurrentState == TileState::SELECTED) {
					mCurrentState = TileState::DEFAULT;
				}

			}

		}
		else {
			if (mCurrentState == TileState::ALT) {
				mCurrentState = TileState::DEFAULT;
			}
			if (mCurrentState == TileState::SELECTED) {
				mCurrentState = TileState::WATER;
			}
		}
	}
}
void Tile::Render() {
	mTileTextures[mCurrentState]->Render();

	if (mOnTileEntity != nullptr) {
		mOnTileEntity->Render();
	}
}

// PRIVATE FUNCTIONS
void Tile::CreateTileTextures() {
	mTileTextures[TileState::DEFAULT] = new GLTexture("Tile.png");
	mTileTextures[TileState::DEFAULT]->Scale(mTileTextures[TileState::DEFAULT]->Scale() * 4.0f);
	mTileTextures[TileState::DEFAULT]->Parent(this);
	mTileTextures[TileState::DEFAULT]->Position(Vec2_Zero);

	mTileTextures[TileState::ALT] = new GLTexture("TileAlt.png");
	mTileTextures[TileState::ALT]->Scale(mTileTextures[TileState::ALT]->Scale() * 4.0f);
	mTileTextures[TileState::ALT]->Parent(this);
	mTileTextures[TileState::ALT]->Position(Vec2_Zero);

	mTileTextures[TileState::SELECTED] = new GLTexture("HighlightTile.png");
	mTileTextures[TileState::SELECTED]->Scale(mTileTextures[TileState::SELECTED]->Scale() * 4.0f);
	mTileTextures[TileState::SELECTED]->Parent(this);
	mTileTextures[TileState::SELECTED]->Position(Vec2_Zero);

	mTileTextures[TileState::WATER] = new GLTexture("WaterTile.png");
	mTileTextures[TileState::WATER]->Scale(mTileTextures[TileState::WATER]->Scale() * 4.0f);
	mTileTextures[TileState::WATER]->Parent(this);
	mTileTextures[TileState::WATER]->Position(Vec2_Zero);
}
void Tile::DeleteTileTextures() {
	delete mTileTextures[TileState::DEFAULT];
	mTileTextures[TileState::DEFAULT] = nullptr;

	delete mTileTextures[TileState::ALT];
	mTileTextures[TileState::ALT] = nullptr;

	delete mTileTextures[TileState::SELECTED];
	mTileTextures[TileState::SELECTED] = nullptr;

	delete mTileTextures[TileState::WATER];
	mTileTextures[TileState::WATER] = nullptr;

	mTileTextures.clear();
}