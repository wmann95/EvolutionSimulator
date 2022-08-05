#pragma once
#include "Shader.h"
#include "Triangle.h"
#include "Quad.h"
#include "World.h"
#include "NeuralNet.h"

class World;
class Food;
class NeuralNet;

class Cell
{
private:
	double energy = 2.0;
	double rotation;
	double velocity = 0.000;
	double xPos = 0;
	double yPos = 0.0;
	double scale = 0.0;
	double lifeTime = 0.0;
	double distanceTraveled = 0;
	double foodGrabDistance = 0.035;
	int totalFood = 0;
	glm::vec3 color = glm::vec3(0,0,0);
	Triangle triangle;
	Shader* shader = nullptr;
	World* world = nullptr;
	Food* targetFood = nullptr;
	NeuralNet* network;
	std::vector<int> foodEaten;
	bool stoppedFlag;
	int stoppedTimer = 0;
	bool deadFlag = false;
	int ID;
public:
	Cell(World* world, int id);
	Cell(const Cell&, int id);
	~Cell();
	void Update(double deltaTime = (10.0 / 1000.0));
	void Render();
	double getLifeTime();
	bool isAlive();
	Cell* mutate(double m);
	int getID() {
		return ID;
	}

	int getTotalFood() {
		return totalFood;
	}

	double getDistanceTravelled() {
		return sqrt(xPos * xPos + yPos * yPos);
		//return yPos;
	}

};

