#include "Food.h"
#include <glm/gtc/matrix_transform.hpp>

Food::Food(World* w, double x, double y, int id) {
	shader = new Shader("shader.vert", "shader.frag");

	world = w;

	xPos = x;
	yPos = y;
	ID = id;

	color = glm::vec3(0, 1, 0);
}

Food::~Food() {
	shader->Delete();
	delete shader;
}

void Food::Render() {
	shader->use();

	glm::mat4 transform = glm::mat4(1.0f);
	glm::mat4 rotate = glm::mat4(1.0f);
	glm::mat4 scale = glm::mat4(1.0f);

	transform = glm::translate(transform, glm::vec3(xPos, yPos, 0));
	scale = glm::scale(scale, glm::vec3(0.01f, 0.01f, 0));


	shader->setMat4("transform", transform);
	shader->setMat4("rotate", rotate);
	shader->setMat4("scale", scale);

	glUniform3fv(glGetUniformLocation(shader->ID, "color"), 1, glm::value_ptr(color));

	glBindVertexArray(circle.GetVAO());
	glDrawArrays(GL_TRIANGLES, 0, Circle::vert3count);
	glBindVertexArray(0);

}