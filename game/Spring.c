#include "Spring.h"
#include "Body.h"
#include "assert.h"
#include "raymath.h"
#include <stdlib.h>

jgSpring_t* jgsprings = NULL;
jgSpring_t* CreateSpring(struct Body* body1, struct Body* body2, float rest, float k) {

	jgSpring_t* spring = (jgSpring_t*)malloc(sizeof(jgSpring_t));
	assert(spring);
	memset(spring, 0, sizeof(jgSpring_t));
	
	spring->body1 = body1;
	spring->body2 = body2;
	spring->restLength = rest;
	spring->k = k;

	return spring;
}

void AddSpring(jgSpring_t* spring) {
	assert(spring);
	spring->prev = NULL;
	spring->next = jgsprings;
	if (jgsprings != NULL) {
		jgsprings->prev = spring;
	}
	jgsprings = spring;

}

void DestroySpring(jgSpring_t* spring) {
	assert(spring);
	if (spring->prev != NULL) spring->prev->next = spring->next;
	if (spring->next != NULL) spring->next->prev = spring->prev;
	if (jgsprings == spring) jgsprings = spring->next;
	free(spring);
}

void ApplySpringForce(jgSpring_t* springs) {
	for (jgSpring_t* spring = springs; spring; spring = spring->next)
	{
		Vector2 direction = Vector2Subtract(spring->body1->Position, spring->body2->Position);
		if (direction.x == 0 && direction.y == 0) continue;

		float length = Vector2Length(direction);
		float x = length - spring->restLength;
		float force = -spring->k * x;

		Vector2 ndirection = Vector2Normalize(direction);

		ApplyForce(spring->body1, Vector2Scale(ndirection, force), FM_FORCE);
		ApplyForce(spring->body2, Vector2Scale(Vector2Negate(ndirection), force), FM_FORCE);
	}
}

void ApplySpringForcePosition(Vector2 position, Body* body, float restLength, float k, float damping)
{
	// Check if the body pointer is null; if so, exit the function
	if (!body) return;

	// Calculate the direction vector from the body's position to the given position
	Vector2 direction = Vector2Subtract(position, body->Position);

	// If the direction vector is zero (i.e., positions are the same), exit the function
	if (direction.x == 0 && direction.y == 0) return;

	// Calculate the length of the direction vector (distance between the two positions)
	float length = Vector2Length(direction);

	// Calculate the displacement from the rest length
	float x = length - restLength;
	float force = -k * x;

	Vector2 ndirection = Vector2Normalize(direction);

		// Calculate the damping force (opposing force due to velocity)
	float dampingForce = damping * Vector2DotProduct(body->Velocity, ndirection);
	
		// Calculate the total force by combining spring force and damping force
	float totalForce = force + dampingForce;

		// Apply the total force to the body in the direction of the normalized vector
		ApplyForce(body, Vector2Scale(ndirection, -totalForce), FM_FORCE);
}