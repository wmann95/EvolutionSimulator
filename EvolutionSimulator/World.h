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
	int cellCount = 200;
	double camX = 0;
	double camY = 0.6;
	double camSpeed = 0.025;
	double foodEnergy = 5.0;
	double foodMultiplier = 1.5;
	int foodChainLength = 200;
	int foodChainCount = 1;
	double maxFoodChainAngle = M_PI/4;
	unsigned int generation = 0;

	std::string gen_random(const int length);
public:
	World(std::string seed);
	~World();
	void GenerateFood();
	void Update(int deltaTime);
	void Render();
	double nextRand();
	const double worldMutator = 2;
	
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

	Food* getFoodByID(int id) {
		if (foodList.size() == 0) return nullptr;
		if (id >= foodList.size()) return foodList[foodList.size() - 1];
		return foodList[id];
	}
};

