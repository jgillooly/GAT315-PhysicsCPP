#pragma once
#include "Body.h"

extern Body* jgBodies;
extern int jgBodyCount;
extern Vector2 jgGravity;

Body* CreateBody();
void DestroyBody(Body* body);