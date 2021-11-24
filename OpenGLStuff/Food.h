#pragma once
#include "Shader.h"
#include "Circle.h"
#include "Triangle.h"
#include "World.h"

class World;

class Food
{
private:
	double energy = 20.0;
	double xPos = 0.0;
	double yPos = 0.0;
	Shader* shader;
	glm::vec3 color;
	World* world;
	Circle circle;
	int ID;
public:
	Food(World* world, double xPos, double yPos, int id);
	~Food();
	void Render();
	double getX() {
		return xPos;
	}
	double getY() {
		return yPos;

	}
	double getDist(double x, double y) {
		return sqrt(pow(xPos - x, 2) + pow(yPos - y, 2));
	}
	int getID() {
		return ID;
	}
	double getEnergy() {
		return energy;
	}
};

