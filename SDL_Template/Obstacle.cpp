#include "Obstacle.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

Obstacle::Obstacle() {
	mBlockTexture = new GLTexture("BaseBlock.png");
	mBlockTexture->Scale(mBlockTexture->Scale() * 4.0f);
	mBlockTexture->Parent(this);
	mBlockTexture->Position(Vec2_Zero);

	AddCollider(new BoxCollider(mBlockTexture->ScaledDimensions()));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);
}
Obstacle::~Obstacle() {
	delete mBlockTexture;
	mBlockTexture = nullptr;
}

bool Obstacle::IgnoreCollisions() {
	return !Active();
}
void Obstacle::Hit(PhysEntity* other) {
	// empty
}

void Obstacle::Update() {
	// ???
}
void Obstacle::Render() {
	mBlockTexture->Render();
	PhysEntity::Render();
}