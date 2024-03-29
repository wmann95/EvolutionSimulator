#pragma once
#include <vector>

class Node
{
private:
	std::vector<Node*> toNodes;
	std::vector<Node*> fromNodes;
	std::vector<double> weights;
	//std::pair<int, int> connIDs;
	double sum = 0;
	int id = 0;
public:
	Node(int id);
	void ConnectNode(Node *n, double weight);
	bool isConnectedTo(Node* n);
	int getConnectionTo(Node* n);
	void passThru();
	void addValue(double val);
	double getValue() const;
	void Sigmoid();
	double getWeight(int node) const;
	void Clear();

	friend class NeuralNet;
};

