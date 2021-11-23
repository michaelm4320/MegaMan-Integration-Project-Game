#include "PlayBG.h"

PlayBG::PlayBG() {

	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	//Background stage entities
	mBackground = new Texture("bgAnimated.png");
    mAnimatedBackground = new AnimatedTexture("bgAnimated.png", 0, 0, 960, 640, 10, 1.25f, AnimatedTexture::vertical);

	mStage = new Texture("Stage.png");
    mStage->Pos(Vector2(480.0f, 450.0f));

	mStatus = new Texture("Status.png");
    mStatus->Pos(Vector2(250.0f, 75.0f));

	mBackground->Parent(this);
	mBackground->Pos(VEC2_ZERO);

	mBackground->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.32f));
    mAnimatedBackground->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mLives = new GameEntity();
	mLives->Parent(this);
	mLives->Pos(Vector2(110.0f, 90.0f));

	//Player lives
	for(int i = 0; i < MAX_MM_TEXTURES; i++) {
	
		mLivesTextures[i] = new Texture("Life.png");
		mLivesTextures[i]->Parent(mLives);
		mLivesTextures[i]->Pos(Vector2(130.0f * (i % 3), 70.f * (i / 3)));
	}

	mFlags = new GameEntity();
	mFlags->Parent(this);
	mFlags->Pos(Vector2(350.0f, 100.0f));

	mFlagTimer = 0.0f;
	mFlagInterval = 0.5;
	
}

PlayBG::~PlayBG() {

	mTimer = NULL;
	mAudio = NULL;

	delete mBackground;
	mBackground = NULL;

	delete mAnimatedBackground;
    mAnimatedBackground = NULL;

	delete mStage;
    mStage = NULL;

	delete mStatus;
    mStatus = NULL;

	delete mLives;
	mLives = NULL;

	for(int i = 0; i < MAX_MM_TEXTURES; i++) {
	
		delete mLivesTextures[i];
		mLivesTextures[i] = NULL;
	}
	delete mFlags;
	mFlags = NULL;

	ClearFlags();
}

void PlayBG::ClearFlags() {

	for (int i = 0; i < mFlagTextures.size(); i++) {  
	
		delete mFlagTextures[i];
		mFlagTextures[i] = NULL;
	}

	mFlagTextures.clear();
}

void PlayBG::AddNextFlag() {

	//Stage level flags
	if(mRemainingLevels == 3)
		AddFlag("3.png", 72.0f, 3);
    else if(mRemainingLevels == 2)
		AddFlag("2.png", 72.0f, 2);
    else if (mRemainingLevels == 1)
		AddFlag("1.png", 72.0f, 2);
}

void PlayBG::AddFlag(std::string filename, float width, int value) {

	
	int index = mFlagTextures.size();

	if(index > 0)
		mFlagXOffset += width * 0.5f;

	//Location of stage flag
	mRemainingLevels -= value;
    mFlagTextures.push_back(new Texture(filename));
	mFlagTextures[index]->Parent(mFlags);
	mFlagTextures[index]->Pos(VEC2_RIGHT*mFlagXOffset);
	mFlagXOffset += width * 0.5f;

	mAudio->PlaySFX("StageSE.wav");
}
void PlayBG::SetLives(int lives) {

	mTotalLives = lives;

}

void PlayBG::SetLevel(int level) {

	ClearFlags();

	mRemainingLevels = level;
	mFlagXOffset = 0.0f;
}

void PlayBG::Update() {

	mAnimatedBackground->Update();

	if(mRemainingLevels > 0) {
	
		mFlagTimer += mTimer->DeltaTime();
		if(mFlagTimer >= mFlagInterval) {
			
			AddNextFlag();
			mFlagTimer = 0.0f;
		}
	}
}

void PlayBG::Render() {
  
	mBackground->Render();
    mAnimatedBackground->Render();

	mStage->Render();
    mStatus->Render();

	for(int i = 0; i < MAX_MM_TEXTURES && i < mTotalLives; i++) {
	
		mLivesTextures[i]->Render();
	}

	for (int i = 0; i < mFlagTextures.size(); i++) {
          mFlagTextures[i]->Render();
        }

}