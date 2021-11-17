#pragma once
class Cell
{
private:
	double energy;
	double rotation;
	double velocity;
	double xPos;
	double yPos;

public:
	Cell();
	void Update();
	void Render();
};

