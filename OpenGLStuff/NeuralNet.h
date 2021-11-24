#pragma once
#include "Node.h"
#include "World.h"
#include <vector>

class World;

class NeuralNet
{
private:
	std::vector<Node> inputs;
	std::vector<std::vector<Node>> hiddenLayers;
	std::vector<Node> outputs;
	World* world;

public:
	NeuralNet(World* w, int inNodeCount, int hLayerCount, int hLayerNodeCount, int outNodeCount);
	NeuralNet(const NeuralNet& old, double m);
	NeuralNet(World* world);
	void Initialize(int inNodeCount, int hLayerCount, int hLayerNodeCount, int outNodeCount);
	std::vector<double> send(std::vector<double> inputs);
	std::vector<double> send(double* inVals, int size);
	NeuralNet* mutate(double m);
};

