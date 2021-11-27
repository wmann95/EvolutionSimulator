#pragma once
#include "Shader.h"
#include "Triangle.h"
#include "World.h"
#include "NeuralNet.h"

class World;
class NeuralNet;

class Cell
{
private:
	double energy = 40.0;
	double rotation;
	double velocity = 0.003;
	double xPos = 0;
	double yPos = 0.0;
	double scale = 0.0;
	double lifeTime = 0.0;
	double distanceTraveled = 0;
	int totalFood = 0;
	glm::vec3 color = glm::vec3(0,0,0);
	Triangle triangle;
	Shader* shader;
	World* world = nullptr;
	NeuralNet* network;
	std::vector<int> foodEaten;
	int ID;
public:
	Cell(World* world, int id);
	Cell(const Cell&, double m);
	~Cell();
	void Update(int deltaTime);
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
		return distanceTraveled;
	}
};

