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
	Cell* cells;
public:
	World(std::string seed);
	~World();
	void Update();
	void Render();
	double nextRand();
	
};

