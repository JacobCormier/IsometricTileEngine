#include "Tunnel.h"

const int Tunnel::SPACING_TUNNEL_BLOCKS = 80;

const int Tunnel::MIN_TUNNEL_BLOCKS = 1;
const int Tunnel::MAX_TUNNEL_BLOCKS = 15;

const float Tunnel::RANDOM_LOWER_HEIGHT_LIMIT = -50.0f;
const float Tunnel::RANDOM_UPPER_HEIGHT_LIMIT =  50.0f;

const float Tunnel::OBSTACLE_RANGE = 200.0f;

// The shrink limit gets hit around ~3000 score
// I tested flying at shrink limit and it is challenging but possible
const int Tunnel::SHRINK_LIMIT = 460;
const float Tunnel::UPPER_LIMIT_START = 368.0f;
const float Tunnel::LOWER_LIMIT_START = 528.0f;
float Tunnel::sUpperLimit = 0;
float Tunnel::sLowerLimit = 0;

// PUBLIC METHODS

Tunnel::Tunnel() {
	mTimer = Timer::Instance();
	mRand = Random::Instance();

	Active(false);

	NewGame();
}
Tunnel::~Tunnel() {
	ClearBlocks();
	ClearSmokeTrail();

	mTimer = nullptr;
	mRand = nullptr;
}

void Tunnel::NewGame() {
	mShrinkTimer = 0.0f;

	ClearBlocks();
	TunnelBlock::NewGame();

	sUpperLimit = UPPER_LIMIT_START;
	sLowerLimit = LOWER_LIMIT_START;

	for (int i = 0; i < MAX_BLOCKS; i++) {
		mTunnelBlocks[i] = (new TunnelBlock());
		mTunnelBlocks[i]->Parent(this);
		mTunnelBlocks[i]->Position(Vector2((i * SPACING_TUNNEL_BLOCKS), 0.0f));
	}
	mCurrentSectionLength = 0.0f;
	mCurrentSectionHeight = 0.0f;

	for (int i = 0; i < 2; i++) {
		mObstacleBlocks[i] = new Obstacle();
		mObstacleBlocks[i]->Parent(this);
		mObstacleBlocks[i]->Position(Vector2(((i * 800.f) + 1100.0f), (mRand->RandomRange((-300.0f), (300.0f)))));
	}
}
void Tunnel::AddSmokeTrail(Vector2 playerPosition) {
	GLTexture* smokeTrail = new GLTexture("Smoke.png");

	smokeTrail->Scale(smokeTrail->Scale() * 3.0f);
	smokeTrail->Position(playerPosition);
	smokeTrail->Rotation(mRand->RandomRange(0.0f, 360.0f));
	smokeTrail->Parent(this);
	mSmokeTrail.push_back(smokeTrail);

}
void Tunnel::ClearSmokeTrail() {
	for (int i = 0; i < mSmokeTrail.size(); i++) {
		delete mSmokeTrail[i];
		mSmokeTrail[i] = nullptr;
	}
	mSmokeTrail.clear();
}

void Tunnel::Update() {
	
	// temporary moving code
	if (Active()) {		
		for (int i = 0; i < MAX_BLOCKS; i++) {
			mTunnelBlocks[i]->Translate(Vector2(TUNNEL_SPEED * mTimer->DeltaTime(), 0.0f));
		}
		for (int i = 0; i < 2; i++) {
			mObstacleBlocks[i]->Translate(Vector2(TUNNEL_SPEED * mTimer->DeltaTime(), 0.0f));
		}
		for (int i = 0; i < mSmokeTrail.size(); i++) {
			mSmokeTrail[i]->Translate(Vector2(TUNNEL_SPEED * mTimer->DeltaTime(), 0.0f), World);
		}

		mShrinkTimer += mTimer->DeltaTime();
		// This allows the tunnels to shrink quicker
		if (mShrinkTimer >= 1.5f) {
			if (mTunnelBlocks[0]->GetSpacing() > SHRINK_LIMIT) {
				ShrinkTunnel();
				mShrinkTimer = 0.0f;
			}
		}
	}
	else {
		ClearSmokeTrail();
	}
	HandleBlocks();
}
void Tunnel::Render() {
	for (int i = 0; i < MAX_BLOCKS; i++) {
		mTunnelBlocks[i]->Render();
	}

	for (int i = 0; i < 2; i++) {
		mObstacleBlocks[i]->Render();
	}

	for (int i = 0; i < mSmokeTrail.size(); i++) {
		mSmokeTrail[i]->Render();
	}
}

// PRIVATE METHODS

