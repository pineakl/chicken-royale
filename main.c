#include <stdio.h>
#include "raylib.h"
#include "engine.h"

int main (void)
{

  const int _screenWidth = 320;
  const int _screenHeight = 240;

  InitWindow(_screenWidth, _screenHeight, "Chicken Royale!");

  Texture2D bg_png = LoadTexture("resources/textures/bg.png");
  Texture2D chick_png = LoadTexture("resources/textures/chick.png");

  Vector2 pivot_center = { 0.5, 0.5 };

  Sprite* bg_; 
  bg_ = Sprite_create(&bg_png, _screenWidth/2, _screenHeight/2, bg_png.width*2, bg_png.height*2, pivot_center);

  Sprite* chick_;
  chick_ = Sprite_create(&chick_png, _screenWidth/2, _screenHeight/2, chick_png.width*2, chick_png.height*2, pivot_center);

  Sprite* sprites[] = {bg_, chick_};
  
  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    

    BeginDrawing();
    
    ClearBackground(BLACK);
    for (int i = 0; i < sprite_count; i++) {
      Sprite_draw(sprites[i]);
    }
    
    EndDrawing();
  } 

  Sprite_destroy(bg_);

  UnloadTexture(bg_png);
  UnloadTexture(chick_png);
  CloseWindow();
  
  return 0;
}
