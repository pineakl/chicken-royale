#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <stdlib.h>
#include "raylib.h"

extern int sprite_count;

typedef struct AnimationClip
{
  const char* name;
  unsigned int frames;
  unsigned int speed;
} AnimationClip;

typedef struct Sprite{
  int x, y;
  int w, h;
  Vector2 origin;
  Texture2D* srcTexture;
  Rectangle srcRect, destRect;

  bool animated;
  int frameCounter;
  int frameCells;
  int currentFrame;
  unsigned int clipCount;
  AnimationClip* clips_;
  int currentClip;

} Sprite;
Sprite* Sprite_create(Texture2D* texture, int x, int y, int width, int height, Vector2 pivot);
AnimationClip* Sprite_createAnimation(Sprite* self, unsigned int cells, unsigned int clips);
void Animation_addCLip(Sprite* self, unsigned int clipIndex, unsigned int frames, unsigned int speed, const char* name);
void Animation_playClip(Sprite* self, char* name);
void Sprite_update(Sprite* self, const int* frameRate);
void Sprite_draw(Sprite* self);
void Sprite_destroy(Sprite* self);

#endif // _ENGINE_H_
