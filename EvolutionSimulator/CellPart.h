#pragma once
#include "Cell.h"

class Cell;

class CellPart {
protected:
	Cell* cell;
	double energyCost = 0.5;
	virtual void Do() = 0;
public:
	CellPart(Cell* parent) {
		cell = parent;
	}
	void Update() {
		Do();
	}
	virtual std::string getName() = 0;
	virtual int maxAllowed() = 0;
	double getEnergyCost() {
		return energyCost;
	}
};