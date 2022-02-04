#pragma once
#include "Shader.h"
#include "Triangle.h"
#include "World.h"
#include "NeuralNet.h"
#include "CellPart.h"

class World;
class CellPart;

class Cell
{
private:
	double energy = 1.0;
	double rotation;
	double velocity = 0.003;
	double xPos = 0;
	double yPos = 0.0;
	double scale = 0.0;
	double lifeTime = 10;
	double distanceTraveled = 0;
	int totalFood = 0;
	glm::vec3 color = glm::vec3(0,0,0);
	Triangle triangle;
	Shader* shader;
	std::vector<CellPart*> cellParts;
public:
	const double reproductionCost = 200;
	World* world = nullptr;
	Cell(World* world, int id);
	Cell(const Cell&, double m);
	~Cell();
	void Update(int deltatime);
	//void DepUpdate(int deltaTime);
	void Render();
	double getLifeTime();
	bool isAlive();
	Cell* mutate(double m);

	int getTotalFood();

	double getDistanceTravelled();
	void Move(double xMove, double yMove);

	bool hasCellPart(std::string partName);
	std::vector<CellPart*> getCellParts();
	void feed(double amount);
	bool canReproduce();
};

