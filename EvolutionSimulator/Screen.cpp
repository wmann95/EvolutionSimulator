#include "Screen.h"

GLuint shaderID;

GLFWwindow* Screen::InitializeWindow(int width, int height) {

	if (!glfwInit()) {
		std::cout << "Could not start GLFW3" << std::endl;
		return NULL;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return NULL;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return NULL;
	}

	return window;
}



Screen::Screen(int width, int height) {
	GLFWwindow* window = InitializeWindow(width, height);

	if (window == NULL) {
		std::cout << "Could not create window." << std::endl;
		return;
	}
	
	this->window = window;
}

void Screen::Render(World* world) {

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		world->moveCam(0.0, world->getCamSpeed());
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		world->moveCam(0.0, -world->getCamSpeed());
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		world->moveCam(-world->getCamSpeed(), 0.0);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		world->moveCam(world->getCamSpeed(), 0.0);
	}

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	world->Render();

	glfwPollEvents();
	glfwSwapBuffers(window);

}

bool Screen::shouldClose() {
	return glfwWindowShouldClose(window);
}

void Screen::Kill()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
}

void Screen::processInput() {
	
}

GLFWwindow* Screen::operator ()()
{
	return window;
}
