#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Shape {
public:
	virtual unsigned int GetVAO() = 0;
	virtual unsigned int GetVBO() = 0;
	virtual unsigned int GetEBO() = 0;
private:
protected:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	Shape() {
		VAO = 0;
		VBO = 0;
		EBO = 0;
	};
	virtual void Init(unsigned int* VAO, unsigned int* VBO) = 0;
	virtual void Initialize() {
		Init(&VAO, &VBO);
	}
};