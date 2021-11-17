#pragma once
#include "Node.h"
#include "World.h"
#include <vector>

class NeuralNet
{
private:
	std::vector<Node> inputs;
	std::vector<std::vector<double>> inToHConns;
	std::vector<std::vector<Node>> hiddenLayers;
	std::vector<std::vector<std::vector<double>>> hiddenConns;
	std::vector<std::vector<double>> hToOConns;
	std::vector<Node> outputs;

public:
	NeuralNet(World* world);
	void Initialize(int inNodeCount, int hLayerCount, int hLayerNodeCount, int outNodeCount);
	std::vector<double> send(std::vector<double> inputs);
	std::vector<double> send(double* inVals, int size);
};

