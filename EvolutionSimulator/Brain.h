#pragma once
#include "CellPart.h"
#include "NeuralNet.h"

class Brain : public CellPart {
private:
	NeuralNet* network;

	void Do() {

	}

public:
	Brain(Cell* cell) : CellPart(cell) {
		network = new NeuralNet(cell->world, 5, 2,3,5);
	}
	~Brain() {
		delete network;
	}

	std::string getName() {
		return "Brain";
	}

	int maxAllowed() {
		return 1;
	}

	void passThru() {

	}
};