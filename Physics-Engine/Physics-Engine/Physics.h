#ifndef PHYSICS_H
#define PHYSICS_H

#include <stdlib.h>
#include <stdio.h>
#include <glm\glm.hpp>

namespace phe
{
	struct Rectangle
	{
		glm::vec2 center;
		glm::vec2 velocity;
		float w;
		float h;
		float rotation;
		float angularVelocity;
		float mass;
	};

	glm::vec4 isColliding(Rectangle* r1, Rectangle* r2);

	glm::vec2 rotate(const glm::vec2 pos, const float angle);

	void collide(Rectangle* r1, Rectangle* r2, glm::vec4 collision);

	void step(Rectangle& r, const float dt);

	bool isIntersecting(const glm::vec2 a, const glm::vec2 b, const glm::vec2 c, const glm::vec2 d);
}

#endif