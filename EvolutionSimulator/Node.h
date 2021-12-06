#pragma once
#include <vector>

class Node
{
private:
	std::vector<Node*> connectedNodes;
	std::vector<double> weights;
	double sum = 0;
public:
	Node();
	void ConnectNode(Node *n, double weight);
	void passThru();
	void addValue(double val);
	double getValue() const;
	void Sigmoid();
	double getWeight(int node) const;
	void Clear();
};

