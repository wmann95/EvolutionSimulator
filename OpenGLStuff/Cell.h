#pragma once
#include "Shader.h"
#include "Triangle.h"
#include "World.h"

class Cell
{
private:
	double energy;
	double rotation;
	double velocity;
	double xPos;
	double yPos;
	double scale;
	Triangle triangle;
	Shader* shader;
	World* world = nullptr;

public:
	Cell();
	~Cell();
	void Update(int deltaTime);
	void Render();
	void setWorld(World* simWorld);
};

