#include "Body.h"
#include "Mathf.h"
#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>
#include <assert.h>
#include <World.h>
#include "integrate.h"
#include "Force.h"
#include "render.h"
#include "editor.h"
#include "Spring.h"
#include "Collision.h"
#include "contact.h"


#define MAX_BODIES 1000


int main(void)
{
	InitWindow(1280, 720, "Physics Engine");
	InitEditor();
	SetTargetFPS(60);

	//initialize world
	jgGravity = (Vector2){ 0,-10 };

	Body* selectedBody = NULL;
	Body* connectBody = NULL;

	Vector2 prevPos = Vector2Zero();
	//game loop
	while (!WindowShouldClose())
	{
		//update
		float dt = GetFrameTime();
		float fps = (float)GetFPS();
		
		Vector2 position = GetMousePosition();
		ncScreenZoom += GetMouseWheelMove() * 0.25f;
		ncScreenZoom = Clamp(ncScreenZoom, 0.1f, 10.0f);
		UpdateEditor(position);
		
		selectedBody = GetBodyIntersect(jgBodies, position);
		if (selectedBody) {
			Vector2 screen = ConvertWorldToScreen(selectedBody->Position);
			DrawCircleLines(screen.x, screen.y, ConvertWorldToPixel(selectedBody->mass * 0.5f) + 5, YELLOW);
		}

		if (IsMouseButtonPressed(0)) {
			Body* newbody = CreateBody(ConvertScreenToWorld(position), GetRandomFloatValue(state.MassMinValue, state.MassMaxValue), state.BodyTypeActive);
			AddBody(newbody);
			newbody->gravityScale = state.GravityScaleValue;
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
			//ApplyForce(newbody, (Vector2) { GetRandomFloatValue(-200, 200), GetRandomFloatValue(-200, 200) }, FM_VELOCITY);
			//newbody->Velocity = );
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && selectedBody) {
			connectBody = selectedBody;
		}
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && connectBody) {
			DrawLineBodyToPosition(connectBody, position);
		}
		if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT) && connectBody) {
			if (selectedBody && selectedBody != connectBody) {
				jgSpring_t* spring = CreateSpring(selectedBody, connectBody, 1, 10);
				AddSpring(spring);
			}
		}
		/*else if (IsMouseButtonDown(1)) {
			Body* newbody = CreateBody();
			newbody->Position = ConvertScreenToWorld(position);
			newbody->mass = GetRandomFloatValue(1, 1);
			newbody->inverseMass = 1 / newbody->mass;
			newbody->type = BT_DYNAMIC;
			newbody->damping = 0.5f;
			newbody->gravityScale = 1.0f;
			newbody->color = ORANGE;
		}*/


		Body* currentbody = jgBodies;
		//apply gravitation
		//ApplyGravitation(jgBodies, 20);

		ApplySpringForce(jgsprings);

		for (Body* body = jgBodies; body; body = body->next) {
			Step(body, dt);
		}

		//collision
		ncContact_t* Contacts = NULL;
		CreateContacts(jgBodies, &Contacts);


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

		//DrawCircle((int)position.x, (int)position.y, 10, RED);
		//draw bodies
		currentbody = jgBodies;
		for (Body* body = jgBodies; body; body = body->next) {
			Vector2 screen = ConvertWorldToScreen(body->Position);
			DrawCircle((int)screen.x, (int)screen.y, ConvertWorldToPixel(body->mass *0.5f), body->color);
			currentbody = currentbody->next;
		}

		for (jgSpring_t* spring = jgsprings; spring; spring = spring->next) {
			Vector2 screen1 = ConvertWorldToScreen(spring->body1->Position);
			Vector2 screen2 = ConvertWorldToScreen(spring->body2->Position);
			DrawLine(screen1.x, screen1.y, screen2.x, screen2.y, LIME);

		}

		for (ncContact_t* contact = Contacts; contact; contact = contact->next) {
			Vector2 screen = ConvertWorldToScreen(contact->body1->Position);
			DrawCircle((int)screen.x, (int)screen.y, ConvertWorldToPixel(contact->body1->mass*0.5f), RED);
		}
		DrawEditor(position);
		EndDrawing();
		prevPos = position;
	}
	CloseWindow();
	//while (jgBodies) {
	//	free(jgBodies);
	//}
	return 0;
}