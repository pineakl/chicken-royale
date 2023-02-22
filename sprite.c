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

  sprite_count++;

  return sprite_;
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
