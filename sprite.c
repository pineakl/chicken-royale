#include "engine.h"
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>

void Sprite_create(Entity *entity, Texture2D *texture) 
{
  int component_id = 0;
  Sprite* sprite_ = (Sprite*) malloc(sizeof(Sprite)); 

  if (sprite_ != NULL)
  {
    sprite_->srcTexture = texture;
    
    Rectangle srcRect = { 0.0f, 0.0f, (float)texture->width, (float)texture->height };
    sprite_->srcRect = srcRect;

    Rectangle destRect = { (float)entity->x, (float)entity->y, (float)entity->w, (float)entity->h };
    sprite_->destRect = destRect;
    sprite_->animated = false;
    
    entity->ptr_component[component_id] = sprite_;
    entity->component_mask[component_id] = '1';
    sprite_->entity_ = entity;
  }
}

AnimationClip* Sprite_createAnimation(Sprite *self, unsigned int cell, unsigned int clips)
{
  // create horizontal slicing
  self->animated = true;
  self->frameCounter = 0;
  self->frameCells = cell;
  self->currentFrame = 0;
  
  self->clipCount = clips;
  AnimationClip* clips_ = (AnimationClip*) malloc(sizeof(AnimationClip) * self->clipCount);

  int newRectWidth = self->srcRect.width / self->frameCells;
  int newRectHeight = self->srcRect.height / self->clipCount;
  self->srcRect.width = newRectWidth;
  self->srcRect.height = newRectHeight;

  return clips_;
}

void Animation_addCLip(Sprite *self, unsigned int clipIndex, unsigned int frames, unsigned int speed, const char* name)
{
  if (self->clips_ != NULL)
  {
    if (clipIndex < self->clipCount)
    {
      self->clips_[clipIndex].name = name;
      if (frames > self->frameCells)
        frames = self->frameCells;
      self->clips_[clipIndex].frames = frames;
      self->clips_[clipIndex].speed = speed;
    }
  }
}

void Animation_playClip(Sprite *self, char *name)
{
  for (size_t i = 0; i < self->clipCount; i++) {
    if (self->clips_[i].name == name)
    {
      self->currentClip = i;
      self->currentFrame = self->clips_[i].frames - 1;
      return;
    }
  }
}

void Sprite_update(Sprite *self, const int *frameRate)
{
  printf("debug\n");
  if (self->animated)
  {
    self->frameCounter++; 
    if (self->frameCounter >= *frameRate/self->clips_[self->currentClip].speed)
    {
      self->frameCounter = 0;
      self->currentFrame = (self->currentFrame + 1) % self->clips_[self->currentClip].frames;
      self->srcRect.x = self->srcRect.width * self->currentFrame;
      self->srcRect.y = self->srcRect.height * self->currentClip;
    }
  }

  //self->destRect.y = self->entity_->y;
}

void Sprite_draw(Sprite *self)
{
  Texture2D* pTexture = self->srcTexture;
  self->destRect.y = self->entity_->y;
  DrawTexturePro(*pTexture, self->srcRect, self->destRect, self->entity_->origin, 0, WHITE);
}

void Sprite_destroy(Sprite *self)
{
  /*
  free(self->clips_);
  self->clips_ = NULL;
  free(self);
  self = NULL;
    */
  free(self);
  self = NULL;
}
