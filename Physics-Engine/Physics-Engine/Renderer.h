#ifndef	RENDERER_H
#define RENDERER_H

#define GLEW_STATIC
#define GLM_FORCE_RADIANS
#define GLFW_INCLUDE_GLU

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include "Physics.h"

namespace phe
{
	void framebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
	}

	void drawRectangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3)
	{
		glBegin(GL_TRIANGLES);

		glColor3f(1.0f, 0.5f, 0.0f);

		glVertex3f(p1.x, p1.y, 0.f);
		glVertex3f(p2.x, p2.y, 0.f);
		glVertex3f(p3.x, p3.y, 0.f);

		glVertex3f(p3.x, p3.y, 0.f);
		glVertex3f(p3.x, p1.y, 0.f);
		glVertex3f(p1.x, p1.y, 0.f);


		glEnd();
	}

	void drawRectangle(Rectangle* r)
	{
		glRotatef(r->rotation, 1.0f, 1.0f, 0.0f);
		glTranslatef(r->center.x, r->center.y, 0.0f);

		glBegin(GL_TRIANGLES);

		glColor3f(1.0f, 0.5f, 0.0f);

		//(0,0)
		//  1----4
		//  |    |
		//  |    |
		//  2----3
		glVertex3f(r->center.x - r->w / 2.0f, r->center.y - r->h / 2.0f, 0.f);//1
		glVertex3f(r->center.x - r->w / 2.0f, r->center.y + r->h / 2.0f, 0.f);//2
		glVertex3f(r->center.x + r->w / 2.0f, r->center.y + r->h / 2.0f, 0.f);//3
		glVertex3f(r->center.x + r->w / 2.0f, r->center.y + r->h / 2.0f, 0.f);//3
		glVertex3f(r->center.x + r->w / 2.0f, r->center.y - r->h / 2.0f, 0.f);//4
		glVertex3f(r->center.x - r->w / 2.0f, r->center.y - r->h / 2.0f, 0.f);//1


		glEnd();
	}
}

#endif