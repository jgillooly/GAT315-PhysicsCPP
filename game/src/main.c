#include "Body.h"
#include "Mathf.h"
#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>
#include <assert.h>
#include <World.h>
#include "integrate.h"

#define MAX_BODIES 1000


int main(void)
{
	InitWindow(1280, 720, "Physics Engine");
	SetTargetFPS(60);

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
			//ApplyForce(newbody, CreateVector2(GetRandomFloatValue(-50, 50), GetRandomFloatValue(-50, 50)));
			
			//newbody->Velocity = );
		}


		Body* currentbody = jgBodies;
		while (currentbody) {
			ApplyForce(currentbody, CreateVector2(0, -200));
			currentbody = currentbody->next;
		}

		currentbody = jgBodies;
		while (currentbody) {
			ExplicitEuler(currentbody, dt);
			ClearForce(currentbody);
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
		while (currentbody) {
			
			DrawCircle((int)currentbody->Position.x, (int)currentbody->Position.y, currentbody->mass, RED);
			currentbody = currentbody->next;
		}
		EndDrawing();
	}
	CloseWindow();
	//while (jgBodies) {
	//	free(jgBodies);
	//}
	return 0;
}