#include "Dungeon.h"

Dungeon::Dungeon() {
	mInput = InputManager::Instance();
	mCurrentRoom = nullptr;

	for (int i = 0; i < DUNGEON_ROWS; i++) {
		for (int j = 0; j < DUNGEON_COLUMNS; j++) {
			if (mDungeonLayout[i][j] == 0) {
				mDungeonMap[i][j] == nullptr;
			}
			else {
				mDungeonMap[i][j] = new DungeonRoom();
				mDungeonMap[i][j]->Parent(this);
				mDungeonMap[i][j]->Position(Vec2_Zero);
			}
		}
	}
	CreateDoorConnections();

	mCurrentRoom = mDungeonMap[0][0];

}
Dungeon::~Dungeon() {
	for (int i = 0; i < DUNGEON_ROWS; i++) {
		for (int j = 0; j < DUNGEON_COLUMNS; j++) {
			delete mDungeonMap[i][j];
			mDungeonMap[i][j] = nullptr;
		}
	}
	mCurrentRoom = nullptr;

	mInput = nullptr;
}

void Dungeon::Update() {

	if (mInput->KeyPressed(SDL_SCANCODE_UP)) {
		MoveToRoom(DungeonRoom::Direction::UP);
	}
	if (mInput->KeyPressed(SDL_SCANCODE_DOWN)) {
		MoveToRoom(DungeonRoom::Direction::DOWN);
	}
	if (mInput->KeyPressed(SDL_SCANCODE_LEFT)) {
		MoveToRoom(DungeonRoom::Direction::LEFT);
	}
	if (mInput->KeyPressed(SDL_SCANCODE_RIGHT)) {
		MoveToRoom(DungeonRoom::Direction::RIGHT);
	}

	mCurrentRoom->Update();

}
void Dungeon::Render() {
	mCurrentRoom->Render();
}

void Dungeon::CreateDoorConnections() {
	
	for (int i = 0; i < DUNGEON_ROWS; i++) {
		for (int j = 0; j < DUNGEON_COLUMNS; j++) {
			if (mDungeonMap[i][j] != nullptr) {
				if (i > 0 && mDungeonMap[i - 1][j] != nullptr) {
					mDungeonMap[i][j]->AddDoor(DungeonRoom::Direction::UP, mDungeonMap[i - 1][j]);
				}
				if (i < DUNGEON_ROWS - 1  && mDungeonMap[i + 1][j] != nullptr) {
					mDungeonMap[i][j]->AddDoor(DungeonRoom::Direction::DOWN, mDungeonMap[i + 1][j]);
				}
				if (j > 0 && mDungeonMap[i][j - 1] != nullptr) {
					mDungeonMap[i][j]->AddDoor(DungeonRoom::Direction::LEFT, mDungeonMap[i][j - 1]);
				}
				if (j < DUNGEON_COLUMNS - 1 && mDungeonMap[i][j + 1] != nullptr) {
					mDungeonMap[i][j]->AddDoor(DungeonRoom::Direction::RIGHT, mDungeonMap[i][j + 1]);
				}
			}
		}
	}

}
void Dungeon::MoveToRoom(DungeonRoom::Direction direction) {
	if (mCurrentRoom->GetDoor(direction) != nullptr) {
		mCurrentRoom = mCurrentRoom->GetDoor(direction);
	}
}