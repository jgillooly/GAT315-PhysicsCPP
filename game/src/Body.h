#pragma once
#include "raylib.h"

typedef struct Body
{
	Vector2 Position;
	Vector2 Velocity;
	Vector2 Force;

	struct Body* next;
	struct Body* prev;
} Body;