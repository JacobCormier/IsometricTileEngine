 #include "ScreenManager.h"

ScreenManager* ScreenManager::sInstance = nullptr;

ScreenManager* ScreenManager::Instance() {
	if (sInstance == nullptr) {
		sInstance = new ScreenManager();
	}

	return sInstance;
}
void ScreenManager::Release() {
	delete sInstance;
	sInstance = nullptr;
}

void ScreenManager::Update() {
		mPlayScreen->Update();
}
void ScreenManager::Render() { 
		mPlayScreen->Render();
}

ScreenManager::ScreenManager() {
	mInput = InputManager::Instance();

	mPlayScreen = new PlayScreen();
	mPlayScreen->Position(Graphics::SCREEN_WIDTH * 0.5, Graphics::SCREEN_HEIGHT * 0.5);

	mCurrentScreen = Play;
}
ScreenManager::~ScreenManager() {
	mInput = nullptr;

	delete mPlayScreen;
	mPlayScreen = nullptr;
}