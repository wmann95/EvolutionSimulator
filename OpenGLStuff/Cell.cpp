#include "Cell.h"
#include <math.h>

Cell::Cell() {
	energy = 100.0;
	rotation = 0.0;
	velocity = 0.0;
	xPos = 0.0;
	yPos = 0.0;
}

void Cell::Update() {
	xPos += cos(rotation);
	yPos += sin(rotation);
}

void Cell::Render() {

}