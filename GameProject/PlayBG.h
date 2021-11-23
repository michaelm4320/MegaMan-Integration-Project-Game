#ifndef _PLAYHEALTH_H
#define _PLAYHEALTH_H
#include "Timer.h"
#include "AnimatedTexture.h"
#include "AudioManager.h"
#include "StartScreen.h"
#include <vector>


class PlayBG : public GameEntity {

	private:
		Timer* mTimer;
		AudioManager* mAudio;

		Texture* mBackground;
        AnimatedTexture* mAnimatedBackground;

		Texture* mStage;
        Texture* mStatus;

		float mBlinkTimer;
		float mBlinkInterval;
		
		static const int MAX_MM_TEXTURES = 2;
		GameEntity* mLives;
		Texture* mLivesTextures[MAX_MM_TEXTURES];
		int mTotalLives;

		GameEntity* mFlags;
		std::vector<Texture*> mFlagTextures;
		int mRemainingLevels;
		int mFlagXOffset;
		float mFlagTimer;
		float mFlagInterval;

		private:

			void ClearFlags();
			void AddNextFlag();
			void AddFlag(std::string filename, float widgth, int value);

	public:

		PlayBG();
		~PlayBG();

		void SetLives(int lives);
		void SetLevel(int level);

		void Update();

		void Render();

};

#endif