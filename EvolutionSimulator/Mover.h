#pragma once
#include "CellPart.h"

class Brain;

class Mover : public CellPart {
private:
	double rotation = 0.0;
	double velocity = 0.01;

	void Do() {

		if (!cell->hasCellPart("Brain")) {
			return;
		}

		std::vector<CellPart*> parts = cell->getCellParts();

		Brain* brain = nullptr;

		for (CellPart* part : parts) {
			//std::cout << part->getName() << std::endl;
			if (part->getName() == "Brain") {
				brain = (Brain*)(part);
			}
		}

		if (brain == nullptr) {
			return;
		}


		rotation += 0.01;


		if (rotation > 3.14159 * 2) { rotation -= M_PI * 2; }
		if (rotation < 0) { rotation += M_PI * 2; }


		double dX = sin(rotation) * velocity;
		double dY = cos(rotation) * velocity;

		cell->Move(dX, dY);
	}

	std::string getName() {
		return "Mover";
	}
public:
	Mover(Cell* cell) : CellPart(cell) {

	}
	int maxAllowed() {
		return 20;
	}
};