#include "Level.h"

Level::Level(int stage, PlayBG* playBG, Player* player) {

	mTimer = Timer::Instance();
	mPlayBG = playBG;
	mPlayBG->SetLevel(stage);

	mStage = stage;
	mStageStarted = false;

	mLabelTimer = 0.0f;

	mStageLabelOnScreen = 0.0f;
	mStageLabelOffScreen = 1.5f;

	//Battle start message entity
	mReadyLabel = new Texture("battleStart.png");
	mReadyLabel->Parent(this);
    mReadyLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT *0.3f));

	mReadyLabelOnScreen = mStageLabelOffScreen;
	mReadyLabelOffScreen = mReadyLabelOnScreen + 3.0f;

	//Player settings
	mPlayer = player;
	mPlayerHit = false;
    mPlayerRespawnDelay = 3.0f;
    mPlayerRespawnTimer = 0.0f;
	mPlayerRespawnLabelOnScreen = 2.0f;

	//Game over entities
	mGameOverLabel = new Texture("GAME OVER", "BN6FontBold.ttf", 75, {150, 0, 0});
	mGameOverLabel->Parent(this);
    mGameOverLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.3f));

	mGameOver = false;
	mGameOverDelay = 6.0f;
	mGameOverTimer = 0.0f;
	mGameOverLabelOnScreen = 1.0f;

	mCurrentState = running;
}

Level::~Level() {

	mTimer = NULL;
	mPlayBG = NULL;

	delete mReadyLabel;
	mReadyLabel = NULL;

	mPlayer = NULL;

	delete mGameOverLabel;
	mGameOverLabel = NULL;
}

void Level::StartStage() {

	mStageStarted = true;
}

void Level::HandleStartLabels() {

	mLabelTimer += mTimer->DeltaTime();
  if (mLabelTimer >= mStageLabelOffScreen) {
    if (mStage > 1) {
      StartStage();
    } else {
      if (mLabelTimer >= mReadyLabelOffScreen) {
        StartStage();
        mPlayer->Active(true);
        mPlayer->Visible(true);
      }
    }
  }
}

void Level::HandleCollisions() {
	
	//Player hit
  if (!mPlayerHit) {
    if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_X)) {
      mPlayer->WasHit();
      mPlayBG->SetLives(mPlayer->Lives());

      mPlayerHit = true;
      mPlayerRespawnTimer = 0.0f;
      mPlayer->Active(false);
    }
  }
}

void Level::HandlePlayerDeath() {

	//Player losing lives
	if(!mPlayer->IsAnimating()) {
	
		if(mPlayer->Lives() > 0) {
		
			if(mPlayerRespawnTimer == 0.0f)
				mPlayer->Visible(false);

			mPlayerRespawnTimer += mTimer->DeltaTime();
			if(mPlayerRespawnTimer >= mPlayerRespawnDelay) {
			
				mPlayer->Active(true);
				mPlayer->Visible(true);
				mPlayerHit = false;
			}

		} else {
		
			if(mGameOverTimer == 0.0f)
				mPlayer->Visible(false);

			mGameOverTimer += mTimer->DeltaTime();
			if(mGameOverTimer >= mGameOverDelay) {
			
				mCurrentState = gameover;
			}
		}
	}
}

Level::LEVEL_STATES Level::State() {

	return mCurrentState;
}

void Level::Update() {

  if (!mStageStarted) {

    HandleStartLabels();

  } else {
    HandleCollisions();

    if (mPlayerHit) {
		
		HandlePlayerDeath();

  } else {	

	if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_N)) {

        mCurrentState = finished;
      }
	}
  }
}

void Level::Render() {

	if(!mStageStarted) {
	
		if(mLabelTimer > mStageLabelOnScreen && mLabelTimer < mStageLabelOffScreen) {
			
		} else if(mLabelTimer > mReadyLabelOnScreen && mLabelTimer < mReadyLabelOffScreen) {
		
			mReadyLabel->Render();
		}
	} else {
	
		if(mPlayerHit) {
		
			if(mPlayerRespawnTimer >= mPlayerRespawnLabelOnScreen)
				mReadyLabel->Render();

			if(mGameOverTimer >=mGameOverLabelOnScreen)
				mGameOverLabel->Render();
		}
	}
}