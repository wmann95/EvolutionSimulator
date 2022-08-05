#include "Node.h"
#include <iostream>

Node::Node(int id){
	this->id = id;
}


void Node::ConnectNode(Node *n, double weight) {
	
	toNodes.push_back(n);
	n->fromNodes.push_back(this);
	weights.push_back(weight);
}

void Node::passThru() {
	for (int i = 0; i < toNodes.size(); i++) {
		toNodes[i]->addValue(sum * weights[i]);
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
	
	for (int i = 0; i < toNodes.size(); i++) {
		if (n == toNodes[i]) {
			return true;
		}
	}

	return false;
}

int Node::getConnectionTo(Node* n) {

	for (int i = 0; i < toNodes.size(); i++) {
		if (n == toNodes[i]) {
			return i;
		}
	}

	return false;
}

