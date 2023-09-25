#ifndef __BLOCK_H
#define __BLOCK_H
#include "GLTexture.h"
#include "PhysEntity.h"
#include "Timer.h"

using namespace SDLFramework;

class Block : public PhysEntity {
private:
	Timer* mTimer;

	GLTexture* mBlockTexture;

public:
	Block();
	// constructor for obstacle blocks
	// different texture & Size
	~Block();

	bool IgnoreCollisions() override;
	void Hit(PhysEntity* other) override;

	void Update() override;
	void Render() override;
};
#endif