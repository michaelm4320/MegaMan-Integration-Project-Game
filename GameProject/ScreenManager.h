#ifndef _SCREENMANAGER_H
#define _SCREENMANAGER_H
#include "StartScreen.h"
#include "PlayScreen.h"
#include "Controls.h"

class ScreenManager {

	private:

		enum SCREENS { start, play, controls };

		static ScreenManager* sInstance;

		InputManager* mInput;

		StartScreen* mStartScreen;
		PlayScreen* mPlayScreen;
        Controls* mControls;

		SCREENS mCurrentScreen;


	public:
		static ScreenManager* Instance();
		static void Release();
        int mode = 1;

		void Update();
		void Render();

	private:

		ScreenManager();
         ~ScreenManager();
};


#endif
