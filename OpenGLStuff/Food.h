#pragma once
#include "Shader.h"
#include "Circle.h"
#include "Triangle.h"
#include "World.h"

class Food
{
private:
	double energy = 10.0;
	double xPos = 0.0;
	double yPos = 0.0;
	Shader* shader;
	glm::vec3 color;
	World* world;
	Circle circle;
	Triangle triangle;
public:
	Food();
	~Food();
	void Render();
	void Initialize(World* world);

};

