#pragma once
#include "Node.h"
#include "World.h"
#include <vector>

class World;

class NeuralNet
{
private:
	std::vector<Node*> inputs; // Node pointers to specific nodes in the nodelist that are the inputs.
	std::vector<Node*> nodeList;
	std::vector<Node*> outputs; // Node pointers to specific nodes in the nodelist that are the outputs.
	World* world;
	int muts = 10;
	void ConnectNode(int node1, int node2);
	void ConnectNode(int node1, int node2, double weight);
	void MutateConnection(int node1, int node2);
	bool recurseLoopFinder(Node* ntf, Node* node);
public:
	NeuralNet(World* w, int inNodeCount, int hiddenNodeCount, int outNodeCount);
	NeuralNet(const NeuralNet& old, double m);
	~NeuralNet();
	void Sigmoid();
	std::vector<double> send(std::vector<double> inputs);
	std::vector<double> send(double* inVals, int size);
	NeuralNet* mutate();
};

