#include "World.h"
#include "NeuralNet.h"


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

	
	for (int i = 0; i < cellCount; i++) {

		Cell* cell = new Cell(this, i);

		cellList.push_back(cell);
	}

	GenerateFood();

}

World::~World() {

	for (int i = 0; i < cellList.size(); i++) {
		delete cellList[i];
	}

	for (int i = 0; i < foodList.size(); i++) {
		delete foodList[i];
	}
}

void World::GenerateFood() {
	std::cout << "Removing old food..." << std::endl;

	if (foodList.size() > 0) {
		for (int i = 0; i < foodList.size(); i++) {
			delete foodList[i];
		}

		foodList.clear();
	}

	std::cout << "Generating food lines..." << std::endl;
	for (int n = 0; n < foodChainCount; n++) {


		double angle = (nextRand() * 2 - 1) * M_PI * 2;
		double dist = 0.2;
		double x = 0;
		double y = 0;

		//std::cout << "[Angle: " << angle << ", dist: " << dist << ", X: " << x << ", Y " << y << "]" << std::endl;


		for (int i = 0; i < foodChainLength; i++) {

			x += sin(angle) * dist;
			y += cos(angle) * dist;
			int id = i * n;
			//std::cout << "<ID: " << id << ", X: " << x << ", Y: " << y << ">" << std::endl;

			Food* food = new Food(this, x, y, id);

			foodList.push_back(food);

			angle += (nextRand() * 2 - 1) * (M_PI / 16);

		}
	}
}

void World::Update(int deltaTime)
{
	if (this->checkAllDead()) {

		this->SortCells();

		std::cout << "Sorted! Winner lifetime is: " << cellList[0]->getLifeTime() << std::endl;

		std::vector<Cell*> winnerList;

		for (int i = 0; i < cellList.size() / 5; i++) {
			winnerList.push_back(cellList[i]);
		}

		std::vector<Cell*> newCells;

		for (int i = 0; i < cellList.size(); i++) {
			newCells.push_back(new Cell(*winnerList[nextRand() * winnerList.size()], 0.001));
		}

		for (int i = 0; i < cellList.size(); i++) {
			delete cellList[i];
			cellList[i] = newCells[i];
		}

		GenerateFood();
	}

	for (int i = 0; i < cellCount; i++) {
		cellList[i]->Update(deltaTime);
	}

}

void World::Render() {

	for (int i = 0; i < cellList.size(); i++) {
		cellList[i]->Render();
	}

	for (int i = 0; i < foodList.size(); i++) {
		foodList[i]->Render();
	}

	//food1->Render();
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
		if (cellList[i]->isAlive()) {
			return false;
		}
	}

	return true;
}

Food* World::getNearestFood(double xPos, double yPos, std::vector<int> foods) {
	Food* closest = nullptr;
	double cDist = -1;
	for (int i = 0; i < foodList.size(); i++) {
		bool flag = false;
		for (int j = 0; j < foods.size(); j++) {
			// if the food that has already been eaten includes this id, then continue
			//std::cout << foods[j] << std::endl;
			//std::cout << foodList[i]->getID() << std::endl;
			if (foods[j] == foodList[i]->getID()) {
				flag = true;
				break;
			}
		}

		if (flag) continue;

		double dist = foodList[i]->getDist(xPos, yPos);

		if (closest == nullptr || dist < cDist || dist == -1) {
			closest = foodList[i];
			cDist = dist;
			continue;
		}
	}

	return closest;
}