#include <stdio.h>
#include "engine.h"
#include "raylib.h"

int entities;

Entity* Entity_create(int x, int y, int width, int height, Vector2 pivot)
{
  Entity* entity = (Entity*)malloc(sizeof(Entity));

  if (entity != NULL)
  {
    entity->x = x;
    entity->y = y;
    entity->w = width;
    entity->h = height;

    Vector2 origin = { pivot.x * width, pivot.y * height };
    entity->origin = origin;
    printf("origin %f \n", origin.x);
    
    entities++;

    return entity;
  }
  else
  {
    return NULL;
  }
}

void Entity_destroy(Entity *entity)
{
  entities--;

  // free all childs
  Sprite* sprite = (Sprite*)entity->ptr_component[0];
  printf("clearing %p\n", sprite);
  Sprite_destroy(sprite);
}
