#pragma once
#include "Cell.h"

#include <iostream>
#include <random>
#include <string>
#include <vector>

class World
{
private:
	unsigned int getSum(std::string seed);
	std::vector<Cell> cells;
public:
	World(std::string seed);
	void Update();
	void Render();
	double nextRand();
	
};

