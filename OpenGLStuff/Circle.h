#pragma once
#define _USE_MATH_DEFINES
#include "Shape.h"
#include "Shader.h"
#include <math.h>

class Circle : virtual public Shape {
protected:
	
	virtual void Init(unsigned int* VAO, unsigned int* VBO) {



		GLfloat vertices[vert3count];

		double theta = 0.0;

		for (int i = 0, j = 0; i < vert3count; i += 3) {
			if (i % 9 == 0) {
				vertices[i] = 0.0f;
				vertices[i + 1] = 0.0f;
				vertices[i + 2] = 0.0f;

				continue;
			}
			vertices[i] = sin(theta);
			vertices[i + 1] = cos(theta);
			vertices[i + 2] = 0;

			if (j % 2 == 0) {
				theta += (M_PI * 2) / (Circle::resolutionScalar * 4);
			}

			j++;


		}


		GLuint vbo = 0;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		GLuint vao = 0;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		*VAO = vao;
		*VBO = vbo;

		//std::cout << "CIRCLE TEST: " << vao << std::endl;

	}
public:
	static const int resolutionScalar = 4;
	static const int vert3count = (Circle::resolutionScalar * 4 * 3 + Circle::resolutionScalar) * 3;
	Circle() {
		Shape::Initialize();
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