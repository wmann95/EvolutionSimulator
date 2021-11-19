#pragma once
#include "Shader.h"
#include "Triangle.h"

class Cell
{
private:
	double energy;
	double rotation;
	double velocity;
	double xPos;
	double yPos;
	Triangle triangle;
	Shader* shader;

public:
	Cell();
	~Cell();
	void Update();
	void Render();
};

