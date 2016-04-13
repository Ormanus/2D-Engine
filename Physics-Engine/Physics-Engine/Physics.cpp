#include "Physics.h"

#define PI 3.14159265

namespace phe
{
	glm::vec2 rotate(const glm::vec2 pos, const float angle)
	{
		float dir = atan2f(pos.y, pos.x);
		float dist = sqrt(pos.x*pos.x + pos.y*pos.y);

		return glm::vec2(cos(dir + angle)*dist, sin(dir + angle)*dist);
	}

	glm::vec2 isColliding(Rectangle* r1, Rectangle* r2)
	{
		float halfPI = PI / 2.0f;

		glm::vec2 cornersA[4];
		glm::vec2 p1A = r1->center + rotate(glm::vec2(-r1->w / 2.0f, -r1->h / 2.0f), r1->rotation);
		glm::vec2 p2A = r1->center + rotate(glm::vec2(-r1->w / 2.0f, +r1->h / 2.0f), r1->rotation);
		glm::vec2 p3A = r1->center + rotate(glm::vec2(+r1->w / 2.0f, +r1->h / 2.0f), r1->rotation);
		glm::vec2 p4A = r1->center + rotate(glm::vec2(+r1->w / 2.0f, -r1->h / 2.0f), r1->rotation);
		cornersA[0].x = p1A.x;
		cornersA[0].y = p1A.y;
		cornersA[1].x = p2A.x;
		cornersA[1].y = p2A.y;
		cornersA[2].x = p3A.x;
		cornersA[2].y = p3A.y;
		cornersA[3].x = p4A.x;
		cornersA[3].y = p4A.y;

		glm::vec2 cornersB[4];
		glm::vec2 p1B = r2->center + rotate(glm::vec2(-r2->w / 2.0f, -r2->h / 2.0f), r2->rotation);
		glm::vec2 p2B = r2->center + rotate(glm::vec2(-r2->w / 2.0f, +r2->h / 2.0f), r2->rotation);
		glm::vec2 p3B = r2->center + rotate(glm::vec2(+r2->w / 2.0f, +r2->h / 2.0f), r2->rotation);
		glm::vec2 p4B = r2->center + rotate(glm::vec2(+r2->w / 2.0f, -r2->h / 2.0f), r2->rotation);
		cornersB[0].x = p1B.x;
		cornersB[0].y = p1B.y;
		cornersB[1].x = p2B.x;
		cornersB[1].y = p2B.y;
		cornersB[2].x = p3B.x;
		cornersB[2].y = p3B.y;
		cornersB[3].x = p4B.x;
		cornersB[3].y = p4B.y;

		glm::vec2 axis[4];

		axis[0].x = cos(r1->rotation);
		axis[0].y = sin(r1->rotation);
		axis[1].x = cos(r1->rotation + halfPI);
		axis[1].y = sin(r1->rotation + halfPI);
		axis[2].x = cos(r2->rotation);
		axis[2].y = sin(r2->rotation);	   
		axis[3].x = cos(r2->rotation + halfPI);
		axis[3].y = sin(r2->rotation + halfPI);

		glm::vec2 collision = glm::vec2(FLT_MAX);

		for (int i = 0; i < 4; i++)
		{
			glm::vec2 projectedA[4];
			glm::vec2 projectedB[4];

			//A
			for (int j = 0; j < 4; j++)
			{
				projectedA[j] = glm::dot(cornersA[j], axis[i]) * axis[i];
			}

			//B
			for (int j = 0; j < 4; j++)
			{
				projectedB[j] = glm::dot(cornersB[j], axis[i]) * axis[i];
			}

			//min and max
			float minA = glm::dot(axis[i], projectedA[0]);
			for (int j = 1; j < 4; j++)
			{
				minA = glm::min(minA, glm::dot(axis[i], projectedA[j]));
			}

			float minB = glm::dot(axis[i], projectedB[0]);
			for (int j = 1; j < 4; j++)
			{
				minB = glm::min(minB, glm::dot(axis[i], projectedB[j]));
			}

			float maxA = glm::dot(axis[i], projectedA[0]);
			for (int j = 1; j < 4; j++)
			{
				maxA = glm::max(maxA, glm::dot(axis[i], projectedA[j]));
			}

			float maxB = glm::dot(axis[i], projectedB[0]);
			for (int j = 1; j < 4; j++)
			{
				maxB = glm::max(maxB, glm::dot(axis[i], projectedB[j]));
			}

			if (!(maxA >= minB && minA <= maxB))
			{
				return glm::vec2(0.0);
			}
			else
			{
				float overlap = glm::min(abs(maxA - minB), abs(minA - maxB));
				collision = glm::min(collision, axis[i]*overlap);
			}
		}
		return collision;
	}

	void step(Rectangle& r1, float dt)
	{
		r1.center.x += r1.velocity.x * dt;
		r1.center.y += r1.velocity.y * dt;

		r1.rotation += r1.angularVelocity * dt;
	}
}