#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <math.h>
#include "Cell.h"
#include "Food.h"

class Cell;
class Food;

class World
{
private:
	unsigned int getSum(std::string seed);
	void SortCells();
	bool checkAllDead();
	std::string seed;
	std::vector<Cell*> cellList;
	std::vector<Food*> foodList;
	int cellCount = 100;
	int foodChainCount = 1;
	int foodChainLength = 20;
	double maxFoodChainAngle = M_PI/2;
	double camX = 0;
	double camY = 0.6;
	double camSpeed = 0.025;
	double worldMutator = 0.005;
public:
	World(std::string seed);
	~World();
	void GenerateFood();
	void Generate(int chainlink, double x, double y, double angle, double dist);
	void Update(int deltaTime);
	void Render();
	double nextRand();
	
	Food* getNearestFood(double xPos, double yPos, std::vector<int> foods);
	
	glm::vec3 getCamPos() {
		return glm::vec3(camX, camY, 0);
	};

	double getCamSpeed() {
		return camSpeed;
	}

	void moveCam(double x, double y) {
		camX += x;
		camY += y;
	};
};

