#include <stdio.h>
#include "engine.h"
#include <raylib.h>

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

void Sprite_createAnimation(Sprite *self, int cell, int speed)
{
  // create horizontal slicing
  self->animated = true;
  self->frameCounter = 0;
  self->frameCells = cell;
  self->animationSpeed = speed;
  self->currentFrame = 0;

  int newRect = self->srcRect.width / self->frameCells;
  self->srcRect.width = newRect; 
}

void Sprite_update(Sprite *self, const int *frameRate)
{
  if (self->animated)
  {
    self->frameCounter++; 
    if (self->frameCounter >= *frameRate/self->animationSpeed)
    {
      self->frameCounter = 0;
      self->currentFrame = (self->currentFrame + 1) % self->frameCells;
      self->srcRect.x = self->srcRect.width * self->currentFrame;
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
  free(self);
}
