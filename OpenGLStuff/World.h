#pragma once
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "Cell.h"

class Cell;

class World
{
private:
	unsigned int getSum(std::string seed);
	void SortCells();
	bool checkAllDead();
	std::string seed;
	std::vector<Cell*> cellList;
	int cellCount = 50;
public:
	World(std::string seed);
	~World();
	void Update(int deltaTime);
	void Render();
	double nextRand();
	
};

