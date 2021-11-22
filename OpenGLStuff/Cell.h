#pragma once
#include "Shader.h"
#include "Triangle.h"
#include "World.h"
#include "NeuralNet.h"

class Cell
{
private:
	double energy;
	double rotation;
	double velocity;
	double xPos;
	double yPos;
	double scale;
	double lifeTime;
	glm::vec3 color = glm::vec3(0,0,0);
	Triangle triangle;
	Shader* shader;
	World* world = nullptr;
	NeuralNet* network;

public:
	Cell();
	~Cell();
	void Update(int deltaTime);
	void Render();
	void Initialize(World* world);
	double getLifeTime();
	bool isAlive();
};

