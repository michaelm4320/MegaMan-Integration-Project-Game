#include "Player.h"

Player::Player() {

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mVisible = false;
	mAnimating = false;

	mScore = 0;
	mLives = 2;

	//Player entity
	mMan = new Texture("megaman.png");
	mMan->Parent(this);
	mMan->Pos(VEC2_ZERO);

	//Player Settings
	mMoveSpeed = 300.0f;
	mMoveBounds = Vector2(99.0f, 413.0f);
    mMoveBounds2 = Vector2(277.0f, 471.0f);

	//Movement transition entity
	mMoveLeave = new AnimatedTexture("transition.png", 0, 0, 175, 262, 4, 0.2f, AnimatedTexture::horizontal);
    mMoveLeave->Parent(this);
    mMoveLeave->Pos(VEC2_ZERO);
    mMoveLeave->WrapMode(AnimatedTexture::once);
	
	//Player death entity
	mDeathAnimation = new AnimatedTexture("mmDeath.png", 0, 0, 237, 217, 1, 2.0f, AnimatedTexture::horizontal);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Pos(VEC2_ZERO);
	mDeathAnimation->WrapMode(AnimatedTexture::once);

	for(int i = 0; i < MAX_BULLETS; i++) {
	
		mBullets[i] = new Bullet();
	}
}

Player::~Player() {

	mTimer = NULL;
	mInput = NULL;
	mAudio = NULL;

	delete mMan;
	mMan = NULL;

	delete mMoveLeave;
    mMoveLeave = NULL;

	delete mDeathAnimation;
	mDeathAnimation = NULL;

	for(int i=0; i < MAX_BULLETS; i++) {
		
		delete mBullets[i];
		mBullets[i] = NULL;
	}
}

void Player::HandleMovement() {

	
	//Player Movement
	if(mInput->KeyPressed(SDL_SCANCODE_RIGHT)) {
    mMoveLeave->ResetAnimation();
    mLeaveMoving = true; 
	
    Translate(VEC2_RIGHT * 157, world);  

	} else if (mInput->KeyPressed(SDL_SCANCODE_LEFT)) {
          mMoveLeave->ResetAnimation();
          mLeaveMoving = true; 
          Translate(-VEC2_RIGHT * 157, world);
        }

	if (mInput->KeyPressed(SDL_SCANCODE_UP)) {
          mMoveLeave->ResetAnimation();
          mLeaveMoving = true; 
          Translate(-VEC2_UP * 100, world);

        } else if (mInput->KeyPressed(SDL_SCANCODE_DOWN)) {
          mMoveLeave->ResetAnimation();
          mLeaveMoving = true; 
          Translate(VEC2_UP * 100, world);
        }
	
	//Player movement bound area
	Vector2 pos = Pos(local);
	if(pos.x < mMoveBounds.x)
		pos.x = mMoveBounds.x;
    else if(pos.x > mMoveBounds.y)
		pos.x = mMoveBounds.y;

    if (pos.y < mMoveBounds2.x)
      pos.y = mMoveBounds2.x;
    else if (pos.y > mMoveBounds2.y)
      pos.y = mMoveBounds2.y;

	Pos(pos);
}

void Player::HandleFiring() {

	//Player firing
	if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {

		for (int i = 0; i < MAX_BULLETS; i++) {
			
			if (!mBullets[i]->Active()) {
				
				mBullets[i]->Fire(Pos());
				mAudio->PlaySFX("fire.wav");
				break;
      }
    }
  }
}

void Player::Visible(bool visible) {

	mVisible = visible;
}

bool Player::IsAnimating() {
	
	return mAnimating;
}

int Player::Score() {

	return mScore;
}

int Player::Lives() {

	return mLives;
}

void Player::AddScore(int change) {

	mScore += change;
}

void Player::WasHit() {

	//Player hit
	mLives--;
	mDeathAnimation->ResetAnimation();
	mAnimating = true;
	mAudio->PlaySFX("death.wav");
}

void Player::Update() { 

	if(mLeaveMoving) {
	
		mMoveLeave->Update();
		mLeaveMoving = mMoveLeave->IsAnimating();
		
	}

	if(mAnimating){

		mDeathAnimation->Update();
		mAnimating = mDeathAnimation->IsAnimating();

	} else {
		if(Active()) {
		
			HandleMovement();
			HandleFiring();
		}
  }
	
	for(int i = 0; i < MAX_BULLETS; i++)
		mBullets[i]->Update();
}

void Player::Render() {

	if(mVisible) {
		 
	
		if (mAnimating) {
                  mDeathAnimation->Render();
                } else if (mLeaveMoving) {
                  mMoveLeave->Render();
                } else {
                  mMan->Render();
                }
	}
        for (int i = 0; i < MAX_BULLETS; i++) 
			mBullets[i]->Render();
}