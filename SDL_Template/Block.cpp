#include "Block.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

Block::Block(){
	mTimer = Timer::Instance();

	mBlockTexture = new GLTexture("NewBlock.png", true);
	mBlockTexture->Scale(mBlockTexture->Scale() * 4.0f);
	mBlockTexture->Parent(this);
	mBlockTexture->Position(Vec2_Zero);

	AddCollider(new BoxCollider(mBlockTexture->ScaledDimensions()));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);
}
Block::~Block(){
	delete mBlockTexture;
	mBlockTexture = nullptr; 

	mTimer = nullptr; 

}

bool Block::IgnoreCollisions() {
	return false;
}
void Block::Hit(PhysEntity* other) {
}

void Block::Update() {
}
void Block::Render() {
	mBlockTexture->Render();
	PhysEntity::Render();
}