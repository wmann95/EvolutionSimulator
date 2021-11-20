#define _USE_MATH_DEFINES
#include "Cell.h"
#include <math.h>
#include <glm/gtc/matrix_transform.hpp>

Cell::Cell() {
	shader = new Shader("33shader.vert", "33shader.frag");

	energy = 100.0;
	rotation = 0.0;
	velocity = 0.002f;
	xPos = 0.0;
	yPos = 0.0;
	scale = 1.0f;
}

Cell::~Cell() {
	//shader->Delete();
	delete shader;
}

int timer = 2000;

void Cell::Update(int deltaTime) {

	timer -= deltaTime;

	if (timer < 0) {
		rotation = world->nextRand() * M_PI * 2;
		timer += 2000;
	}



	if (rotation > 3.14159 * 2) { rotation -= M_PI * 2; }
	if (rotation < 0) { rotation += M_PI * 2; }

	xPos += sin(rotation) * velocity;
	yPos += cos(rotation) * velocity;

	std::cout << "X: " << xPos << ", Y: " << yPos << std::endl;
}

void Cell::Render() {
	shader->use();

	glm::mat4 transform = glm::mat4(1.0f);
	glm::mat4 rotate = glm::mat4(1.0f);
	glm::mat4 scale = glm::mat4(1.0f);

	transform = glm::translate(transform, glm::vec3(xPos,yPos,0));
	rotate = glm::rotate(rotate, (float)(rotation), glm::vec3(0, 0, -1.0f));
	scale = glm::scale(scale, glm::vec3(0.5f,0.5f,0));


	shader->setMat4("transform", transform);
	shader->setMat4("rotate", rotate);
	shader->setMat4("scale", scale);

	glBindVertexArray(triangle.GetVAO());
	glDrawArrays(GL_TRIANGLES, 0, 3);

}

void Cell::setWorld(World* simWorld)
{
	world = simWorld;
}
