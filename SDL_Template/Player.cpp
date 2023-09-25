#include "Player.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

const float Player::GRAVITY = 35.0f;
const float Player::LIFT_STRENGTH = -80.0f;

const float Player::LIFT_LIMIT = -500.0f;
const float Player::FALL_LIMIT = 700.0f;

const float Player::RESPAWN_TIME = 2.0f;

const float Player::DEATH_CIRCLE_SIZE = 50.0f;
const float Player::DEATH_CIRCLE_TIME = 0.01f;
const float Player::DEATH_SMOKE_LIMIT = 78.0f;

Player::Player() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();
	mRand = Random::Instance();

	mPlayerDeathTexture = new GLTexture("PlayerDeath.png");
	mPlayerDeathTexture->Scale(mPlayerDeathTexture->Scale() * 4.0f);
	mPlayerDeathTexture->Parent(this);
	mPlayerDeathTexture->Position(Vec2_Zero);

	mAnimatedPlayerTexture = new AnimatedGLTexture(
		"Player.png", // File Name
		0, // X Value
		0, // Y Value
		39, // Width
		18, // Height
		6, // Frame Count
		0.6f, // Animation Duration
		Animation::Layouts::Horizontal, // Tiling Direction
		true); // Managed Bool

	mAnimatedPlayerTexture->Scale(mAnimatedPlayerTexture->Scale() * 4.0f);
	mAnimatedPlayerTexture->Parent(this);
	mAnimatedPlayerTexture->Position(Vec2_Zero);

	for (int i = 0; i < DEATH_TEXTURES_LIMIT; i++) {
		mDeathFireTextures[i] = new GLTexture("Fire.png");
		mDeathFireTextures[i]->Scale(mDeathFireTextures[i]->Scale() * 4.0f);
		mDeathFireTextures[i]->Parent(this);
		mDeathSmokeTextures[i] = new GLTexture("Smoke.png");
		mDeathSmokeTextures[i]->Scale(mDeathSmokeTextures[i]->Scale() * 3.0f);
		mDeathSmokeTextures[i]->Parent(this);
	}

	mDeathCircle = new GLTexture("PlayerDeathCircle.png");
	// Scaled in Reset()
	mDeathCircle->Parent(this);
	mDeathCircle->Position(Vec2_Zero);

	Reset();

	// Tail Collider
	AddCollider(new BoxCollider(Vector2( 150.0f, 20.0f)), Vector2( (0.0f), (-15.0f)));
	// Body Collider
	AddCollider(new BoxCollider(Vector2(  70.0f, 30.0f)), Vector2((23.0f), ( 15.0f)));
	// Rotor Collider
	AddCollider(new BoxCollider(Vector2(  90.0f, 50.0f)), Vector2((12.0f),  (-8.0f)));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);

}
Player::~Player() {
	mTimer = nullptr;
	mInput = nullptr;
	mAudio = nullptr;
	mRand = nullptr;

	delete mPlayerDeathTexture;
	mPlayerDeathTexture = nullptr;
	delete mAnimatedPlayerTexture;
	mAnimatedPlayerTexture = nullptr;

	for (int i = 0; i < DEATH_TEXTURES_LIMIT; i++) {
		delete mDeathFireTextures[i];
		mDeathFireTextures[i] = nullptr;
		delete mDeathSmokeTextures[i];
		mDeathSmokeTextures[i] = nullptr;
	}

	delete mDeathCircle;
	mDeathCircle = nullptr;
}

bool Player::IsDead() {
	return mIsDead;
}
bool Player::ReadyForRespawn() {
	return mIsReadyForRespawn;
}

bool Player::IgnoreCollisions() {
	return !Active();
}
void Player::Hit(PhysEntity * other) {
	mIsDead = true;
}

void Player::Reset() {
	Active(false);
	mVelocity = 0.0f;
	mRespawnTimer = 0.0f;
	mDeathCircleTimer = 0.0f;
	mIsRising = false;
	mIsDead = false;
	mIsReadyForRespawn = false;

	mDeathCircle->Scale(Vector2(DEATH_CIRCLE_SIZE, DEATH_CIRCLE_SIZE));
	mDeathCircle->Rotation(0.0f);
}
void Player::PlayerTilt() {
	if (mIsRising) {
		Rotation(-5.0f); 
	}
	else {
		Rotation(0.0f);
	}
}

