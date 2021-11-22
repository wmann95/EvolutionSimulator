#include "World.h"
#include "Screen.h"
#include "Shapes.h"

#include <iostream>
#include <string>
#include <chrono>

Screen* scrPtr;
bool isRunning = true;

void Close() {
	isRunning = false;
	(*scrPtr).Kill();
}

int main() {

	// Initialize the opengl window at 800 by 600 pixels.
	Screen screen(800, 800);

	// Define the pointer to the screen object so that it can later be killed
	scrPtr = &screen;

	// Initialize an instance of a new world with a seed value of "testWorld"
	World world("");

	long long int millis;
	long long int deltaTime;

	std::chrono::milliseconds m = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	millis = m.count();
	
	int fps = 120;
	int ups = 120;

	int updates = 0;
	int frames = 0;

	int rdt = 0;

	int fpsCounter = 0;
	int upsCounter = 0;
	int clock = 0;

	// General Game Loop
	while (isRunning) {

		// Update time taken to do the loop. Will be used for movement of cells in simulation later.
		deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - millis;
		millis = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

		rdt += deltaTime;
		clock += deltaTime;

		fpsCounter += deltaTime;
		upsCounter += deltaTime;

		// Render stuff
		if (fpsCounter >= 1000 / fps) {
			screen.Render(&world);
			
			fpsCounter = 0;
			frames++;
		}

		// Update World
		if (upsCounter >= 1000 / ups) {
			world.Update(rdt);

			rdt = 0;
			upsCounter = 0;
			updates++;
		}

		if (clock >= 1000) {
			std::cout << "FRAMES: " << frames << ", UPDATES: " << updates << std::endl;
			frames = updates = 0;
			clock = 0;
		}

		if (screen.shouldClose()) {
			Close();
		}

	}


	return 0;
}
