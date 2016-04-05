#include "Renderer.h"

GLFWwindow* window;

int main()
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	//glfwWindowHint(GLFW_SAMPLES, 4);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int w = 1024;
	int h = 768;
	window = glfwCreateWindow(w, h,
		"PhysicsEngine", NULL, NULL);
	if (window == NULL){
		fprintf(stderr, "Failed to open GLFW window.");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glfwSetFramebufferSizeCallback(window, phe::framebufferSizeCallback);
	//glfwSetKeyCallback(window, Renderer::key_callback);
	phe::framebufferSizeCallback(window, w, h);
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	//glfwMakeContextCurrent(window);

	//Game loop
	do
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);

		glLoadIdentity();
		float ratio = w / (float)h;
		glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();

		phe::drawTriangle(glm::vec2(0.0, 50.5), glm::vec2(-50.5, 0.0), glm::vec2(50.5, 0.0));
		glfwSwapBuffers(window);

		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	glfwDestroyWindow(window);
	glfwTerminate();
	system("pause");
	return 0;
}