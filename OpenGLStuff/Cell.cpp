#include "Cell.h"
#include <math.h>

Cell::Cell() {
	shader = new Shader("33shader.vert", "33shader.frag");

	energy = 100.0;
	rotation = 0.0;
	velocity = 0.0;
	xPos = 0.0;
	yPos = 0.0;
}

Cell::~Cell() {
	shader->Delete();
	delete shader;
}

void Cell::Update() {
	xPos += cos(rotation);
	yPos += sin(rotation);
}

void Cell::Render() {

}