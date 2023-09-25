#include "PlayScreen.h"

const float PlayScreen::SCORE_DELAY_TIME = 0.05f;
const float PlayScreen::PLAYER_SMOKE_DELAY_TIME = 0.01f;

const Vector2 PlayScreen::PLAYER_STARTING_POSITION = 
	Vector2((-Graphics::SCREEN_WIDTH * 0.1667f), (0.0f));

PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();
	mInput = InputManager::Instance();

	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Position(PLAYER_STARTING_POSITION);

	CreateLabels();

	mDistanceScore = 0;
	mDistanceTimer = 0.0f;
	mPlayerSmokeTrailTimer = 0.0f;

	mBestScore = 0;
}
PlayScreen::~PlayScreen() {
	mTimer = nullptr;
	mAudio = nullptr;
	mInput = nullptr;

	delete mPlayer;
	mPlayer = nullptr;

	delete mClickToStartLabel;
	mClickToStartLabel = nullptr;

	delete mClickDescriptionLabelOne;
	delete mClickDescriptionLabelTwo;
	mClickDescriptionLabelOne = nullptr;
	mClickDescriptionLabelTwo = nullptr;

	delete mDistanceLabel;
	mDistanceLabel = nullptr;

	delete mBestLabel;
	mBestLabel = nullptr;

	delete mCopyrightLabelOne;
	delete mCopyrightLabelTwo;
	mCopyrightLabelOne = nullptr;
	mCopyrightLabelTwo = nullptr;
}

void PlayScreen::Update() {
	mPlayer->Update();

	if (mPlayer->Active()) {
		Active(true);

		mDistanceTimer += mTimer->DeltaTime();
		if (mDistanceTimer > SCORE_DELAY_TIME) {
			mDistanceScore++;
			mDistanceTimer = 0.0f;
		}

	}
	else {
		Active(false);
	}

	//Temporary Code to catch player and restart
	if (mPlayer->IsDead() && mPlayer->ReadyForRespawn()) {
		ResetGame();
		mPlayer->Rotation(0.0f);
	}
}
void PlayScreen::Render() {

	if (!Active() && !mPlayer->IsDead()) {
		mClickToStartLabel->Render();
		mClickDescriptionLabelOne->Render();
		mClickDescriptionLabelTwo->Render();
		mCopyrightLabelOne->Render();
		mCopyrightLabelTwo->Render();
	}
	mDistanceLabel->Render();
	mBestLabel->Render();

	mPlayer->Render();
}

void PlayScreen::ResetGame() {
	ResetPlayer();

	if (mDistanceScore > mBestScore) {
		mBestScore = mDistanceScore;
	}
	mDistanceScore = 0;
	mDistanceTimer = 0.0f;

	mPlayerSmokeTrailTimer = 0.0f;
}
void PlayScreen::ResetPlayer() {
	mPlayer->Reset();
	mPlayer->Position(PLAYER_STARTING_POSITION);
}
void PlayScreen::CreateLabels() {

	mClickToStartLabel = new GLTexture("CLICK TO START", "DIGITALDREAM.ttf", 36, { 49, 196, 245 });
	mClickToStartLabel->Parent(this);
	mClickToStartLabel->Position(Vector2(185.0f, 0.0f));

	mClickDescriptionLabelOne = new GLTexture(
		"CLICK AND HOLD LEFT MOUSE BUTTON TO GO UP",
		"DIGITALDREAMNARROW.ttf",
		28,
		{ 49, 196, 245 });
	mClickDescriptionLabelOne->Parent(this);
	mClickDescriptionLabelOne->Position(Vector2(0.0f, 200.0f));

	mClickDescriptionLabelTwo = new GLTexture(
		"RELEASE TO GO DOWN",
		"DIGITALDREAMNARROW.ttf",
		28,
		{ 49, 196, 245 });
	mClickDescriptionLabelTwo->Parent(mClickDescriptionLabelOne);
	mClickDescriptionLabelTwo->Position(Vector2(206.0f, 40.0f));

	mDistanceLabel = new GLTexture(
		"DISTANCE:", 
		"DIGITALDREAMNARROW.ttf", 
		40, 
		{ 0, 0, 0 });
	mDistanceLabel->Parent(this);
	mDistanceLabel->Position(Vector2(-370.0f, 420.0f));

	mBestLabel = new GLTexture(
		"BEST:", 
		"DIGITALDREAMNARROW.ttf", 
		40, 
		{ 0, 0, 0 });
	mBestLabel->Parent(this);
	mBestLabel->Position(Vector2(294.0f, 420.0f));

	mCopyrightLabelOne = new GLTexture(
		"A game by Jacob Cormier",
		"DIGITALDREAMFAT.ttf",
		40,
		{ 0, 0, 0 });
	mCopyrightLabelOne->Parent(this);
	mCopyrightLabelOne->Position(140.0f, -420.0f);

	mCopyrightLabelTwo = new GLTexture(
		"COPYRIGHT: SEETHRU.CO.UK",
		"DIGITALDREAMFAT.ttf",
		16,
		{ 0, 0, 0 });
	mCopyrightLabelTwo->Parent(mCopyrightLabelOne);
	mCopyrightLabelTwo->Position(210.0f, 40.0f);
}
