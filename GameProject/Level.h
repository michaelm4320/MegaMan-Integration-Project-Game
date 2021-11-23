#ifndef _LEVEL_H
#define _LEVEL_H
#include "InputManager.h"
#include "PlayBG.h"
#include "Player.h"

class Level : public GameEntity {

	public:

		enum LEVEL_STATES { running, finished, gameover };

	private:

		Timer* mTimer;
		PlayBG* mPlayBG;

		int mStage;
		bool mStageStarted;

		float mLabelTimer;

		Texture* mStageLabel;
		float mStageLabelOnScreen;
		float mStageLabelOffScreen;

		Texture* mReadyLabel;
		float mReadyLabelOnScreen;
		float mReadyLabelOffScreen;

		Player* mPlayer;
		bool mPlayerHit;
		float mPlayerRespawnDelay;
		float mPlayerRespawnTimer;
		float mPlayerRespawnLabelOnScreen;

		Texture* mGameOverLabel;
		bool mGameOver;
		float mGameOverDelay;
		float mGameOverTimer;
		float mGameOverLabelOnScreen;

		LEVEL_STATES mCurrentState;

		private:

			void StartStage();
			void HandleStartLabels();
			void HandleCollisions();
			void HandlePlayerDeath();

	public:

		Level(int stage, PlayBG* playBG, Player* player);
		~Level();

		LEVEL_STATES State();

		void Update();

		void Render();
};

#endif
