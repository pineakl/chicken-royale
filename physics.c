#include "engine.h"
#include "stdlib.h"
#include <stdio.h>

void Physics_create(Entity *entity)
{
  int component_id = 1;
  Physics* physics = (Physics*)malloc(sizeof(Physics)); 
  if (physics != NULL)
  {
    physics->accG = 1;
    physics->curG = 0;
    physics->maxG = 10;

    entity->ptr_component[component_id] = physics;
    entity->component_mask[component_id] = '1';
    physics->entity = entity;
  }
}

void Physics_update(Physics *self)
{
    if (self->curG < self->maxG)
      self->curG += self->accG;
    else
      self->curG = self->maxG;

    self->entity->y += self->curG / 2;
}

void Physics_destroy(Physics *self)
{
  free(self);
  self = NULL;
}
