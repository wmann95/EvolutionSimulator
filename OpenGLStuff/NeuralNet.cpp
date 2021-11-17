#include "NeuralNet.h"
#include "Node.h"
#include <vector>

double weight = 0.5;
World* world;

NeuralNet::NeuralNet(World* w) {
	world = w;
	Initialize(3, 5, 5, 3);
}

void NeuralNet::Initialize(int inNodeCount, int hLayerCount, int hLayerNodeCount, int outNodeCount) {

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

					n.ConnectNode(&(outputs[k]), (*world).nextRand());

				}
			}
			else {
				for (int k = 0; k < hLayerNodeCount; k++) {

					int index = hLayerCount - i - 2;

					n.ConnectNode(&((hiddenLayers[index])[k]), (*world).nextRand());
				}
			}

			layer.insert(layer.begin(), n);
		}

		hiddenLayers.push_back(layer);
	}

	for (int i = 0; i < inNodeCount; i++) {
		Node n;

		for (int j = 0; j < hLayerNodeCount; j++) {
			n.ConnectNode(&(hiddenLayers[0][j]), (*world).nextRand());
		}

		inputs.push_back(n);
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