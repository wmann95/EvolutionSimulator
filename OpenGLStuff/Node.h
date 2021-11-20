#pragma once
#include <vector>

class Node
{
private:
	std::vector<Node*> connectedNodes;
	std::vector<double> weights;
	double sum;
public:
	Node();
	void ConnectNode(Node *n, double weight);
	void passThru();
	void addValue(double val);
	double getValue();
	void Clear();
};

