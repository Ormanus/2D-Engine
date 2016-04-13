#include "Renderer.h"
#include <Windows.h>
#define PI 3.14159265

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
int main(void)
{
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	window = glfwCreateWindow(1280, 640, "Simple example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	phe::Rectangle r1;
	r1.center = glm::vec2(-0.5f, 0.0f);
	r1.w = 0.5f;
	r1.h = 0.1f;
	r1.rotation = 0.0f;//-PI / 4.0f;
	r1.velocity = glm::vec2(5.5f, 0.0f);
	r1.angularVelocity = 0.9f;

	phe::Rectangle r2;
	r2.center = glm::vec2(0.5f, 0.0f);
	r2.w = 0.25f;
	r2.h = 0.25f;
	r2.rotation = 0.0f;
	r2.velocity = glm::vec2(0.0f, 0.0f);
	r2.angularVelocity = 0.0f;


	while (!glfwWindowShouldClose(window))
	{
		Sleep(1);

		float ratio;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		
		//phe::drawRectangle(glm::vec2(-0.5f, -0.1f), glm::vec2(-0.5f, 0.1f), glm::vec2(0.5f, 0.1f));

		phe::drawRectangle(&r1);
		phe::drawRectangle(&r2);

		phe::step(r1, 0.005);
		phe::step(r2, 0.005);

		glm::vec2 collision = phe::isColliding(&r1, &r2);
		if (collision != glm::vec2(0.0))
		{
			phe::setColor(0xFF0000FF);
			r1.center += collision;
		}
		else
		{
			phe::setColor(0x0000FFFF);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}