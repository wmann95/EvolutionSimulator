#pragma once
#include <iostream>
#include <random>
#include <string>
#include <vector>


class World
{
private:
	unsigned int getSum(std::string seed);
	void SortCells();
	bool checkAllDead();
public:
	World(std::string seed);
	~World();
	void Update(int deltaTime);
	void Render();
	double nextRand();
	
};

