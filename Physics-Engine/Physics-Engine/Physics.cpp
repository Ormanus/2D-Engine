#include "Physics.h"

#define PI 3.14159265

namespace phe
{
	bool isColliding(Rectangle* r1, Rectangle* r2)
	{
		float halfPI = PI / 2.0f;

		glm::vec2 cornersA[4];
		cornersA[0].x = r1->center.x - r1->w;
		cornersA[0].y = r1->center.y - r1->h;
		cornersA[1].x = r1->center.x + r1->w;
		cornersA[1].y = r1->center.y - r1->h;
		cornersA[2].x = r1->center.x - r1->w;
		cornersA[2].y = r1->center.y + r1->h;
		cornersA[3].x = r1->center.x + r1->w;
		cornersA[3].y = r1->center.y + r1->h;

		glm::vec2 cornersB[4];
		cornersB[0].x = r2->center.x - r2->w;
		cornersB[0].y = r2->center.y - r2->h;
		cornersB[1].x = r2->center.x + r2->w;
		cornersB[1].y = r2->center.y - r2->h;
		cornersB[2].x = r2->center.x - r2->w;
		cornersB[2].y = r2->center.y + r2->h;
		cornersB[3].x = r2->center.x + r2->w;
		cornersB[3].y = r2->center.y + r2->h;

		glm::vec2 axis[4];

		axis[0].x = cos(r1->rotation);
		axis[0].y = sin(r1->rotation);
		axis[1].x = cos(r1->rotation + halfPI);
		axis[1].y = sin(r1->rotation + halfPI);
		axis[2].x = cos(r2->rotation);
		axis[2].y = sin(r2->rotation);	   
		axis[3].x = cos(r2->rotation + halfPI);
		axis[3].y = sin(r2->rotation + halfPI);

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
				return false;
			}
		}
		return true;
	}
}