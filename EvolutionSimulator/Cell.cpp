#define _USE_MATH_DEFINES
#include "Cell.h"
#include "Mover.h"
#include "Brain.h"
#include "Chloroplast.h"
#include <math.h>
#include <glm/gtc/matrix_transform.hpp>

// Dummy Constructor
Cell::Cell(World* world, int id) {

	shader = new Shader("shader.vert", "shader.frag");

	this->world = world;

	//rotation = abs(world->nextRand() - world->nextRand()) * M_PI * 2;
	rotation = 0;

	color = glm::vec3(world->nextRand(), world->nextRand(), world->nextRand());


	//Mover* mover = new Mover(this);
	//Brain* brain = new Brain(this);
	Chloroplast* plast = new Chloroplast(this);

	//cellParts.push_back(mover);
	//cellParts.push_back(brain);
	cellParts.push_back(plast);

}

Cell::Cell(const Cell& oldCell, double m) {
	shader = new Shader("shader.vert", "shader.frag");

	this->world = oldCell.world;

	rotation = abs(world->nextRand() - world->nextRand()) * M_PI * 2;
	//rotation = 0;

	for (int i = 0; i < oldCell.cellParts.size(); i++) {
		std::string name = oldCell.cellParts[i]->getName();

		if (name == "Chloroplast") {
			cellParts.push_back(new Chloroplast(this));
		}
		if (name == "Brain") {
			cellParts.push_back(new Brain(this));
		}
		if (name == "Mover") {
			cellParts.push_back(new Mover(this));
		}
	}

	//mutate
	double mutChance = abs(world->nextRand() - world->nextRand());

	if (mutChance >= 0.95) {

	}
	
	double spawnRot = abs(world->nextRand() - world->nextRand()) * M_PI * 2;
	xPos = sin(spawnRot) * abs(world->nextRand() - world->nextRand()) * 0.5;
	yPos = cos(spawnRot) * abs(world->nextRand() - world->nextRand()) * 0.5;
	

	float colorMutation = 0.2;

	color = (oldCell.color) * (1.0f - colorMutation) + (glm::vec3(world->nextRand(), world->nextRand(), world->nextRand())) * colorMutation;

	//color = glm::vec3(world->nextRand(), world->nextRand(), world->nextRand());


}

Cell::~Cell() {
	shader->Delete();
	delete shader;
	for (int i = 0; i < cellParts.size(); i++) {
		delete cellParts[i];
	}
	cellParts.clear();
}

void Cell::Update(int deltaTime) {
	lifeTime -= deltaTime / 1000.0;

	for (int i = 0; i < cellParts.size(); i++) {
		energy -= cellParts[i]->getEnergyCost();
		cellParts[i]->Update();
	}
}

//void Cell::DepUpdate(int deltaTime) {
//
//
//	if (energy <= 0) {
//		return;
//	}
//
//	Food* closest = world->getNearestFood(xPos, yPos, foodEaten);
//
//	lifeTime += deltaTime;
//
//	double ins[] = { rotation, velocity, deltaTime / 1000.0, closest == nullptr ? 1000.0 : closest->getX(), closest == nullptr ? 1000.0 : closest->getY() };
//
//
//	std::vector<double> vec = network->send(ins, 5);
//
//	double dRotation = vec[0] - vec[1];
//	//double accel = vec[3];
//
//	double maxAccel = 1.0;
//	double minAccel = -1.0;
//
//
//	double accel = vec[3] - vec[4];
//
//
//	if (accel < minAccel) {
//		accel = minAccel;
//	}
//	else if (accel > maxAccel) {
//		accel = maxAccel;
//	}
//
//	rotation += dRotation * deltaTime / 1000.0;
//
//	//velocity += accel * pow(deltaTime / 1000.0, 2);
//
//	velocity = 0.005;
//
//	if (velocity <= 0) {
//		energy = 0;
//		return;
//	}
//
//	if (rotation > 3.14159 * 2) { rotation -= M_PI * 2; }
//	if (rotation < 0) { rotation += M_PI * 2; }
//
//
//	double dX = sin(rotation) * velocity;
//	double dY = cos(rotation) * velocity;
//
//	distanceTraveled += std::sqrt(dX * dX + dY * dY);
//
//	double dSenergyCost = abs(std::sqrt(dX * dX + dY * dY)) * 80;
//	double dVenergyCost = abs( accel * (deltaTime / 1000.0) * (deltaTime / 1000.0)) * 200.0;
//	double dRenergyCost = abs(dRotation * (deltaTime / 1000.0)) * 2.0;
//
//	energy -= dSenergyCost + dVenergyCost + dRenergyCost;
//
//	xPos += dX;
//	yPos += dY;
//
//	if (closest == nullptr) {
//		return;
//	}
//	//std::cout << closest->getDist(xPos, yPos) << std::endl;
//	double dist = closest->getDist(xPos, yPos);
//	if (dist < 0.05) {
//		//std::cout << "foodEatenTest" << std::endl;
//		foodEaten.push_back(closest->getID());
//		energy += closest->getEnergy();
//		totalFood++;
//
//		//std::cout << "Food ID of <" << closest->getID() << "> eaten by cell of ID <" << ID << ">" << std::endl;
//	}
//}

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

	if (!isAlive()) {
		color = glm::vec3(0.3, 0.50, 0.7);
	}
	
	glUniform3fv(glGetUniformLocation(shader->ID, "color"), 1, glm::value_ptr(color));

	glBindVertexArray(triangle.GetVAO());
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

}

double Cell::getLifeTime() {
	return lifeTime;
}

bool Cell::isAlive() {
	return energy > 0 && lifeTime > 0;
}

Cell* Cell::mutate(double m) {
	return new Cell(*this, m);
}

void Cell::Move(double xMove, double yMove) {
	xPos += xMove;
	yPos += yMove;
}

double Cell::getDistanceTravelled() {
	return sqrt(xPos * xPos + yPos * yPos);
}

int Cell::getTotalFood() {
	return totalFood;
}

bool Cell::hasCellPart(std::string partName) {
	for (CellPart* part : cellParts) {
		if (part->getName() == partName) {
			return true;
		}
	}
	return false;
}

std::vector<CellPart*> Cell::getCellParts() {
	return cellParts;
}

void Cell::feed(double amount) {
	energy += amount;
}

bool Cell::canReproduce() {
	return isAlive() && energy > reproductionCost * 1.3;
}