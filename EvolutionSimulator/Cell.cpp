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

	network = new NeuralNet(world, 4, 15, 4);

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

	//std::cout << "test" << std::endl;

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
		//std::cout << "Death by energy out. Energy: " << energy << std::endl;
		deadFlag = true;
		return;
	}

	if (targetFood == nullptr) {
		targetFood = world->getFoodByID(0);

		//std::cout << "Cell ID: " << ID << ", Food target position (" << targetFood->getX() << ", " << targetFood->getY() << ")" << std::endl;
	}

	//Food* closest = world->getNearestFood(xPos, yPos, foodEaten);

	lifeTime += deltaTime;

	double ins[] = { xPos, yPos, targetFood == nullptr ? 1000.0 : targetFood->getX(), targetFood == nullptr ? 1000.0 : targetFood->getY() };


	std::vector<double> vec = network->send(ins, 4);

	//double accel = vec[3];

	double maxAccel = 1.0;
	double minAccel = -1.0;

	double dRotation = vec[0] - vec[1];
	rotation += dRotation * deltaTime;

	double accel = vec[2] - vec[3];
	velocity += accel * pow(deltaTime / 1000.0, 2);

	//velocity = 0.005;

	if (velocity < 0 || abs(accel) >= 1 || abs(dRotation) > 0.04) {
		energy = 0;

		//std::cout << "Death by speed or rotation" << std::endl;
		return;
	}

	if (velocity <= 0 && !stoppedFlag) {
		stoppedFlag = true;
		//std::cout << "stopped" << std::endl;
	}
	else if (velocity <= 0 && stoppedFlag && ((double)stoppedTimer) / 1000.0 > 0.1) {
		energy = 0;
		//std::cout << "Death by stopping" << std::endl;
		return;
	}
	else if (velocity == 0 && stoppedFlag) {
		stoppedTimer += deltaTime;
		//std::cout << ((double)stoppedTimer) / 1000.0 << std::endl;
	}
	else if (velocity != 0 && stoppedFlag) {
		stoppedFlag = false;
	}

	if (rotation > 3.14159 * 2) { rotation -= M_PI * 2; }
	if (rotation < 0) { rotation += M_PI * 2; }


	double dX = sin(rotation) * velocity;
	double dY = cos(rotation) * velocity;

	if (velocity > 0 && dY > 0) distanceTraveled += dY;

	//double dSenergyCost = abs(std::sqrt(dX * dX + dY * dY)) * 1.0;
	double dVenergyCost = abs( accel * (deltaTime / 1000.0) * (deltaTime / 1000.0)) * 1.0;
	double dRenergyCost = abs(dRotation * (deltaTime / 1000.0)) * 0.01;

	double energycost = dVenergyCost * 10 + dRenergyCost + (deltaTime / 1000.0) * 5;

	//std::cout << energycost << std::endl;

	energy -= energycost;

	//std::cout << energy << std::endl;
	
	xPos += dX;
	yPos += dY;

	//std::cout << closest->getDist(xPos, yPos) << std::endl;
	double dist = targetFood->getDist(xPos, yPos);
	if (dist < 0.02) {
		//std::cout << "foodEatenTest: "  << targetFood->getID() << std::endl;
		//foodEaten.push_back(closest->getID());

		//std::cout << "Cell energy: " << energy << std::endl;
		energy += targetFood->getEnergy();
		//std::cout << "Food target position (" << targetFood->getX() << ", " << targetFood->getY() << ") : " << targetFood->getEnergy() << std::endl;
		//std::cout << "Cell energy: " << energy << std::endl;
		//std::cout << std::endl;
		totalFood += 1;
		//std::cout << totalFood << std::endl;

		targetFood = world->getFoodByID(targetFood->getID() + 1);
		//std::cout << "Cell ID: " << ID << ", Food target position (" << targetFood->getX() << ", " << targetFood->getY() << ")" << std::endl;
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
	scale = glm::scale(scale, glm::vec3(1,1,0));

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
	return !deadFlag;
}

Cell* Cell::mutate(double m) {
	return new Cell(*this, m);
}