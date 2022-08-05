#include "NeuralNet.h"
#include "Node.h"
#include <vector>



NeuralNet::NeuralNet(World* w, int inNodeCount, int hiddenNodeCount, int outNodeCount) {

	world = w;

	for (int i = 0; i < inNodeCount; i++) {
		Node* n = new Node(nodeList.size());
		inputs.push_back(n);
		nodeList.push_back(n);
	}

	for (int i = 0; i < hiddenNodeCount; i++) {

		Node* n = new Node(nodeList.size());

		nodeList.push_back(n);

	}

	for (int i = 0; i < outNodeCount; i++) {

		Node* n = new Node(nodeList.size());
		outputs.push_back(n);
		nodeList.push_back(n);

	}


}

NeuralNet::~NeuralNet() {

	for (int i = 0; i < nodeList.size(); i++) {
		delete nodeList[i];
	}

	inputs.clear();
	outputs.clear();
	nodeList.clear();
}

NeuralNet::NeuralNet(const NeuralNet& old, double m) {

	world = old.world;


	// duplicate the structure of the old neural network.


	for (int i = 0; i < old.inputs.size(); i++) {
		//if (i < old.inputs.size()) { // input nodes

		Node* n = new Node(nodeList.size());
		inputs.push_back(n);
		nodeList.push_back(n);
		
		//}
		//else if (i >= old.inputs.size() && i < old.nodeList.size() - old.outputs.size()) { // hidden nodes
		//	Node n(nodeList.size());
		//	nodeList.push_back(n);
		//}
		//else { // output nodes.
		//	Node n(nodeList.size());
		//	outputs.push_back(&(n));
		//	nodeList.push_back(n);
		//}
	}

	for (int i = 0; i < old.nodeList.size() - old.inputs.size() - old.outputs.size(); i++) {
		Node* n = new Node(nodeList.size());

		nodeList.push_back(n);
	}

	for (int i = 0; i < old.outputs.size(); i++) {
		Node* n = new Node(nodeList.size());
		outputs.push_back(n);
		nodeList.push_back(n);
	}

	// Remake connections

	for (int i = 0; i < old.nodeList.size(); i++) {
		// i will represent the id in the new nodeList.

		for (int j = 0; j < old.nodeList[i]->toNodes.size(); j++) {
			int id = old.nodeList[i]->toNodes[j]->id; // This id refers to the id that this node connects to, as per the last nodelist.

			//TODO: Something is causing the previous cell to have incorrect tonode ids. Have to fix, causing crashes.

			if (id < 0) {
				id = 0;
			}
			else if (id >= old.nodeList.size()) {
				id = old.nodeList.size() - 1;
			}

			ConnectNode(i, id, old.nodeList[i]->getWeight(j)); // (1 / (1 + exp((*world).nextRand()))) / 1000.0

			// Unused code currently, decided to go a different route but keeping this for posterity and reference.
			/*
			if (id < nodeList.size() && i < nodeList.size()) {
				ConnectNode(i, id);
			}
			else if (i > nodeList.size() && id > nodeList.size()) {
				id = world->nextRand() * nodeList.size();
				ConnectNode(i, id);
			}
			else if (i > nodeList.size()) {

				id = world->nextRand() * nodeList.size();

				ConnectNode(i, id);

			}
			else if (id > nodeList.size()) {
				id = world->nextRand() * nodeList.size();

				ConnectNode(i, id);
			}
			*/
		}

	}

	// Mutate

	for (int i = 0; i < muts; i++) {

		double chance = world->nextRand();

		if (chance >= 0.9) {
			int hiddenNodeCount = nodeList.size() - inputs.size() - outputs.size();

			if (chance >= 0.95) {

				int placement = inputs.size() + (int)((nodeList.size() - inputs.size() - outputs.size()) * world->nextRand());

				Node* n = new Node(placement);

				nodeList.insert(nodeList.begin() + placement, n);

				for (int j = placement + 1; j < nodeList.size(); j++) {
					nodeList[j]->id += 1;
				}

				std::cout << "New node! " << nodeList.size() << std::endl;
			}
			else if(hiddenNodeCount > 0){
				unsigned int nodeID = inputs.size() + floor(hiddenNodeCount * world->nextRand());

				Node* n = nodeList[nodeID];


				//delete nodeList[inputs.size() + nodeID];
				//nodeList.erase(nodeList.begin() + nodeID);

				for (int j = nodeID + 1; j < nodeList.size(); j++) { // Go through all of the nodes that will be impacted by the removal, including the removed.

					nodeList[j]->id--; // update their id to represent the lost node.
				}

				std::vector<Node*> buffer = n->fromNodes;

				nodeList.erase(nodeList.begin() + nodeID);
				delete n;


				//for (int j = nodeID; j < nodeList.size(); j++) { // Go through all of the nodes that will be impacted by the removal, including the removed.


				//	std::vector<Node*> buffer = nodeList[j]->fromNodes; // get all the connections the this node has

				//	for (int k = 0; k < buffer.size(); k++) {

				//		unsigned int connID = buffer[k]->getConnectionTo(nodeList[j]); // get the old connection to this node

				//		double weight = buffer[k]->getWeight(connID);

				//		buffer[k]->toNodes.erase(nodeList[j]->toNodes.begin() + connID); // and erase it.

				//		//int id2 = (nodeList.size() - 2) * world->nextRand();

				//		//ConnectToRandomNode()

				//	}

				//}


//				for (int j = 0; j < buffer.size(); j++) {
//					ConnectToRandomNode(buffer[j]->id);
//				}


				std::cout << "Erased a node! " << nodeList.size() << std::endl;
			}
		}
		else if (chance >= 0.8) {
			int id1 = (nodeList.size() - 1) * world->nextRand();
			int id2 = (nodeList.size() - 1) * world->nextRand();

			MutateConnection(id1, id2);
		}



	}


}

