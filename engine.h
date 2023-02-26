#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <stdlib.h>
#include "raylib.h"

/**
 * Root Entity
 */
extern int entities;
typedef struct Entity 
{
  int x, y, w, h;
  Vector2 origin;
  void* ptr_component[2];
} Entity;

Entity* Entity_create(int x, int y, int width, int height, Vector2 pivot);
void Entity_destroy(Entity* entity);

/**
 * Sprite and Animation Component
 */
typedef struct AnimationClip
{
  const char* name;
  unsigned int frames;
  unsigned int speed;
} AnimationClip;

typedef struct Sprite{ 
  Entity* entity_;
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

void Sprite_create(Entity* entity, Texture2D* texture);
AnimationClip* Sprite_createAnimation(Sprite* self, unsigned int cells, unsigned int clips);
void Animation_addCLip(Sprite* self, unsigned int clipIndex, unsigned int frames, unsigned int speed, const char* name);
void Animation_playClip(Sprite* self, char* name);
void Sprite_update(Sprite* self, const int* frameRate);
void Sprite_draw(Sprite* self);
void Sprite_destroy(Sprite* self);

/**
 * Physics Component
 */
typedef struct Physics 
{
  Entity* entity;
} Physics ;

Physics* Physics_create(Entity* entity);

#endif // _ENGINE_H_
