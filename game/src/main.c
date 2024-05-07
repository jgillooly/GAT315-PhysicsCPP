#include "Body.h"
#include "Mathf.h"
#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>
#include <assert.h>
#include <World.h>
#include "integrate.h"
#include "Force.h"

#define MAX_BODIES 1000


int main(void)
{
	InitWindow(1280, 720, "Physics Engine");
	SetTargetFPS(60);

	//initialize world
	jgGravity = (Vector2){ 0,0 };

	Vector2 prevPos = Vector2Zero();
	//game loop
	while (!WindowShouldClose())
	{
		//update
		float dt = GetFrameTime();
		float fps = (float)GetFPS();
		
		Vector2 position = GetMousePosition();
		if (IsMouseButtonDown(0)) {
			Body* newbody = CreateBody();
			newbody->Position = position;
			newbody->mass = GetRandomFloatValue(1, 10);
			newbody->inverseMass = 1 / newbody->mass;
			newbody->type = BT_DYNAMIC;
			newbody->damping = 0.5f;
			newbody->gravityScale = 1.0f;
			int num = (rand() % (3 - 1 + 1)) + 1;
			switch (num)
			{
			case 1:
				newbody->color = RED;
				break;
			case 2:
				newbody->color = GREEN;
				break;
			case 3:
				newbody->color = BLUE;
				break;
			}
			ApplyForce(newbody, (Vector2) { GetRandomFloatValue(-200, 200), GetRandomFloatValue(-200, 200) }, FM_VELOCITY);
			//newbody->Velocity = );
		}
		else if (IsMouseButtonDown(2) && !Vector2Equals(prevPos, position)) {
			Body* newbody = CreateBody();
			newbody->Position = position;
			newbody->mass = GetRandomFloatValue(1, 10);
			newbody->inverseMass = 1 / newbody->mass;
			newbody->type = BT_DYNAMIC;
			newbody->damping = 0.5f;
			newbody->gravityScale = 1.0f;
			newbody->color = RED;
			ApplyForce(newbody, Vector2Scale(Vector2Subtract(position, prevPos), 100), FM_VELOCITY);
		}
		else if (IsMouseButtonDown(1)) {
			Body* newbody = CreateBody();
			newbody->Position = position;
			newbody->mass = GetRandomFloatValue(1, 1);
			newbody->inverseMass = 1 / newbody->mass;
			newbody->type = BT_DYNAMIC;
			newbody->damping = 0.5f;
			newbody->gravityScale = 1.0f;
			newbody->color = ORANGE;
		}


		Body* currentbody = jgBodies;
		//apply gravitation
		//ApplyGravitation(jgBodies, 10);

		for (Body* body = jgBodies; body; body = body->next) {
			Step(body, dt);
		}

		currentbody = jgBodies;
		while (currentbody) {
			
			
			currentbody = currentbody->next;
		}


		//draw
		BeginDrawing();
		ClearBackground(BLACK);
		//stats
		DrawText(TextFormat("FPS: %.2f (%.2fms)", fps, 1000/fps), 10, 10, 20, LIME);
		DrawText(TextFormat("FRAME: (%.4f)", dt), 10, 30, 20, LIME);

		DrawCircle((int)position.x, (int)position.y, 10, RED);
		//draw bodies
		currentbody = jgBodies;
		for (Body* body = jgBodies; body; body = body->next) {	
			DrawCircle((int)currentbody->Position.x, (int)currentbody->Position.y, currentbody->mass, currentbody->color);
			currentbody = currentbody->next;
		}
		EndDrawing();
		prevPos = position;
	}
	CloseWindow();
	//while (jgBodies) {
	//	free(jgBodies);
	//}
	return 0;
}