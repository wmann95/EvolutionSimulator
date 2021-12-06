#include "NeuralNet.h"
#include "Node.h"
#include <vector>



NeuralNet::NeuralNet(World* w, int inNodeCount, int hLayerCount, int hLayerNodeCount, int outNodeCount) {

	for (int i = 0; i < outNodeCount; i++) {
		Node n;
		outputs.push_back(n);
	}

	for (int i = hLayerCount - 1; i >= 0; i--) {

		std::vector<Node> layer;

		for (int j = 0; j < hLayerNodeCount; j++) {
			Node n;

			if (i == hLayerCount - 1) {

				for (int k = 0; k < outNodeCount; k++) {

					n.ConnectNode(&(outputs[k]), (1 / (1 + exp((*world).nextRand()))) / 1000.0);

				}
			}
			else {
				for (int k = 0; k < hLayerNodeCount; k++) {

					int index = hLayerCount - i - 2;

					n.ConnectNode(&((hiddenLayers[index])[k]), (1 / (1 + exp((*world).nextRand()))) / 1000.0);
				}
			}

			layer.insert(layer.begin(), n);
		}

		hiddenLayers.push_back(layer);
	}

	for (int i = 0; i < inNodeCount; i++) {
		Node n;

		for (int j = 0; j < hLayerNodeCount; j++) {
			n.ConnectNode(&(hiddenLayers[0][j]), (1 / (1 + exp((*world).nextRand()))) / 1000.0);
		}

		inputs.push_back(n);
	}
}

NeuralNet::NeuralNet(const NeuralNet& old, double m) {

	world = old.world;

	for (int i = 0; i < old.outputs.size(); i++) {
		Node n;
		outputs.push_back(n);
	}

	for (int i = old.hiddenLayers.size() - 1; i >= 0; i--) {

		std::vector<Node> layer;

		for (int j = 0; j < old.hiddenLayers[i].size(); j++) {
			Node n;

			if (i == old.hiddenLayers.size() - 1) {
				for (int k = 0; k < old.outputs.size(); k++) {
					n.ConnectNode(&(outputs[k]), old.hiddenLayers[i][j].getWeight(k) + (world->nextRand() * 2 - 1) * m);
				}
			}
			else {
				for (int k = 0; k < old.hiddenLayers[i].size(); k++) {

					int index = old.hiddenLayers.size() - i - 2;

					n.ConnectNode(&((hiddenLayers[index])[k]), old.hiddenLayers[index + 1][j].getWeight(k) + (world->nextRand() * 2 - 1) * m);
				}
			}

			layer.insert(layer.begin(), n);
		}

		hiddenLayers.push_back(layer);
	}

	for (int i = 0; i < old.inputs.size(); i++) {
		Node n;

		for (int j = 0; j < hiddenLayers[0].size(); j++) {
			n.ConnectNode(&(hiddenLayers[0][j]), old.inputs[i].getWeight(j) + (world->nextRand() * 2 - 1) * m);
		}

		inputs.push_back(n);
	}
}

void NeuralNet::Sigmoid() {


	for (int i = 0; i < outputs.size(); i++) {
		//outputs[i].Sigmoid();
	}

	for (int i = hiddenLayers.size() - 1; i >= 0; i--) {

		for (int j = 0; j < hiddenLayers[i].size(); j++) {
			hiddenLayers[i][j].Sigmoid();
		}
	}

	for (int i = 0; i < inputs.size(); i++) {
		//inputs[i].Sigmoid();
	}
}

std::vector<double> NeuralNet::send(std::vector<double> inVals)
{
	std::vector<double> outs;

	if (inVals.size() != inputs.size()) {
		return outs;
	}

	for (int i = 0; i < inputs.size(); i++) {
		inputs[i].addValue(inVals[i]);
		inputs[i].passThru();
	}

	for (int i = 0; i < hiddenLayers.size(); i++) {

		for (int j = 0; j < hiddenLayers[i].size(); j++) {
			hiddenLayers[i][j].Sigmoid();
			hiddenLayers[i][j].passThru();
		}
	}


	for (int i = 0; i < outputs.size(); i++) {
		outs.push_back(outputs[i].getValue());
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