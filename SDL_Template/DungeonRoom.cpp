#include "DungeonRoom.h"

const float DungeonRoom::X_LEFT_BOUNDARY = 40.0f;
const float DungeonRoom::X_RIGHT_BOUNDARY = 1010.0f;
const float DungeonRoom::Y_TOP_BOUNDARY = 142.0f;
const float DungeonRoom::Y_BOTTOM_BOUNDARY = 656.0f;

DungeonRoom::DungeonRoom() {
	mInput = InputManager::Instance();

	mBackground = new GLTexture("BindingOfIsaacRoom.png");
	mBackground->Scale(mBackground->Scale() * 2.1f);
	mBackground->Parent(this);
	mBackground->Position(Vec2_Zero);

	CreateDoorTextures();

}
DungeonRoom::~DungeonRoom() {
	mInput = nullptr;

	delete mBackground;
	mBackground == nullptr;
}

void DungeonRoom::AddDoor(DungeonRoom::Direction direction, DungeonRoom* connectedRoom) {
	if (mDoors[direction] == nullptr) {
		mDoors[direction] = connectedRoom;
	}
	else {
		std::cout << "DungeonRoom::AddDoor() Error: already connected!" << std::endl;
	}
}
DungeonRoom* DungeonRoom::GetDoor(DungeonRoom::Direction direction) {
	if (mDoors[direction] != nullptr) {
		return mDoors[direction];
	}
	else {
		return nullptr;
	}
}

void DungeonRoom::Update() {
	// Updates entities within room
}
void DungeonRoom::Render() {
	// Render walls

	mBackground->Render();

	for (int i = 0; i <= (int)Direction::LEFT; i++) {
		if (mDoors[(Direction)i] != nullptr) {
			mDoorTextures[(Direction)i]->Render();
		}
	}
}

void DungeonRoom::CreateDoorTextures() {
	mDoors[Direction::NONE] = nullptr;
	mDoorTextures[Direction::NONE] = nullptr;
	for (int i = 0; i <= (int)Direction::LEFT; i++) {
		//If true, the door renders.
		// Would instead be nullptr if mDoors were set to a DungeonRoom*
		mDoors[(Direction)i] = nullptr;

		mDoorTextures[(Direction)i] = new GLTexture("DoorOpen.png");
		mDoorTextures[(Direction)i]->Scale(mDoorTextures[(Direction)i]->Scale() * 2.1f);
		mDoorTextures[(Direction)i]->Parent(this);
		//mDoorTextures[(Direction)i]->Position(Vector2((i * 30), (0.0f)));
	}

	mDoorTextures[Direction::UP]->Position(Vector2((0.0f), (-254.0f)));

	mDoorTextures[Direction::RIGHT]->Position(Vector2((420.0f), (0.0f)));
	mDoorTextures[Direction::RIGHT]->Rotate(90.0f);

	mDoorTextures[Direction::DOWN]->Position(Vector2((0.0f), (254.0f)));
	mDoorTextures[Direction::DOWN]->Rotate(180.0f);

	mDoorTextures[Direction::LEFT]->Position(Vector2((-420.0f), (0.0f)));
	mDoorTextures[Direction::LEFT]->Rotate(270.0f);
}