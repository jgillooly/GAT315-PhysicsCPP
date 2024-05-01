#include "World.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

Body* jgBodies = NULL;
int jgBodyCount = 0;

Body* CreateBody() {
	Body* body = (Body*)malloc(sizeof(Body));
	assert(body);

	memset(body, 0, sizeof(Body));

	body->prev = NULL;
	body->next = jgBodies;
	if (jgBodies != NULL) {
		jgBodies->prev = body;
	}
	jgBodyCount++;
	jgBodies = body;


	return body;
}
void DestroyBody(Body* body) {
	assert(body);
	if (body->prev != NULL) body->prev->next = body->next;
	if (body->next != NULL) body->next->prev = body->prev;
	if (jgBodies == body) jgBodies = body->next;
	jgBodyCount--;
	free(body);
}