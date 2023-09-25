#ifndef __PLAYER_H
#define __PLAYER_H
#include "AnimatedGLTexture.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "PhysEntity.h"
#include "Random.h"

using namespace SDLFramework;

class Player : public PhysEntity {
private:
	// This variable is only programmed to be 2, used in initialization
	static const int DEATH_TEXTURES_LIMIT = 2;

	static const float GRAVITY;
	static const float LIFT_STRENGTH;

	static const float LIFT_LIMIT;
	static const float FALL_LIMIT;

	static const float RESPAWN_TIME;

	static const float DEATH_CIRCLE_SIZE;
	static const float DEATH_CIRCLE_TIME;
	static const float DEATH_SMOKE_LIMIT;

	float mVelocity;
	float mRespawnTimer;

	bool mIsRising;
	bool mIsDead;
	bool mIsReadyForRespawn;

	Timer * mTimer;
	InputManager * mInput;
	AudioManager * mAudio;
	Random* mRand;

	GLTexture* mPlayerDeathTexture;
	AnimatedGLTexture* mAnimatedPlayerTexture;
	GLTexture* mDeathFireTextures[DEATH_TEXTURES_LIMIT];
	GLTexture* mDeathSmokeTextures[DEATH_TEXTURES_LIMIT];

	float mDeathCircleTimer;
	GLTexture* mDeathCircle;
private:
	
public:
	Player();
	~Player();

	bool IsDead();
	bool ReadyForRespawn();

	// Inherited from PhysEntity
	bool IgnoreCollisions() override;
	void Hit(PhysEntity * other) override;

	void Reset();
	void PlayerTilt();
	
	void Update() override;
	void Render() override;
private:
	void DeathSmokeReset(GLTexture* deathSmoke);
};
#endif