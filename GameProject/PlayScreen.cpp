#include "PlayScreen.h"


PlayScreen::PlayScreen() {

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mPlayBG = new PlayBG();

	//Ready player texture
	mStartLabel = new Texture("ARE YOU READY?", "BN6FontBold.ttf", 60, {0, 0, 0});
	mStartLabel->Parent(this);
    mStartLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f,Graphics::Instance()->SCREEN_HEIGHT * 0.3f));

	mLevel = NULL;
	mLevelStartDelay = 1.0f;
	mLevelStarted = false;

	mPlayer = NULL;
}

PlayScreen::~PlayScreen() {

	mTimer = NULL;
	mInput = NULL;

	delete mPlayBG;
	mPlayBG = NULL;

	delete mStartLabel;
	mStartLabel = NULL;

	delete mLevel;
	mLevel = NULL;

	delete mPlayer;
	mPlayer = NULL;
}

void PlayScreen::StartNextLevel() {

	mCurrentStage++;
	mLevelStartTimer = 0.0f;
	mLevelStarted = true;
	
	delete mLevel;
	mLevel = new Level(mCurrentStage, mPlayBG, mPlayer);
}

void PlayScreen::StartNewGame() {

	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Parent(this);
    mPlayer->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.267f,Graphics::Instance()->SCREEN_HEIGHT * 0.58f));
	mPlayer->Active(false);

	mPlayBG->SetLives(mPlayer->Lives());
	mPlayBG->SetLevel(0);

	mGameStarted = false;
	mLevelStarted = false;
	mLevelStartTimer = 0.0f;

    mCurrentStage = 0;

	mAudio->PlayMusic("start.wav", 0);
	
}

bool PlayScreen::GameOver() {

	//Game over state
	if(!mLevelStarted)
		return false;

	return (mLevel->State() == Level::gameover);
}

void PlayScreen::Update() {

	if(mGameStarted) {
		
		if(!mLevelStarted) {
		
			mLevelStartTimer += mTimer->DeltaTime();
			if(mLevelStartTimer >= mLevelStartDelay)
				StartNextLevel();
		}
		
	} else {
	
		if(!Mix_PlayingMusic()) {
		
			mGameStarted = true;
		}
	}

	if(mGameStarted) {
	
		if(mCurrentStage > 0)
			mPlayBG->Update();

		if (mLevelStarted) {
                 
			mLevel->Update();

			if(mLevel->State() == Level::finished) {
			
				mLevelStarted = false;
			}
        }

		mPlayer->Update();		
	}       
}

void PlayScreen::Render() {

  mPlayBG->Render();

  if (!mGameStarted) 
	  mStartLabel->Render();

  if (mGameStarted) {

    if (mLevelStarted) 
      mLevel->Render();

    mPlayer->Render();
    
  }
}