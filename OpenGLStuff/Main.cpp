#include "World.h"
#include "Screen.h"
#include "Shapes.h"

#include <iostream>
#include <string>
#include <chrono>

// ------------- DECLARATIONS -------------
void Close();

// -------------  VARIABLES	  -------------
Screen* scrPtr;
bool isRunning = true;

long long int millis;
long long int deltaTime;


int main() {

	// Initialize the opengl window at 800 by 600 pixels.
	Screen screen(800, 800);

	// Define the pointer to the screen object so that it can later be killed
	scrPtr = &screen;

	// Initialize an instance of a new world with a seed value of "testWorld"
	World world("");

	std::chrono::milliseconds m = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	millis = m.count();
	
	// General Game Loop
	while (isRunning) {

		// Update time taken to do the loop. Will be used for movement of cells in simulation later.
		deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - millis;
		millis = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

		// Render stuff
		screen.Render(&world);

		// Update World
		world.Update(deltaTime);

		if (screen.shouldClose()) {
			Close();
		}
	}


	return 0;
}

// ------------- DEFINITIONS	-------------

void Close() {
	isRunning = false;
	(*scrPtr).Kill();
}
