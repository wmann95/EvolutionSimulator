#include "Cell.h"
#include <math.h>

Cell::Cell() {
	shader = new Shader("33shader.vert", "33shader.frag");

	energy = 100.0;
	rotation = 0.0;
	velocity = 0.0;
	xPos = 0.0;
	yPos = 0.0;
}

Cell::~Cell() {
	//shader->Delete();
	delete shader;
}

void Cell::Update() {
	xPos += cos(rotation);
	yPos += sin(rotation);
}

void Cell::Render() {
	
	shader->use();

	glm::mat4 transform = glm::mat4(1.0f);
	glm::mat4 scale = glm::mat4(1.0f);

	shader->setMat4("transform", transform);
	shader->setMat4("scale", scale);

	glBindVertexArray(triangle.GetVAO());
	glDrawArrays(GL_TRIANGLES, 0, 3);
}