void NeuralNet::ConnectToRandomNode(int node) {
	int id2 = (nodeList.size() - 1) * world->nextRand();

	ConnectNode(node, id2);
}

void NeuralNet::ConnectToRandomNode(int node, double weight) {

	int id2 = (nodeList.size() - 1) * world->nextRand();

	ConnectNode(node, id2, weight);
}

bool NeuralNet::recurseLoopFinder(Node* ntf, Node* node) {
	if (node->toNodes.size() == 0) {
		return false;
	}
	if (node == ntf) {
		return true;
	}
	
	for (int i = 0; node->toNodes.size(); i++) {
		recurseLoopFinder(ntf, node->toNodes[i]);
	}

	return false;
}

void NeuralNet::ConnectNode(int node1, int node2) {
	if (node2 < inputs.size()) {
		//return; // these are the inputs, we don't want to connect back to the inputs.
	}

	nodeList[node1]->ConnectNode(nodeList[node2], (1 / (1 + exp((*world).nextRand()))) / 1000.0);
}

void NeuralNet::ConnectNode(int node1, int node2, double weight) {
	if (node2 < inputs.size()) {
		//return; // these are the inputs, we don't want to connect back to the inputs.
	}

	nodeList[node1]->ConnectNode(nodeList[node2], weight);
}

void NeuralNet::MutateConnection(int node1, int node2) {
	double chance = world->nextRand();

	if (nodeList[node1]->isConnectedTo(nodeList[node2])) {
		int connID = nodeList[node1]->getConnectionTo(nodeList[node2]);

		
		//std::cout << "Connection found!" << std::endl;

		if (chance >= 0.8) { // remove the connection.
			std::cout << "Connection erased!" << std::endl;

			nodeList[node1]->toNodes.erase(nodeList[node1]->toNodes.begin() + connID);
			return;
		}
		else {
			std::cout << "Connection mutated!" << std::endl;
			nodeList[node1]->weights[connID] = nodeList[node1]->weights[connID] + (world->nextRand() * 2 - 1) * world->worldMutator;
		}

	}
	else {
		std::cout << "New connection made!" << std::endl;
		ConnectNode(node1, node2);
	}
}


// This is an unused function currently as I found that sigmoiding the values of the neural network resulted in uninteresting
// behaviors. I may use it in the future though.
void NeuralNet::Sigmoid() {


	for (int i = 0; i < outputs.size(); i++) {
		outputs[i]->Sigmoid();
	}

	for (int i = nodeList.size() - inputs.size() - outputs.size(); i >= 0; i--) {

		nodeList[i + inputs.size()]->Sigmoid();

	}

	for (int i = 0; i < inputs.size(); i++) {
		inputs[i]->Sigmoid();
	}
}

std::vector<double> NeuralNet::send(std::vector<double> inVals)
{
	std::vector<double> outs;

	if (inVals.size() != inputs.size()) {
		return outs;
	}

	for (int i = 0; i < inputs.size(); i++) {
		nodeList[i]->addValue(inVals[i]);
		nodeList[i]->passThru();
	}

	for (int i = nodeList.size() - inputs.size() - outputs.size(); i >= 0; i--) {

		nodeList[i + inputs.size()]->passThru();

	}
	
	for (int i = 0; i < outputs.size(); i++) {

		outs.push_back(nodeList[nodeList.size() - outputs.size() + i]->getValue());

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

NeuralNet* NeuralNet::mutate() {
	NeuralNet* buffer = new NeuralNet(*this, world->worldMutator);

	return buffer;
}