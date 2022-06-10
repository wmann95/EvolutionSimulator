#include "Node.h"
#include <iostream>

Node::Node(int id){
	this->id = id;
}

void Node::ConnectNode(Node *n, double weight) {
	
	connectedNodes.push_back(n);
	weights.push_back(weight);
}

void Node::passThru() {
	for (int i = 0; i < connectedNodes.size(); i++) {
		connectedNodes[i]->addValue(sum * weights[i]);
	}

	/*for (int i = 0; i < connectedNodes.size(); i++) {
		connectedNodes[i]->passThru();
	}*/

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

void Node::Sigmoid() {
	sum = 1 / (1 + exp(-sum));
}

double Node::getWeight(int conn) const {
	return weights[conn];
}

bool Node::isConnectedTo(Node* n) {
	
	for (int i = 0; i < connectedNodes.size(); i++) {
		if (n == connectedNodes[i]) {
			return true;
		}
	}

	return false;
}

int Node::getConnection(Node* n) {

	for (int i = 0; i < connectedNodes.size(); i++) {
		if (n == connectedNodes[i]) {
			return i;
		}
	}

	return false;
}

