#include "Body.h"
#include "Mathf.h"
#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>
#include <assert.h>
#include <World.h>

#define MAX_BODIES 1000


int main(void)
{
	InitWindow(1280, 720, "Physics Engine");
	SetTargetFPS(60);
	
	int bodyCount = 0;

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
			newbody->Velocity = CreateVector2(GetRandomFloatValue(-5, 5), GetRandomFloatValue(-5, 5));
		}

		//draw
		BeginDrawing();
		ClearBackground(BLACK);
		//stats
		DrawText(TextFormat("FPS: %.2f (%.2fms)", fps, 1000/fps), 10, 10, 20, LIME);
		DrawText(TextFormat("FRAME: (%.4f)", dt), 10, 30, 20, LIME);

		DrawCircle((int)position.x, (int)position.y, 10, RED);
		Body* currentbody = bodies;
		while (currentbody) {
			currentbody->Position = Vector2Add(currentbody->Position, currentbody->Velocity);
			DrawCircle((int)currentbody->Position.x, (int)currentbody->Position.y, 10, RED);
			currentbody = currentbody->next;
		}
		EndDrawing();
	}
	CloseWindow();
	while (bodies) {
		free(bodies);
	}
	return 0;
}