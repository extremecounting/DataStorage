#pragma once
#ifndef CLASSES_H2 // Include guard to prevent double inclusion
#define CLASSES_H2

#include <vector>
#include <random>

class HiddenNeuron {
public:
    HiddenNeuron(const float valueIn) {
        bias = getRandom();
        value = sigmoid(valueIn + bias);
    }
    void setWeights(int amount) {
        weights.reserve(amount);
        outputs.reserve(amount);
        float randWeight = getRandom();
        for (int i = 0; i < amount; i++) {
            weights.push_back(randWeight);
            outputs.push_back(value * randWeight);
        }
    }
    float value;
    float bias;
    std::vector<float> weights;
    std::vector<float> outputs;
};

class HiddenLayer {
public:
    HiddenLayer(const std::vector<HiddenNeuron> hiddenNeurons) : hiddenNeurons(hiddenNeurons) {
        amount = hiddenNeurons.size();
    };
    HiddenLayer() {};
    void connectInputLayer(InputLayer& layer) {
        amount = hiddenNeurons.size();
        layer.calcOutputSums(amount);
        for (int i = 0; i < amount; i++) {
            setNeuronValue(i, layer.getOutputSum(i));
        }
    }
    void connectHiddenLayer(HiddenLayer& layer) {
        amount = hiddenNeurons.size();
        layer.calcOutputSums(amount);
        for (int i = 0; i < amount; i++) {
            setNeuronValue(i, layer.getOutputSum(i));
        }
    }
    void setNeuronValue(int index, float value) {
        hiddenNeurons[index] = HiddenNeuron(value);
    }
    void createNeurons(const std::vector<float> values) {
        for (float value : values) {
            hiddenNeurons.push_back(HiddenNeuron(value));
        }
        amount = hiddenNeurons.size();
    }
    void calcOutputSums(int neuronsNextLayer) {
        outputSums.clear();
        outputSums.resize(neuronsNextLayer);
        for (int i = 0; i < hiddenNeurons.size(); i++) {
            hiddenNeurons[i].setWeights(neuronsNextLayer);
        }
        for (int i = 0; i < neuronsNextLayer; i++) {
            for (int j = 0; j < hiddenNeurons.size(); j++) {
                outputSums[i] += hiddenNeurons[j].outputs[i];
            }
        }
    }
    //gradient includes LR * error * σ'(aw+b)
    void backpropagate(float gradient, int index) {
        for (int i = 0; i < hiddenNeurons.size(); i++) {
            hiddenNeurons[i].weights[index] += gradient * hiddenNeurons[i].value;
        }
    }
    float getOutputSum(int index) {
        return outputSums[index];
    }
    std::vector<float> getOutputSum() {
        return outputSums;
    }
    float getSize() {
        return amount;
    }
    std::vector<HiddenNeuron> getNeurons() {
        return hiddenNeurons;
    }
private:
    std::vector<HiddenNeuron> hiddenNeurons;
    int amount = 0;
    std::vector<float> outputSums;
};

class HiddenLayerGroup {
public:
    HiddenLayerGroup(const std::vector<HiddenLayer> hiddenLayers) : hiddenLayers(hiddenLayers) {
        amount = hiddenLayers.size();
    };
    HiddenLayerGroup() {};
    void AddLayer(const HiddenLayer hiddenLayer) {
        hiddenLayers.push_back(hiddenLayer);
        amount++;
    }
    HiddenLayer getLayer(int i) {
        return hiddenLayers[i];
    }
private:
    std::vector<HiddenLayer> hiddenLayers;
    int amount = 0;
};
#endif // CLASSES_H