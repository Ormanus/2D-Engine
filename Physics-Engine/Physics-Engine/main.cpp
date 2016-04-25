#include "Renderer.h"
#include <Windows.h>
#include <time.h>
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

float rFloat(float x)
{
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX / x);
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

	const int n_rectangles = 10;

	phe::Rectangle r[n_rectangles];

	srand(time(NULL));

	for (int i = 0; i < n_rectangles; i++)
	{
		r[i].center = glm::vec2(rFloat(2.0f) - 1.0f, rFloat(2.0f) - 1.0f);
		r[i].w = rFloat(0.5f) + 0.1f;
		r[i].h = rFloat(0.5f) + 0.1f;
		r[i].rotation = rFloat(2.0f * PI);
		r[i].velocity = glm::vec2(rFloat(2.0f) - 1.0f, rFloat(2.0f) - 1.0f);
		r[i].angularVelocity = rFloat(8.0f) - 4.0f;
	}


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

		glm::vec2 prev[n_rectangles];
		bool color[n_rectangles];

		for (int i = 0; i < n_rectangles; i++)
		{
			phe::step(r[i], 0.005);
			prev[i] = r[i].center;

			if (r[i].center.x < -2.f) { r[i].center.x = 2.0f; }
			if (r[i].center.y < -2.f) { r[i].center.y = 2.0f; }
			if (r[i].center.x > 2.f) { r[i].center.x = -2.0f; }
			if (r[i].center.y > 2.f) { r[i].center.y = -2.0f; }

			color[i] = false;
		}

		for (int i = 0; i < n_rectangles; i++)
		{
			for (int j = 0; j < n_rectangles; j++)
			{
				if (i != j)
				{
					glm::vec4 collision = isColliding(&r[i], &r[j]);

					if (collision != glm::vec4(0.0))
					{
						phe::collide(&r[i], &r[j], collision);
						//r[i].center = prev[i];
						//r[j].center = prev[j];
						color[i] = true;
						color[j] = true;
					}
				}
			}
		}

		for (int i = 0; i < n_rectangles; i++)
		{
			if (color[i])
			{
				phe::setColor(0xFF0000FF);
			}
			else
			{
				phe::setColor(0x0000FFFF);
			}
			phe::drawRectangle(&r[i]);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}