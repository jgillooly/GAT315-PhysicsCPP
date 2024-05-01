#pragma once
#include "Body.h"
#include "raymath.h"

void ExplicitEuler(Body* body, float timestep) {
	body->Position = Vector2Add(body->Position, Vector2Scale(body->Velocity, timestep));
	body->Velocity = Vector2Add(body->Velocity, Vector2Scale(Vector2Scale(body->Force, 1/body->mass), timestep));
}