#include "Scoreboard.h"

// PUBLIC METHOD

Scoreboard::Scoreboard() 
	: Scoreboard({0, 0, 0}) {
}
Scoreboard::Scoreboard(SDL_Color color) {
	mColor = color;
	Score(0);
}
Scoreboard::~Scoreboard() {
	ClearBoard();
}

void Scoreboard::Score(int score) {
	ClearBoard();

	if (score == 0) {
		for (int i = 0; i < 1; i++) {
			mScore.push_back(new GLTexture("0", "DIGITALDREAMFAT.ttf", 40, mColor));
			mScore[i]->Parent(this);
			mScore[i]->Position(Vector2(32.0f * i, 0.0f));
		}
	}
	else {
		std::string str = std::to_string(score);
		unsigned lastIndex = (unsigned)str.length() - 1;

		for (unsigned i = 0; i <= lastIndex; i++) {
			mScore.push_back(new GLTexture(str.substr(i, 1), "DIGITALDREAMFAT.ttf", 40, mColor));
			mScore[i]->Parent(this);
			mScore[i]->Position(Vector2(32.0f * (i), 0.0f));
		}
	}
}
int Scoreboard::GetScore() {
	return mScoreValue;
}

void Scoreboard::Render() {
	for (auto digit : mScore) {
		digit->Render();
	}
}

// PRIVATE METHOD

void Scoreboard::ClearBoard() {
	for (auto score : mScore) {
		delete score;
		score = nullptr;
	}

	mScore.clear();
}
