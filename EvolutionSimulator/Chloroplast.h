#pragma once
#include "CellPart.h"

class Chloroplast : public CellPart {
private:
	void Do() {

	}

public:
	Chloroplast(Cell* cell) : CellPart(cell) {
		energyCost = -0.5;
	}

	std::string getName() {
		return "Chloroplast";
	}

	int maxAllowed() {
		return 100;
	}

};