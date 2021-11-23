#include "ScreenManager.h"

//Responsible for handling all screens for game (Title scree, Control Screen, Play Screen)
ScreenManager* ScreenManager::sInstance = NULL;

ScreenManager* ScreenManager::Instance() {

	if(sInstance == NULL)
		sInstance = new ScreenManager();

	return sInstance;
}

void ScreenManager::Release() {

	delete sInstance;
	sInstance = NULL;
}

ScreenManager::ScreenManager() {

	mInput = InputManager::Instance();

	mStartScreen = new StartScreen();
	mPlayScreen = new PlayScreen();
    mControls = new Controls();
        
	mCurrentScreen = start;
}

ScreenManager::~ScreenManager() {

	mInput = NULL;

	delete mStartScreen;
	mStartScreen = NULL;

	delete mPlayScreen;
	mPlayScreen = NULL;

}

void ScreenManager::Update() {
  if (mInput->KeyPressed(SDL_SCANCODE_DOWN) || mInput->KeyPressed(SDL_SCANCODE_UP))
      mode *= -1;

  switch (mCurrentScreen) {
    

    
    case start:

      mStartScreen->Update();
      
      // Switch screens by hitting enter
      if (mInput->KeyPressed(SDL_SCANCODE_RETURN) && mode == -1) {
          mCurrentScreen = controls;  
      }
      else if (mInput->KeyPressed(SDL_SCANCODE_RETURN) && mode == 1) { 
        mCurrentScreen = play;
        mPlayScreen->StartNewGame();
      }
      break;

    case play:

      mPlayScreen->Update();
      if (mPlayScreen->GameOver()) {
        mCurrentScreen = start;
      
      }
      break;

    case controls:

      mControls->Update();
      if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) 
          mCurrentScreen = start;
      break;
  }
}

void ScreenManager::Render() {

	switch (mCurrentScreen) {

    case start:

      mStartScreen->Render();
	  
      break;

	case play:

		mPlayScreen->Render();
		break;

    case controls:

        mControls->Render();
        break;
  }
}