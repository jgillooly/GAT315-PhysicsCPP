#include "World.h"

#include <stdlib.h>
#include <assert.h>

Body* bodies = NULL;
int bodyCount = 0;

Body* CreateBody() {
	Body* body = (Body*)malloc(sizeof(Body));
	assert(body);
	body->prev = NULL;
	body->next = bodies;
	if (bodies != NULL) {
		bodies->prev = body;
	}
	bodyCount++;
	bodies = body;


	return body;
}
void DestroyBody(Body* body) {
	assert(body);
	if (body->prev != NULL) body->prev->next = body->next;
	if (body->next != NULL) body->next->prev = body->prev;
	if (bodies == body) bodies = body->next;
	bodyCount--;
	free(body);
}