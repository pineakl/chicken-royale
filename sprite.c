#include "engine.h"
#include <raylib.h>
#include <stdlib.h>

int sprite_count = 0;

Sprite* Sprite_create(Texture2D* texture, int x, int y, int width, int height, Vector2 pivot) 
{
  Sprite* sprite_ = (Sprite*) malloc(sizeof(Sprite));
  sprite_->x = x;
  sprite_->y = y; 
  
   Vector2 origin = { pivot.x * width, pivot.y * height };
  sprite_->origin = origin;

  sprite_->srcTexture = texture;
  
  Rectangle srcRect = { 0.0f, 0.0f, (float)texture->width, (float)texture->height };
  sprite_->srcRect = srcRect;

  Rectangle destRect = { (float)x, (float)y, (float)width, (float)height };
  sprite_->destRect = destRect;

  sprite_->animated = false;

  sprite_count++;

  return sprite_;
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
}

void Sprite_draw(Sprite *self)
{
  Texture2D* pTexture = self->srcTexture;
  DrawTexturePro(*pTexture, self->srcRect, self->destRect, self->origin, 0, WHITE);
}

void Sprite_destroy(Sprite *self)
{
  sprite_count--;
  free(self->clips_);
  self->clips_ = NULL;
  free(self);
  self = NULL;
}
