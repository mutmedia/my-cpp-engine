#ifndef GAME_H
#define GAME_H

#include "camera.h"

class Game {
  public:
    void Update();
    void Initialize();
    Camera * main_camera_;
  private:
};

#endif
