#include "Screen.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

GLuint shaderID;
Shader* shader;

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
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

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
	
	// This was originally just "Shader shader("33shader.vert", "33shader.frag"), but I realized that the shader object was getting removed when the Screen constructor popped of the stack, thereby making a
	// pointer I had linked to it essentially be pointing to an empty shader.
	shader = new Shader("33shader.vert", "33shader.frag");

	//Shader shader("33shader.vert", "33shader.frag");
	//shade = &shader;
	shaderID = (*shader).ID;

	std::cout << (*shader).ID << std::endl;

	float vertices[] = {
		// positions
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vertices, GL_STATIC_DRAW);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);


	this->window = window;
	VAO = vao;
	VBO = vbo;



}

Screen::~Screen() {
	delete shader;
}

void Screen::Render(World* world) {

	processInput();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glm::mat4 transform = glm::mat4(1.0f);
	//glm::mat4 viewMatrix = glm::lookAt(glm::vec3(1.0), glm::vec3(0.0), glm::vec3(0.0, 1.0, 0.0));
	transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

	int vertColorLoc = glGetUniformLocation((*shader).ID, "color");

	(*shader).use();

	unsigned int transformLoc = glGetUniformLocation((*shader).ID, "transform");
	//unsigned int viewMatLoc = glGetUniformLocation((*shader).ID, "viewMatrix");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	//glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniform3f(vertColorLoc, 0.0f, 1.0f, 0.0f);


	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

	//(*world).Render();

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

	(*shader).Delete();
	glDeleteProgram(shaderID);

	glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width, height);
}

void Screen::processInput() {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

}

GLFWwindow* Screen::operator ()()
{
	return window;
}