void Tunnel::ClearBlocks() {
	for (int i = 0; i < MAX_BLOCKS; i++) {
		delete mTunnelBlocks[i];
		mTunnelBlocks[i] = nullptr;
	}

	for (int i = 0; i < 2; i++) {
		delete mObstacleBlocks[i];
		mObstacleBlocks[i] = nullptr;
	}
}

void Tunnel::HandleBlocks() {	
	if (mTunnelBlocks[0]->Position().x < -Graphics::SCREEN_WIDTH * 0.1f) {
		delete mTunnelBlocks[0];
		mTunnelBlocks[0] = nullptr;
		AddNewBlock();
	}

	if (mObstacleBlocks[0]->Position().x < -Graphics::SCREEN_WIDTH * 0.1f) {
		mObstacleBlocks[0]->Position(Vector2((1600.0f), (mRand->RandomRange((-OBSTACLE_RANGE), (OBSTACLE_RANGE)))));

		Obstacle* temp = mObstacleBlocks[0];
		mObstacleBlocks[0] = mObstacleBlocks[1];
		mObstacleBlocks[1] = temp;
	}

	if (mSmokeTrail.size() >= 1) {
		if (mSmokeTrail[0]->Position().x < -Graphics::SCREEN_WIDTH * 0.1f) {
			delete mSmokeTrail[0];
			mSmokeTrail[0] = nullptr;
			mSmokeTrail.erase(mSmokeTrail.begin());
		}
	}

}
void Tunnel::AddNewBlock() {
	// Only called from within Tunnel::CheckBlocks where position 0 is empty
	for (int i = 1; i < MAX_BLOCKS; i++) {
		mTunnelBlocks[i - 1] = mTunnelBlocks[i];
	}

	mTunnelBlocks[MAX_BLOCKS - 1] = new TunnelBlock();
	mTunnelBlocks[MAX_BLOCKS - 1]->Position(GetNextBlockPosition());
	mTunnelBlocks[MAX_BLOCKS - 1]->Parent(this);
}

Vector2 Tunnel::GetNextBlockPosition() {
	// The next block is spaced right of the rightmost block
	float newX = mTunnelBlocks[MAX_BLOCKS - 2]->Position().x + SPACING_TUNNEL_BLOCKS;
	float newY = mTunnelBlocks[MAX_BLOCKS - 2]->Position().y;
	
	if (newY < sLowerLimit && newY > sUpperLimit) {
		SetTunnelRandomness();
	}
	else if (newY >= sLowerLimit) {
		SetTunnelRandomness(TunnelDirection::UP);
	}
	else if (newY <= sUpperLimit) {
		SetTunnelRandomness(TunnelDirection::DOWN);
	}
	else {
		std::cout << "Tunnel::GetNextBlockPosition() BROKE!" << std::endl;
	}

	mCurrentSectionLength--;
	newY += mCurrentSectionHeight;

	if (newY > sLowerLimit) {
		newY = sLowerLimit;
	}
	else if (newY < sUpperLimit) {
		newY = sUpperLimit;
	}

	//std::cout << "Tunnel::GetNextBlockPosition(): " << Vector2(newX, newY) << std::endl;
	return Vector2(newX, newY);
}
void Tunnel::SetTunnelRandomness(TunnelDirection direction) {
	// By default, won't change randomness unless the 
	// length of current tunnel segment is 0 
	// OR the parameter was specifically UP or DOWN to control limits
	if (mCurrentSectionLength <= 0 && direction == TunnelDirection::RANDOM) {
		mCurrentSectionLength = mRand->RandomRange(MIN_TUNNEL_BLOCKS, MAX_TUNNEL_BLOCKS);
		mCurrentSectionHeight = mRand->RandomRange(RANDOM_LOWER_HEIGHT_LIMIT, RANDOM_UPPER_HEIGHT_LIMIT);
	}	
	else if (direction == TunnelDirection::UP) {
		mCurrentSectionLength = mRand->RandomRange(MIN_TUNNEL_BLOCKS, MAX_TUNNEL_BLOCKS / 2);
		mCurrentSectionHeight = mRand->RandomRange(RANDOM_LOWER_HEIGHT_LIMIT, 0.0f);
	}
	else if (direction == TunnelDirection::DOWN) {
		mCurrentSectionLength = mRand->RandomRange(MIN_TUNNEL_BLOCKS, MAX_TUNNEL_BLOCKS / 2);
		mCurrentSectionHeight = mRand->RandomRange(0.0f, RANDOM_UPPER_HEIGHT_LIMIT);
	}	
}

void Tunnel::ShrinkTunnel() {
	TunnelBlock::DecreaseBlockSpacing();
	sUpperLimit--;
	sLowerLimit++;
}