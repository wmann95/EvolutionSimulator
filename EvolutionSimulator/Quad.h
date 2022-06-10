#pragma once
#include "Shape.h"

class Quad : virtual public Shape {
protected:
	virtual void Init(unsigned int* VAO, unsigned int* VBO) {

		float vertices[] = {
			// positions
			 0.25f,  0.25f, 0.0f,
			-0.25f,  0.25f, 0.0f,
			-0.25f, -0.25f, 0.0f,
			 0.25f,  0.25f, 0.0f,
			 0.25f, -0.25f, 0.0f,
			-0.25f, -0.25f, 0.0f
		};

		GLuint vbo = 0;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), vertices, GL_STATIC_DRAW);

		GLuint vao = 0;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		*VAO = vao;
		*VBO = vbo;

	}
public:
	Quad() {

		float vertices[] = {
			// positions
			 0.25f,  0.25f, 0.0f,
			-0.25f,  0.25f, 0.0f,
			-0.25f, -0.25f, 0.0f,
			 0.25f,  0.25f, 0.0f,
			 0.25f, -0.25f, 0.0f,
			-0.25f, -0.25f, 0.0f
		};

		GLuint vbo = 0;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), vertices, GL_STATIC_DRAW);

		GLuint vao = 0;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		this->VAO = vao;
		this->VAO = vbo;
	}
	unsigned int GetVAO() {
		return VAO;
	}

	unsigned int GetVBO() {
		return VBO;
	}

	unsigned int GetEBO() {
		return EBO;
	}

};
