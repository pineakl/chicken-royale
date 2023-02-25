#include <stddef.h>
#include <stdio.h>
#include "raylib.h"
#include "engine.h"

int main (void)
{

  const int _screenWidth = 320;
  const int _screenHeight = 240;
  const int _targetFps = 60;

  InitWindow(_screenWidth, _screenHeight, "Chicken Royale!");

  Texture2D bg_png = LoadTexture("resources/textures/bg.png");
  Texture2D chick_png = LoadTexture("resources/textures/chick.png");
  Texture2D chicken_png = LoadTexture("resources/textures/chicken.png");

  Vector2 pivot_center = { 0.5, 0.5 };

  Sprite* bg_; 
  bg_ = Sprite_create(&bg_png, _screenWidth/2, _screenHeight/2, bg_png.width*2, bg_png.height*2, pivot_center);

  /*
  Sprite* chick_;
  chick_ = Sprite_create(&chick_png, _screenWidth/4, _screenHeight/2, 64, 64, pivot_center);
  chick_->clips_ = Sprite_createAnimation(chick_, 4, 2);
  Animation_addCLip(chick_, 0, 2, 10, "fall");
  Animation_addCLip(chick_, 1, 4, 5, "flap");
  Animation_playClip(chick_, "fall");
  */

  Sprite* chicken_;
  chicken_ = Sprite_create(&chicken_png, _screenWidth * 2/3, _screenHeight/2, 64, 64, pivot_center);
  chicken_->clips_ = Sprite_createAnimation(chicken_, 6, 2);
  Animation_addCLip(chicken_, 0, 2, 10, "fall");
  Animation_addCLip(chicken_, 1, 6, 7, "flap");
  Animation_playClip(chicken_, "flap");

  Sprite* sprites[] = {bg_, /*chick_,*/ chicken_};

  SetTargetFPS(_targetFps);
  while (!WindowShouldClose()) {

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
      Animation_playClip(chicken_, "flap");
    }
    else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
      Animation_playClip(chicken_, "fall");
    }
    
    for (size_t i = 0; i < sprite_count; i++) {
      Sprite_update(sprites[i], &_targetFps);
    }

    BeginDrawing();
    
    ClearBackground(BLACK);
    for (size_t i = 0; i < sprite_count; i++) {
      Sprite_draw(sprites[i]);
    }
    DrawText(chicken_->clips_[chicken_->currentClip].name, 86, _screenHeight/2, 24, WHITE);
    
    EndDrawing();
  } 

  Sprite_destroy(bg_);

  UnloadTexture(bg_png);
  UnloadTexture(chick_png);
  UnloadTexture(chicken_png);
  CloseWindow();
  
  return 0;
}
