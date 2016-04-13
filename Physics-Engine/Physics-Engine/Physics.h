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

	glm::vec2 isColliding(Rectangle* r1, Rectangle* r2);

	glm::vec2 rotate(const glm::vec2 pos, const float angle);

	void step(Rectangle& r, float dt);
}

#endif