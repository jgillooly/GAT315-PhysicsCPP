#pragma once
#include "raylib.h"
#include <raymath.h>

typedef enum {
	STATIC,
	KINEMATIC,
	DYNAMIC
} bodyType;

typedef struct Body
{
	bodyType type;
	Vector2 Position;
	Vector2 Velocity;
	Vector2 Force;

	float mass;
	float inverseMass;

	struct Body* next;
	struct Body* prev;
} Body;

inline void ApplyForce(Body* body, Vector2 force) {
	body->Force = Vector2Add(body->Force, force);
}

inline void ClearForce(Body* body) {
	body->Force = Vector2Zero();
}