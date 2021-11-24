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
	int cellCount = 20;
	int foodChainCount = 10;
	int foodChainLength = 100;
	double maxFoodChainAngle = M_PI/2;
public:
	World(std::string seed);
	~World();
	void GenerateFood();
	void Update(int deltaTime);
	void Render();
	double nextRand();
	
	Food* getNearestFood(double xPos, double yPos, std::vector<int> foods);
	
};

