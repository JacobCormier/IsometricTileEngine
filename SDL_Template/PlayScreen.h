#ifndef __PLAYSCREEN_H
#define __PLAYSCREEN_H
#include "Player.h"
#include "Tunnel.h"
#include "Scoreboard.h"

class PlayScreen : public GameEntity {
private:
	static const float SCORE_DELAY_TIME;
	static const float PLAYER_SMOKE_DELAY_TIME;
	static const Vector2 PLAYER_STARTING_POSITION;

	Timer* mTimer;
	AudioManager* mAudio;
	InputManager* mInput;
	
	Player* mPlayer;
	float mPlayerSmokeTrailTimer;
	Tunnel* mTunnel;

	// These are only visible when the screen isn't active
	GLTexture* mClickToStartLabel;
	GLTexture* mClickDescriptionLabelOne;
	GLTexture* mClickDescriptionLabelTwo;
	GLTexture* mCopyrightLabelOne;
	GLTexture* mCopyrightLabelTwo;
	
	// These are visible always
	GLTexture* mDistanceLabel;
	Scoreboard* mDistanceScoreboard;
	int mDistanceScore;
	float mDistanceTimer;
	GLTexture* mBestLabel;
	Scoreboard* mBestScoreboard;
	int mBestScore;

public:
	PlayScreen();
	~PlayScreen();


	void Update() override;
	void Render() override;
private:
	void ResetGame();
	void ResetPlayer();
	void CreateLabels();
};
#endif