#include "Node.h"

Node::Node(){}

void Node::ConnectNode(Node *n, double weight) {
	connectedNodes.push_back(n);
	weights.push_back(weight);
}

void Node::passThru() {
	for (int i = 0; i < connectedNodes.size(); i++) {
		connectedNodes[i]->addValue(sum * weights[i]);
	}
	for (int i = 0; i < connectedNodes.size(); i++) {
		connectedNodes[i]->passThru();
	}

}

void Node::addValue(double val) {
	sum += val;
}

double Node::getValue() const
{
	return sum;
}

void Node::Clear() {
	sum = 0;
}

double Node::getWeight(int node) const {
	return weights[node];
}