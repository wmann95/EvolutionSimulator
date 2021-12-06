#pragma once
#include <GLFW/glfw3.h>

bool* keys;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

bool isKeyDown(int key) {
	return keys[key];
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		keys[key] = true;
	}
	if (action == GLFW_RELEASE) {
		keys[key] = false;
	}
}