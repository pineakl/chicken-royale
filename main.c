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

  Sprite* chick_;
  chick_ = Sprite_create(&chick_png, _screenWidth/4, _screenHeight/2, 64, 64, pivot_center);
  Sprite_createAnimation(chick_, 4, 5);

  Sprite* chicken_;
  chicken_ = Sprite_create(&chicken_png, _screenWidth * 3/4, _screenHeight/2, 64, 64, pivot_center);
  Sprite_createAnimation(chicken_, 6, 7);

  Sprite* sprites[] = {bg_, chick_, chicken_};
  
  SetTargetFPS(_targetFps);
  while (!WindowShouldClose()) {
    
    for (size_t i = 0; i < sprite_count; i++) {
      Sprite_update(sprites[i], &_targetFps);
    }

    BeginDrawing();
    
    ClearBackground(BLACK);
    for (size_t i = 0; i < sprite_count; i++) {
      Sprite_draw(sprites[i]);
    }
    
    EndDrawing();
  } 

  Sprite_destroy(bg_);

  UnloadTexture(bg_png);
  UnloadTexture(chick_png);
  UnloadTexture(chick_png);
  CloseWindow();
  
  return 0;
}
