#include "World.h"
#include "NeuralNet.h"
#include "Cell.h"
#include "Food.h"

std::string seed;
Cell* cells;
std::vector<Cell*> cellList;
//Cell* cell1;
int cellCount = 20;

Food* food1;

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

	
	//cell1 = new Cell();
	//cell1->Initialize(this);
	//cell2 = new Cell();
	
	cells = nullptr;

	for (int i = 0; i < cellCount; i++) {
		Cell* cell = (Cell*)malloc(sizeof(Cell));

		cell = new Cell();
		cell->Initialize(this);

		cellList.push_back(cell);

		//cells[i].Initialize(this);
	}
	

	food1 = new Food();
	food1->Initialize(this);

}

World::~World() {

	for (int i = 0; i < cellCount; i++) {
		delete cellList[i];
	}

	//delete[] cells;
	//delete cell1;
	//delete cell2;

	delete food1;
}

bool sorted = false;

void World::Update(int deltaTime)
{
	if (this->checkAllDead()) {
		if (!sorted) {
			this->SortCells();

			std::cout << "Sorted! Winner lifetime is: " << cellList[0]->getLifeTime() << std::endl;
			sorted = true;
		}

		return;
	}

	for (int i = 0; i < cellCount; i++) {
		//cells[i].Update(deltaTime);
		cellList[i]->Update(deltaTime);
	}

	//cell1->Update(deltaTime);
	//cell2->Update(deltaTime);
}

void World::Render() {

	for (int i = 0; i < cellCount; i++) {
		//cells[i].Render();
		cellList[i]->Render();
	}

	//cell2->Render();
	//cell1->Render();
	food1->Render();
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

void World::SortCells() {

	std::vector<Cell*> sortedCells;

	for (int i = 0; i < cellList.size(); i++) {
		if (i == 0) {
			sortedCells.push_back(cellList[i]);
			continue;
		}
		for (int j = 0; j < sortedCells.size(); j++) {
			if (cellList[i]->getLifeTime() > sortedCells[j]->getLifeTime()) {
				sortedCells.insert(sortedCells.begin() + j, cellList[i]);
				break;
			}
			else if (j == sortedCells.size() - 1) {
				sortedCells.push_back(cellList[i]);
				break;
			}
		}
	}

	for (int i = 0; i < cellList.size(); i++) {
		cellList[i] = sortedCells[i];
	}
}

bool World::checkAllDead() {

	for (int i = 0; i < cellCount; i++) {
		if (cells == nullptr) {
			if (cellList[i]->isAlive()) {
				return false;
			}
			continue;
		}
		else if (cells[i].isAlive()) {
			return false;
		}
	}

	return true;
}