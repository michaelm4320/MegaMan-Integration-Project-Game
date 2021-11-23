#include "Controls.h"

Controls::Controls() {

  //Control screen text entities
  mControlsMove = new Texture("Arrow Keys - Move Up, Down, Left, Right", "BN6FontBold.ttf", 45, {255, 255, 255});
  mControlsMove->Parent(this);
  mControlsMove->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.1f));

  mControlShoot = new Texture("Spacebar Key - Shoot", "BN6FontBold.ttf", 45, {255, 255, 255});
  mControlShoot->Parent(this);
  mControlShoot->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.2f));

  mControlHit = new Texture("X Key - Lose a life", "BN6FontBold.ttf", 45, {255, 255, 255});
  mControlHit->Parent(this);
  mControlHit->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.3f));

  mControlLevel = new Texture("N Key - Skip a level", "BN6FontBold.ttf", 45, {255, 255, 255});
  mControlLevel->Parent(this);
  mControlLevel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.4f));

  mControlReturn = new Texture("Press Enter to return to title", "BN6FontBold.ttf", 45, {255, 255, 255});
  mControlReturn->Parent(this);
  mControlReturn->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.6f));

}

Controls::~Controls() {
  delete mControlsMove;
  mControlsMove = NULL;

  delete mControlShoot;
  mControlShoot = NULL;

  delete mControlHit;
  mControlHit = NULL;

  delete mControlLevel;
  mControlLevel = NULL;

  delete mControlReturn;
  mControlReturn = NULL;
}

void Controls::Render() { 
  mControlsMove->Render();
  mControlShoot->Render();
  mControlHit->Render();
  mControlLevel->Render();
  mControlReturn->Render();
}