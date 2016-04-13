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
	static int color = 0x0000FFFF;

	void setColor(const int newColor)
	{
		color = newColor;
	}

	void framebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
	}

	void drawRectangle(Rectangle* r)
	{
		//glRotatef(r->rotation, 1.0f, 1.0f, 0.0f);
		//glTranslatef(r->center.x, r->center.y, 0.0f);

		glBegin(GL_TRIANGLES);

		int R = (color & 0xFF000000) >> 24;
		int G = (color & 0x00FF0000) >> 16;
		int B = (color & 0x0000FF00) >> 8;

		glColor3ub(R, G, B);

		//(0,0)
		//  1----4
		//  |    |
		//  |    |
		//  2----3

		glm::vec2 p1 = r->center + rotate(glm::vec2(- r->w / 2.0f,- r->h / 2.0f), r->rotation);
		glm::vec2 p2 = r->center + rotate(glm::vec2(- r->w / 2.0f,+ r->h / 2.0f), r->rotation);
		glm::vec2 p3 = r->center + rotate(glm::vec2(+ r->w / 2.0f,+ r->h / 2.0f), r->rotation);
		glm::vec2 p4 = r->center + rotate(glm::vec2(+ r->w / 2.0f,- r->h / 2.0f), r->rotation);

		glVertex3f(p1.x, p1.y, 0.0f);//1
		glVertex3f(p2.x, p2.y, 0.0f);//2
		glVertex3f(p3.x, p3.y, 0.0f);//3

		glVertex3f(p3.x, p3.y, 0.0f);//3
		glVertex3f(p4.x, p4.y, 0.0f);//4
		glVertex3f(p1.x, p1.y, 0.0f);//1


		glEnd();
	}
}

#endif