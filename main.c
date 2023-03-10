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

  Entity* bg_ = Entity_create(_screenWidth/2, _screenHeight/2, bg_png.width*2, bg_png.height*2, pivot_center);
  Sprite_create(bg_, &bg_png);

  Entity* chicken_ = Entity_create(_screenWidth/2, _screenHeight/2, 64, 64, pivot_center);
  Sprite_create(chicken_, &chicken_png);
  Sprite_createAnimation(chicken_->ptr_component[0], 6, 2);
  //Animation_addCLip(chicken_->ptr_component[0], 0, 2, 10, "fall");
  //Animation_playClip(chicken_->ptr_component[0], "fall");
  
  Physics_create(chicken_);

  Entity* arrEntity[] = {bg_, chicken_};

  SetTargetFPS(_targetFps);
  while (!WindowShouldClose()) {

    for (size_t i = 0; i < entities; i++) { 
      if (arrEntity[i]->component_mask[1] == '1')
        Physics_update(arrEntity[i]->ptr_component[1]);

      /*
      if (arrEntity[i]->component_mask[0] == '1')
        Sprite_update(arrEntity[i]->ptr_component[0], &_targetFps);
        */
    }    

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
    {
      chicken_->y = 0;
    }

    BeginDrawing();
    ClearBackground(BLACK);
    for (size_t i = 0; i < entities; i++) {
        if (arrEntity[i]->component_mask[0] == '1')
          Sprite_draw(arrEntity[i]->ptr_component[0]);
        
    }
    EndDrawing();
  }

  //Entity_destroy(&arrEntity[0]);

  UnloadTexture(bg_png);
  UnloadTexture(chick_png);
  UnloadTexture(chicken_png);
  CloseWindow();
  
  return 0;
}
