#ifndef _CONTROLS_H
#define _CONTROLS_H
#include "InputManager.h"
#include "Level.h"
#include "PlayBG.h"
#include "Player.h"
#include "StartScreen.h"

class Controls : public GameEntity {
 private:
  Texture* mControlsMove;
  Texture* mControlShoot;
  Texture* mControlHit;
  Texture* mControlLevel;
  Texture* mControlReturn;

 public:
  Controls();
  ~Controls();

  void Render();
};

#endif
