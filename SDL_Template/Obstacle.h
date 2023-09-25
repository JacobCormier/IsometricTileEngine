#ifndef __OBSTACLE_H_
#define __OBSTACLE_H_

#include "GLTexture.h"
#include "PhysEntity.h"
#include "Timer.h"

using namespace SDLFramework;

class Obstacle : public PhysEntity {
private:
	GLTexture* mBlockTexture;
public:
	Obstacle();
	~Obstacle();

	bool IgnoreCollisions() override;
	void Hit(PhysEntity* other) override;

	void Update() override;
	void Render() override;
};


#endif //__OBSTACLE_H_
