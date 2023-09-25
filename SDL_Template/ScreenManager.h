#ifndef __SCREENMANAGER_H
#define __SCREENMANAGER_H
#include "PlayScreen.h"
#include "InputManager.h"

// StartScreen is currently unused,
// still has Galaga stuff

class ScreenManager {
private:
	static ScreenManager * sInstance;

	enum Screens { Start, Play };
	Screens mCurrentScreen;

	InputManager * mInput;

	PlayScreen * mPlayScreen;

public:
	static ScreenManager * Instance();
	static void Release();

	void Update();
	void Render();

private:
	ScreenManager();
	~ScreenManager();
};
#endif