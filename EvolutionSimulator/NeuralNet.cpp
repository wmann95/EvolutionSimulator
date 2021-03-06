#include "NeuralNet.h"
#include "Node.h"
#include <vector>



NeuralNet::NeuralNet(World* w, int inNodeCount, int hiddenNodeCount, int outNodeCount) {

	world = w;

	for (int i = 0; i < inNodeCount; i++) {
		Node n(nodeList.size());
		inputs.push_back(&(n));
		nodeList.push_back(n);
	}

	for (int i = 0; i < hiddenNodeCount; i++) {

		Node n(nodeList.size());

		nodeList.push_back(n);

	}

	for (int i = 0; i < inNodeCount; i++) {

		Node n(nodeList.size());
		outputs.push_back(&(n));
		nodeList.push_back(n);

	}


}

NeuralNet::NeuralNet(const NeuralNet& old, double m) {

	world = old.world;


	// duplicate the structure of the old neural network.


	for (int i = 0; i < old.nodeList.size(); i++) {
		if (i < old.inputs.size()) { // input nodes
			Node n(nodeList.size());
			inputs.push_back(&(n));
			nodeList.push_back(n);
		}
		else if (i >= old.inputs.size() && i < old.nodeList.size() - old.outputs.size()) { // hidden nodes
			

			Node n(nodeList.size());
			nodeList.push_back(n);
		}
		else { // output nodes.
			Node n(nodeList.size());
			outputs.push_back(&(n));
			nodeList.push_back(n);
		}
	}

	// Remake connections

	for (int i = 0; i < old.nodeList.size(); i++) {
		// i will represent the id in the new nodeList.

		for (int j = 0; j < old.nodeList[i].connectedNodes.size(); j++) {
			int id = old.nodeList[i].connectedNodes[j]->id;

			ConnectNode(i, id);
		}

	}

	// Mutate

	double chance = world->nextRand();

	if (chance > 0.96) { // new node mutated.
		std::cout << "New node!" << std::endl;
		Node n(nodeList.size());
		nodeList.push_back(n);
	}

	for (int i = 0; i < muts; i++) {
		int id1 = nodeList.size() * world->nextRand();
		int id2 = nodeList.size() * world->nextRand();

		if (id1 == id2) continue;

		MutateConnection(id1, id2);

	}

}

bool NeuralNet::recurseLoopFinder(Node* ntf, Node* node) {
	if (node->connectedNodes.size() == 0) {
		return false;
	}
	if (node == ntf) {
		return true;
	}
	
	for (int i = 0; node->connectedNodes.size(); i++) {
		recurseLoopFinder(ntf, node->connectedNodes[i]);
	}

	return false;
}

void NeuralNet::ConnectNode(int node1, int node2) {
	if (node2 < inputs.size()) {
		return; // these are the inputs, we don't want to connect back to the inputs.
	}

	nodeList[node1].ConnectNode(&(nodeList[node2]), (1 / (1 + exp((*world).nextRand()))) / 1000.0);
}

void NeuralNet::MutateConnection(int node1, int node2) {
	double chance = world->nextRand();

	if (nodeList[node1].isConnectedTo(&(nodeList[node2]))) {
		int connID = nodeList[node1].getConnection(&(nodeList[node2]));

		//std::cout << "Connection found!" << std::endl;

		if (chance < 0.25) return; // No mutation
		else if (chance >= 0.975) { // remove the connection.
			std::cout << "Connection erased!" << std::endl;
			nodeList[node1].connectedNodes.erase(nodeList[node1].connectedNodes.begin() + connID);
		}

		nodeList[node1].weights[connID] = nodeList[node1].weights[connID] + (world->nextRand() * 2 - 1) * world->worldMutator;

	}
	else {
		if (chance > 0.80) { // create new connection
			//std::cout << "New connection made!" << std::endl;
			ConnectNode(node1, node2);
		}
	}
}

void NeuralNet::Sigmoid() {


	//for (int i = 0; i < outputs.size(); i++) {
		//outputs[i].Sigmoid();
	//}

	for (int i = nodeList.size() - inputs.size() - outputs.size(); i >= 0; i--) {

		//nodeList[i + inputs.size()].Sigmoid();

	}

	//for (int i = 0; i < inputs.size(); i++) {
		//inputs[i].Sigmoid();
	//}
}

std::vector<double> NeuralNet::send(std::vector<double> inVals)
{
	std::vector<double> outs;

	if (inVals.size() != inputs.size()) {
		return outs;
	}

	for (int i = 0; i < inputs.size(); i++) {
		nodeList[i].addValue(inVals[i]);
		nodeList[i].passThru();
	}

	for (int i = nodeList.size() - inputs.size() - outputs.size(); i >= 0; i--) {

		nodeList[i + inputs.size()].passThru();

	}
	
	for (int i = 0; i < outputs.size(); i++) {

		outs.push_back(nodeList[nodeList.size() - outputs.size() + i].getValue());

	}

	return outs;
}

std::vector<double> NeuralNet::send(double* inVals, int size) {
	std::vector<double> inArr;
	for (int i = 0; i < size; i++) {
		inArr.push_back(inVals[i]);
	}

	return send(inArr);
}

NeuralNet* NeuralNet::mutate(double m) {
	NeuralNet* buffer = new NeuralNet(*this, m);

	return buffer;
}