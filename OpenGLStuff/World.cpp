#include "World.h"
#include "NeuralNet.h"
#include "Cell.h"

std::string seed;
Cell* cells;
int cellCount = 5;
Cell* cell1;
Cell* cell2;

World::World(std::string s) {

	seed = s;

	if (seed != "") {
		std::cout << "World Seed: " << seed << std::endl;

		std::srand(getSum(seed));

		std::cout << "World Seed to int: " << getSum(seed) << std::endl;
	}
	else {
		std::srand(time(NULL));
	}


	//cells = new Cell[cellCount];

	cell1 = new Cell();
	cell2 = new Cell();
	

	for (int i = 0; i < cellCount; i++) {
		//cells[i].setWorld(this);

		//std::cout << &cells[i] << std::endl;
	}

}

World::~World() {
	//delete[] cells;
	delete cell1;
	delete cell2;
}

void World::Update(int deltaTime)
{
	for (int i = 0; i < cellCount; i++) {
		//cells[i].Update();
	}

	cell1->Update(deltaTime);
	cell2->Update(deltaTime);
}

void World::Render() {

	for (int i = 0; i < cellCount; i++) {
		//cells[i].Render();
	}

	cell2->Render();
	cell1->Render();
}

double World::nextRand() {
	return ((double)(rand() % 1000)) / 1000;
}

unsigned int World::getSum(std::string seed) {
	//std::cout << "World Seed: " << seed << std::endl;
	//std::cout << "World Seed Length: " << seed.length() << std::endl;
	unsigned int sum = 0;

	for (int i = 0; i < seed.length(); i++) {
		int a = seed[i];
		int b = a + seed[i] * i;
		sum += (a + b);
	}
	sum = sum % (1028 * 2 * 2 * 2);
	
	//std::cout << "World Seed to int: " << sum << std::endl;

	return sum;
}