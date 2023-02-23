#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <stdlib.h>
#include "raylib.h"

extern int sprite_count;

typedef struct Sprite{
  int x, y;
  int w, h;
  Vector2 origin;
  Texture2D* srcTexture;
  Rectangle srcRect, destRect;

  bool animated;
  int frameCounter;
  int frameCells;
  int animationSpeed;
  int currentFrame;

} Sprite;
Sprite* Sprite_create(Texture2D* texture, int x, int y, int width, int height, Vector2 pivot);
void Sprite_createAnimation(Sprite* self, int frameCells, int animationSpeed);
void Sprite_update(Sprite* self, const int* frameRate);
void Sprite_draw(Sprite* self);
void Sprite_destroy(Sprite* self);

#endif // _ENGINE_H_
