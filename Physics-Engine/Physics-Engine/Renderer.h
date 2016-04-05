#ifndef	RENDERER_H
#define RENDERER_H

#define GLEW_STATIC
#define GLM_FORCE_RADIANS
#define GLFW_INCLUDE_GLU

#include <iostream>
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include <glm\glm.hpp>

namespace phe
{
	void framebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
	}

	void drawTriangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3)
	{
		glBegin(GL_TRIANGLES);

		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(p1.x, p1.y, -2.0f);
		glVertex3f(p2.x, p2.y, -2.0f);
		glVertex3f(p3.x, p3.y, -2.0f);

		glEnd();
	}

	class Renderer
	{
	public:
		static Renderer& getInstance()
		{
			if (instance == nullptr)
			{
				instance = new Renderer();
			}
			return *instance;
		}
	private:
		Renderer();
		static Renderer* instance;
	};

	Renderer::Renderer()
	{
	}
}

#endif