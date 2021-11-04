#ifndef _STARTSCREEN_H
#define _STARTSCREEN_H
#include "AnimatedTexture.h"
#include "InputManager.h"

using namespace QuickSDL;

//Creating subclass StartScreen from parent GameEntity. Used to attach objects to StartScreen so they
//will have a position on screen which will be used to move the objects around.
class StartScreen : public GameEntity {

private:
	//Initialization list for text/images
	//Texture used to create text/images, vector2 with regards to movemement
	Timer* mTimer;
	InputManager* mInput;

	//Logo Entities
	Texture* mLogo;
	AnimatedTexture* mAnimatedLogo;

	//Play Mode Entities
	GameEntity* mPlayModes;
	Texture* mNewGame;
	Texture* mCursor;
    AnimatedTexture* mAnimatedCursor;
	Vector2 mCursorStartPos;
	Vector2 mCursorOffset;
	int mSelectedMode;

	//Bottom Bar Entities
	GameEntity* mBotBar;
	Texture* mRights;
	
	//Screen Animation Variables
	Vector2 mAnimationStartPos;
	Vector2 mAnimationEndPos;
	float mAnimationTotalTime;
	float mAnimationTimer;
	bool mAnimationDone;
	
public:
	//Constructor
	StartScreen();
	~StartScreen();

	void ChangeSelectedMode(int change);

	void Update();

	void Render();

};

#endif