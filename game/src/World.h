#pragma once
#include "Body.h"

extern Body* jgBodies;
extern int jgBodyCount;

Body* CreateBody();
void DestroyBody(Body* body);