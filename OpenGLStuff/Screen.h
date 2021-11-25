#pragma once
#include "World.h"
#include "Shader.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Screen
{
private:
	GLFWwindow* window;
	unsigned int shaderProgram;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	GLFWwindow* InitializeWindow(int width, int height);
public:
	Screen(int width, int height);
	void Render(World* world);
	bool shouldClose();
	void Kill();
	void processInput();
	GLFWwindow* operator ()();


};

