#include "World.h"
#include "NeuralNet.h"

std::string seed;

World::World(std::string s) {

	seed = s;


	std::cout << "World Seed: " << seed << std::endl;

	std::srand(getSum(seed));

	std::cout << "World Seed to int: " << getSum(seed) << std::endl;

	std::cout << std::endl;
	for (int i = 0; i < 10; i++) {
		std::cout << nextRand() << " ";
	}
	std::cout << std::endl;


	NeuralNet nn(this);

	double ins[] = {1.0, 1.0, 1.0};

	std::vector<double> outs = nn.send(ins, 3);


	for (int i = 0; i < outs.size(); i++) {
		std::cout << outs[i] << std::endl;
	}

}

void World::Update()
{
}

void World::Render() {
	
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