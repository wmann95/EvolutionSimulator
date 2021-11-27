#define _USE_MATH_DEFINES
#include "Cell.h"
#include <math.h>
#include <glm/gtc/matrix_transform.hpp>

// Dummy Constructor
Cell::Cell(World* world, int id) {

	shader = new Shader("shader.vert", "shader.frag");

	this->world = world;

	//rotation = abs(world->nextRand() - world->nextRand()) * M_PI * 2;
	rotation = 0;

	color = glm::vec3(world->nextRand(), world->nextRand(), world->nextRand());

	network = new NeuralNet(world, 5, 5, 10, 5);

	ID = id;
}

Cell::Cell(const Cell& oldCell, double m) {
	shader = new Shader("shader.vert", "shader.frag");

	this->world = oldCell.world;

	//rotation = abs(world->nextRand() - world->nextRand()) * M_PI * 2;
	rotation = 0;

	this->foodEaten.clear();
	this->foodEaten = std::vector<int>();

	float colorMutation = 0.1;

	color = (oldCell.color) * (1.0f - colorMutation) + (glm::vec3(world->nextRand(), world->nextRand(), world->nextRand())) * colorMutation;

	//color = glm::vec3(world->nextRand(), world->nextRand(), world->nextRand());

	delete network;
	network = oldCell.network->mutate(m);

}

Cell::~Cell() {
	shader->Delete();
	delete shader;
	delete network;
}


void Cell::Update(int deltaTime) {


	if (energy <= 0) {
		return;
	}

	Food* closest = world->getNearestFood(xPos, yPos, foodEaten);

	lifeTime += deltaTime;

	double ins[] = { rotation, velocity, deltaTime / 1000.0, closest == nullptr ? 1000.0 : closest->getX(), closest == nullptr ? 1000.0 : closest->getY() };


	std::vector<double> vec = network->send(ins, 5);

	double dRotation = vec[0] - vec[1];
	//double accel = vec[3];

	double maxAccel = 1.0;
	double minAccel = -1.0;


	double accel = vec[3] - vec[4];


	if (accel < minAccel) {
		accel = minAccel;
	}
	else if (accel > maxAccel) {
		accel = maxAccel;
	}

	rotation += dRotation * deltaTime / 1000.0;

	//velocity += accel * pow(deltaTime / 1000.0, 2);

	velocity = 0.005;

	if (velocity <= 0) {
		energy = 0;
		return;
	}

	if (rotation > 3.14159 * 2) { rotation -= M_PI * 2; }
	if (rotation < 0) { rotation += M_PI * 2; }


	double dX = sin(rotation) * velocity;
	double dY = cos(rotation) * velocity;

	distanceTraveled += std::sqrt(dX * dX + dY * dY);

	double dSenergyCost = abs(std::sqrt(dX * dX + dY * dY)) * 80;
	double dVenergyCost = abs( accel * (deltaTime / 1000.0) * (deltaTime / 1000.0)) * 200.0;
	double dRenergyCost = abs(dRotation * (deltaTime / 1000.0)) * 2.0;

	energy -= dSenergyCost + dVenergyCost + dRenergyCost;

	xPos += dX;
	yPos += dY;

	if (closest == nullptr) {
		return;
	}
	//std::cout << closest->getDist(xPos, yPos) << std::endl;
	double dist = closest->getDist(xPos, yPos);
	if (dist < 0.05) {
		//std::cout << "foodEatenTest" << std::endl;
		foodEaten.push_back(closest->getID());
		energy += closest->getEnergy();
		totalFood++;

		//std::cout << "Food ID of <" << closest->getID() << "> eaten by cell of ID <" << ID << ">" << std::endl;
	}
}

void Cell::Render() {
	shader->use();

	glm::mat4 transform = glm::mat4(1.0f);
	glm::mat4 rotate = glm::mat4(1.0f);
	glm::mat4 scale = glm::mat4(1.0f);

	transform = glm::translate(transform, glm::vec3(xPos,yPos,0));
	transform = glm::translate(transform, -world->getCamPos());
	rotate = glm::rotate(rotate, (float)(rotation), glm::vec3(0, 0, -1.0f));
	scale = glm::scale(scale, glm::vec3(0.1f,0.1f,0));


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

Cell* Cell::mutate(double m) {
	return new Cell(*this, m);
}