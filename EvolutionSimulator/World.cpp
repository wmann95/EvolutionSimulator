#include "World.h"
#include "NeuralNet.h"

double getScore(Cell* cell);

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
	//std::cout << "Removing old food..." << std::endl;

	for (int i = 0; i < foodList.size(); i++) {
		delete foodList[i];
	}

	foodList.clear();
	std::vector<Food*>().swap(foodList);
	foodList.shrink_to_fit();

	//std::cout << "Generating food lines..." << std::endl;
	
	/*for (int i = 0; i < foodChainCount; i++) {
		Generate(foodChainLength, 0, 0, (nextRand() * 2 - 1) * M_PI * 2, 0.1);
	}*/

	for (int n = 0; n < foodChainCount; n++) {


		//double angle = (nextRand() * 2 - 1) * M_PI * 2;
		double angle = 0;
		double dist = 0.1;
		double x = 0;
		double y = 0.065;

		//std::cout << "[Angle: " << angle << ", dist: " << dist << ", X: " << x << ", Y " << y << "]" << std::endl;

		Food* food = new Food(this, x, y, foodEnergy, 0);

		foodList.push_back(food);

		for (int i = 1; i < foodChainLength; i++) {

			int id = n * foodChainLength + i;

			angle += (nextRand() * 2 - 1) * (M_PI / 3.5);
			x += sin(angle) * dist;
			y += cos(angle) * dist;
			dist *= 1.75;

			Food* food = new Food(this, x, y, foodEnergy * (i + 1) * 2.0, id);

			foodList.push_back(food);

			//Generate(chainlink - 1, x, y, angle, dist);

		}
	}
}


void World::Generate(int chainlink, double x = 0, double y = 0, double angle = 0, double dist = 0.1) {
	if (chainlink <= 0) {
		return;
	}

	angle += (nextRand() * 2 - 1) * (M_PI / 32) * 2;
	x += sin(angle) * dist;
	y += cos(angle) * dist;
	dist *= 1.5;

	Food* food = new Food(this, x, y, 0, foodList.size());

	foodList.push_back(food);

	Generate(chainlink - 1, x, y, angle, dist);

}

void World::Update(int deltaTime)
{
	if (this->checkAllDead() && cellList.size() > 0) {


		this->SortCells();

		std::cout << "Sorted! Highest score is: " << getScore(cellList[0]) << std::endl;

		std::vector<Cell*> winnerList = std::vector<Cell*>();
		//std::vector<Cell*>().swap(winnerList);
		//winnerList.clear();

		double indexLikelihood = 0.05;

		//for (int i = 0; i < cellList.size(); i++) {

		//	//Cell* winner = cellList[(cellList.size() - 1) * indexLikelihood * nextRand()];
		//	Cell* winner = cellList[0];

		//	//std::cout << "Winner chosen with score of: " << getScore(winner) << std::endl;

		//	winnerList.push_back(winner);
		//	if (indexLikelihood < 0) indexLikelihood = 0;
		//	else indexLikelihood -= indexLikelihood / ((double)cellList.size());
		//}


		for (int i = 0; i < (cellList.size() > 20? 20 : cellList.size()); i++) {
			//std::cout << getScore(cellList[i]) << std::endl;
			winnerList.push_back(cellList[i]);
		}

		std::vector<Cell*> newCells;

		for (int i = 0; i < cellList.size(); i++) {
			//std::cout << "Selected winner: " << getScore(winnerList[i % winnerList.size()]) << std::endl;
			newCells.push_back(new Cell(*winnerList[i % winnerList.size()], worldMutator));
			//newCells.push_back(new Cell(*cellList[0], worldMutator));
		}

		for (int i = 0; i < cellList.size(); i++) {
			delete cellList[i];
		}
		
		cellList.clear();
		//std::vector<Cell*>().swap(cellList);

		for (int i = 0; i < newCells.size(); i++) {
			cellList.push_back(newCells[i]);
		}

		//GenerateFood();
	}

	for (int i = 0; i < cellList.size(); i++) {
		if (!cellList[i]->isAlive()) continue;
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
	return ((double)(rand() % 100)) / 100.0;
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

double getScore(Cell* cell) {
	//std::cout << cell->getTotalFood() << std::endl;
	return cell->getTotalFood() * 3.0 + cell->getDistanceTravelled() / 100;
}

void World::SortCells() {

	std::vector<Cell*> sortedCells;

	for (int i = 0; i < cellList.size(); i++) {
		if (i == 0) {
			sortedCells.push_back(cellList[i]);
			continue;
		}


		for (int j = 0; j < sortedCells.size(); j++) {

			if (getScore(cellList[i]) > getScore(sortedCells[j])) {
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
		//std::cout << getScore(cellList[i]) << std::endl;
	}
}

bool World::checkAllDead() {


	for (int i = 0; i < cellList.size(); i++) {
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
