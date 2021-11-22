#define _USE_MATH_DEFINES
#include "Cell.h"
#include <math.h>
#include <glm/gtc/matrix_transform.hpp>

// Dummy Constructor
Cell::Cell() {}

void Cell::Initialize(World* world) {
	
	shader = new Shader("shader.vert", "shader.frag");

	this->world = world;

	energy = 100.0;
	rotation = world->nextRand() * M_PI * 2;
	velocity = 0.003f;
	xPos = 0.0;
	yPos = 0.0;
	scale = 1.0f;
	lifeTime = 0.0;
	
	color = glm::vec3(world->nextRand(), world->nextRand(), world->nextRand());

	network = new NeuralNet(world);

}

Cell::~Cell() {
	delete shader;
	delete network;
}

int timer = 2000;

void Cell::Update(int deltaTime) {


	if (energy <= 0) {
		return;
	}

	lifeTime += deltaTime;

	double ins[] = { rotation, velocity, (double)((double)deltaTime / 10)};
	std::vector<double> vec = network->send(ins, 3);

	double dRotation = vec[0] - vec[1];
	rotation += dRotation / 100;

	if (rotation > 3.14159 * 2) { rotation -= M_PI * 2; }
	if (rotation < 0) { rotation += M_PI * 2; }

	double dX = sin(rotation) * velocity;
	double dY = cos(rotation) * velocity;

	energy -= std::sqrt(dX * dX + dY * dY) * 10 + std::abs(dRotation) / 10;

	xPos += dX;
	yPos += dY;

	//std::cout << "X: " << xPos << ", Y: " << yPos << std::endl;
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
	
	glUniform3fv(glGetUniformLocation(shader->ID, "color"), 1, glm::value_ptr(color));

	glBindVertexArray(triangle.GetVAO());
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

}

double Cell::getLifeTime() {
	return lifeTime;
}

bool Cell::isAlive() {
	return energy > 0;
}