#include "Renderer.h"
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
	window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	phe::Rectangle r1;
	r1.center = glm::vec2(-0.0f, 0.0f);
	r1.w = 0.5f;
	r1.h = 0.1f;
	r1.rotation = PI / 4.0f;
	r1.velocity = glm::vec2(0.01f, 0.0f);

	phe::Rectangle r2;
	r2.center = glm::vec2(1.0f, 0.0f);
	r2.w = 0.5f;
	r2.h = 0.5f;
	r2.rotation = 0.0f;


	while (!glfwWindowShouldClose(window))
	{
		float ratio;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		//phe::drawRectangle(glm::vec2(-0.5f, -0.1f), glm::vec2(-0.5f, 0.1f), glm::vec2(0.5f, 0.1f));

		phe::drawRectangle(&r1);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}