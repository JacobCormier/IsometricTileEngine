#ifndef __TUNNEL_H
#define __TUNNEL_H

#include "TunnelBlock.h"
#include "Obstacle.h"
#include "Random.h"

using namespace SDLFramework;

class Tunnel : public GameEntity {
private:
	enum class TunnelDirection {RANDOM = -1, UP, DOWN};

	// Used in Initializer, required in .H file
	static const int MAX_BLOCKS = 16;

	static const int SPACING_TUNNEL_BLOCKS;
	static const int MIN_TUNNEL_BLOCKS;
	static const int MAX_TUNNEL_BLOCKS;
	static const float RANDOM_LOWER_HEIGHT_LIMIT;
	static const float RANDOM_UPPER_HEIGHT_LIMIT;
	static const float OBSTACLE_RANGE;

	static const int SHRINK_LIMIT;
	static const float UPPER_LIMIT_START;
	static const float LOWER_LIMIT_START;
	static float sUpperLimit;
	static float sLowerLimit;


	static const int TUNNEL_SPEED = -600.0f;

	Timer* mTimer;
	Random* mRand;

	float mShrinkTimer;

	TunnelBlock* mTunnelBlocks[MAX_BLOCKS];
	float mCurrentSectionLength;
	float mCurrentSectionHeight;

	Obstacle* mObstacleBlocks[2];

	std::vector<GLTexture*> mSmokeTrail;

public:

	Tunnel();
	~Tunnel();

	void NewGame();
	void AddSmokeTrail(Vector2 playerPosition);
	void ClearSmokeTrail();

	void Update();
	void Render();
private:
	void ClearBlocks();

	void HandleBlocks();
	void AddNewBlock();
	
	Vector2 GetNextBlockPosition();
	void SetTunnelRandomness(TunnelDirection direction = TunnelDirection::RANDOM);

	void ShrinkTunnel();
};

#endif //__TUNNEL_H