void Player::Update() {
	
	if (mIsDead) {
		if (Active()) {
			mAudio->StopSFX(1);
			mAudio->PlaySFX("SFX/DeathSound.mp3", 0, 1);

			for (int i = 0; i < DEATH_TEXTURES_LIMIT; i++) {
				mDeathFireTextures[i]->Position((i * 60), (30 * (i - 1)));
				DeathSmokeReset(mDeathSmokeTextures[i]);
			}
		}
		for (int i = 0; i < DEATH_TEXTURES_LIMIT; i++) {
			// Bug where the smoke's y axis tilts with the Helicopter - not sure how to fix :(
			mDeathSmokeTextures[i]->Translate(Vector2((0.0f), (-200.0 * mTimer->DeltaTime())), World);
			if (mDeathSmokeTextures[i]->Position().y <= Position().y - 80.0f) {
				DeathSmokeReset(mDeathSmokeTextures[i]);
			}
		}

		Active(false);
		mRespawnTimer += mTimer->DeltaTime();
		mDeathCircleTimer += mTimer->DeltaTime();

		if (mDeathCircle->Scale().x > 4.0f && mDeathCircleTimer >= DEATH_CIRCLE_TIME) {
			mDeathCircleTimer = 0.0f;
			mDeathCircle->Scale(Vector2(mDeathCircle->Scale().x - 1.0f, mDeathCircle->Scale().y - 1.0f));
			mDeathCircle->Rotate(3.9f);
		}
		
		if (mRespawnTimer >= RESPAWN_TIME) {
			mRespawnTimer = 0.0f;
			mIsReadyForRespawn = true;
		}
	}
	else {
		if (mInput->MouseButtonPressed(InputManager::MouseButton::Left) && !Active()) {
			Active(true);
		}

		if (Active()) {
			if (mInput->MouseButtonDown(InputManager::MouseButton::Left)) {
				mVelocity += LIFT_STRENGTH;
				if (!mIsRising) {
					mIsRising = true;
					mAudio->StopSFX(1);
					mAudio->PlaySFX("SFX/LiftSound.mp3", -1, 1);
				}
			}
			if (mInput->MouseButtonReleased(InputManager::MouseButton::Left)) {
				if (mIsRising) {
					mIsRising = false;
					mAudio->StopSFX(1);
					mAudio->PlaySFX("SFX/FallSound.mp3", -1, 1);
				}
			}
			PlayerTilt();
			mVelocity += GRAVITY;
		}

		// Limit Lift & Fall speed
		if (mVelocity < LIFT_LIMIT) {
			mVelocity = LIFT_LIMIT;
		}
		else if (mVelocity > FALL_LIMIT) {
			mVelocity = FALL_LIMIT;
		}

		Translate(Vector2(0.0f, (mVelocity * mTimer->DeltaTime())), (World));

		mAnimatedPlayerTexture->Update();
	}
}
void Player::Render() {

	if (mIsDead) {
		mPlayerDeathTexture->Render();

		for (int i = 0; i < DEATH_TEXTURES_LIMIT; i++) {
			mDeathFireTextures[i]->Render();
			mDeathSmokeTextures[i]->Render();
		}
		mDeathCircle->Render();
	}
	else {
		mAnimatedPlayerTexture->Render();
	}

	PhysEntity::Render();
}

// PRIVATE METHODS

void Player::DeathSmokeReset(GLTexture* deathSmoke) {
	if (Active()) {
		deathSmoke->Position((mRand->RandomRange(
			(-DEATH_SMOKE_LIMIT),
			(DEATH_SMOKE_LIMIT))), 
			mRand->RandomRange(0.0f, 50.0f));
	}
	else {
		deathSmoke->Position((mRand->RandomRange(
			(-DEATH_SMOKE_LIMIT),
			(DEATH_SMOKE_LIMIT))),
			0.0f);
	}

	deathSmoke->Rotation(mRand->RandomRange((0.0f), (360.0f)));
}
