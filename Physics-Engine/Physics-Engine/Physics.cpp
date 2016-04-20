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

	glm::vec4 isColliding(Rectangle* r1, Rectangle* r2)
	{
		const float halfPI = PI / 2.0f;

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

		for (int k = 0; k < 4; k++) //k = point index
		{
			bool pointFound = true;
			glm::vec4 point = glm::vec4(cornersA[k], 0.0f, 0.0f);
			for (int i = 2; i < 4; i++) //i = axis index
			{
				//project cornersB to
				//axis 2 and 3
				//find min and max
				//project a single cornerA to
				//the same axis and check if it's between min and max
				glm::vec2 projectedB[4];
				for (int j = 0; j < 4; j++) //j = corner index
				{
					projectedB[j] = glm::dot(cornersB[j], axis[i]) * axis[i];
				}

				float maxB = glm::dot(axis[i], projectedB[0]);
				float minB = glm::dot(axis[i], projectedB[0]);
				for (int j = 1; j < 4; j++)
				{
					float dot = glm::dot(axis[i], projectedB[j]);
					minB = glm::min(minB, dot);
					maxB = glm::max(maxB, dot);
				}


				glm::vec2 projectedPoint = glm::dot(glm::vec2(point.x, point.y), axis[i]) * axis[i];
				float scalar = glm::dot(axis[i], projectedPoint);

				if (!(scalar < maxB && scalar > minB) && !(scalar > maxB && scalar < minB))
				{
					pointFound = false;
					break;
				}
			}
			if (pointFound)
			{
				for (int j = 0; j < 4; j++)
				{
					glm::vec2 p1 = cornersB[j];
					glm::vec2 p2 = cornersB[(j + 1) % 4];
					if (isIntersecting(glm::vec2(point), r1->center, p2, p1))
					{
						glm::vec2 n = glm::normalize(glm::vec2(p1.y - p2.y, p2.x - p1.x));
						point.z = n.x;
						point.w = n.y;
						printf("line found (A)\n");
					}
				}
				printf("point found (A)\n");
				return point;
			}
		}
		for (int k = 0; k < 4; k++) //k = point index
		{
			bool pointFound = true;
			glm::vec4 point = glm::vec4(cornersB[k], 0.0f, 0.0f);
			for (int i = 0; i < 2; i++) //i = axis index
			{
				glm::vec2 projectedA[4];
				for (int j = 0; j < 4; j++) //j = corner index
				{
					projectedA[j] = glm::dot(cornersA[j], axis[i]) * axis[i];
				}

				float maxA = glm::dot(axis[i], projectedA[0]);
				float minA = glm::dot(axis[i], projectedA[0]);
				for (int j = 1; j < 4; j++)
				{
					float dot = glm::dot(axis[i], projectedA[j]);
					minA = glm::min(minA, dot);
					maxA = glm::max(maxA, dot);
				}


				glm::vec2 projectedPoint = glm::dot(glm::vec2(point.x, point.y), axis[i]) * axis[i];
				float scalar = glm::dot(axis[i], projectedPoint);

				if (!(scalar < maxA && scalar > minA) && !(scalar > maxA && scalar < minA))
				{
					pointFound = false;
					break;
				}
			}
			if (pointFound)
			{
				for (int j = 0; j < 4; j++)
				{
					glm::vec2 p1 = cornersA[j];
					glm::vec2 p2 = cornersA[(j + 1) % 4];
					if (isIntersecting(glm::vec2(point), r2->center, p1, p2))
					{
						glm::vec2 n = glm::normalize(glm::vec2(p1.y - p2.y, p2.x - p1.x));
						point.z = n.x;
						point.w = n.y;
						printf("line found (B)\n");
					}
				}
				printf("point found (B)\n");
				return point;
			}
		}

		return glm::vec4(0);
	}

	void step(Rectangle& r1, const float dt)
	{
		r1.center.x += r1.velocity.x * dt;
		r1.center.y += r1.velocity.y * dt;

		r1.rotation += r1.angularVelocity * dt;
	}

	void collide(Rectangle* a, Rectangle* b, glm::vec4 collision)
	{
		glm::vec2 p = glm::vec2(collision.x, collision.y);
		glm::vec2 n = glm::vec2(collision.z, collision.w);

		a->mass = a->w * a->h; //mass 1
		b->mass = b->w * b->h; //mass 2

		//distances to the centers of mass
		float r1 = glm::length(a->center - p);
		float r2 = glm::length(b->center - p);

		//velocities at the collision point
		const float halfPI = PI / 2.0f;

		glm::vec2 normalOfRadiusA = glm::vec2(cos(a->rotation + halfPI), sin(a->rotation + halfPI)) * r1;
		glm::vec2 normalOfRadiusB = glm::vec2(cos(b->rotation + halfPI), sin(b->rotation + halfPI)) * r2;

		glm::vec2 vp1 = a->velocity + normalOfRadiusA * a->angularVelocity;
		glm::vec2 vp2 = b->velocity + normalOfRadiusB * b->angularVelocity;

		float normalVelocity = glm::dot((vp1 - vp2), n);

		float e = 1.0f; //superball

		assert(glm::length(n) > 0.01f);

		float momentOfInertiaA = 1.0f / 12.0f*a->mass*(a->w*a->w + a->h*a->h);
		float momentOfInertiaB = 1.0f / 12.0f*b->mass*(b->w*b->w + b->h*b->h);

		float j = glm::dot(-(1 + e), normalVelocity) / (glm::dot(n, n*(1.0f / a->mass + 1.0f / b->mass))
			+ pow(glm::dot(normalOfRadiusA, n), 2) / momentOfInertiaA
			+ pow(glm::dot(normalOfRadiusB, n), 2) / momentOfInertiaB);

		printf("j = %f\n", j);

		a->velocity = a->velocity + j / a->mass * n;
		b->velocity = b->velocity - j / b->mass * n;

		a->angularVelocity = a->angularVelocity + (glm::dot(normalOfRadiusA, j*n) / momentOfInertiaA);
		b->angularVelocity = b->angularVelocity - (glm::dot(normalOfRadiusB, j*n) / momentOfInertiaB);
	}

	bool isIntersecting(const glm::vec2 a, const glm::vec2 b, const glm::vec2 c, const glm::vec2 d)
	{
		//TODO: optimoi!

		float p0_x = a.x;
		float p0_y = a.y;

		float p1_x = b.x;
		float p1_y = b.y;

		float p2_x = c.x;
		float p2_y = c.y;

		float p3_x = d.x;
		float p3_y = d.y;

		float s1_x, s1_y, s2_x, s2_y;
		s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
		s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

		float s, t;
		s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
		t = (s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

		if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
		{
			return true;
		}

		return false; // No collision
	}
}