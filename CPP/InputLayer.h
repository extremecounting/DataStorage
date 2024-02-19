#pragma once
#ifndef CLASSES_H // Include guard to prevent double inclusion
#define CLASSES_H

#include <vector>
#include <random>

class InputNeuron {
public:
    InputNeuron(const float value) : value(value) {};
    void setWeights(int amount) {
        weights.reserve(amount);
        outputs.reserve(amount);
        float randWeight;
        for (int i = 0; i < amount; i++) {
            randWeight = getRandom();
            weights.push_back(randWeight);
            outputs.push_back(value * randWeight);
        }
    }
    std::vector<float> getOutputs() {
        return outputs;
    }
    float value;
    std::vector<float> weights;
    std::vector<float> outputs;
};

class InputLayer {
public:
    InputLayer(const std::vector<InputNeuron> inputNeurons) : inputNeurons(inputNeurons) {
        amount = inputNeurons.size();
    };
    InputLayer() {};
    void createNeurons(const std::vector<float> values) {

        for (float value : values) {
            inputNeurons.push_back(InputNeuron(value));
        }
        amount = inputNeurons.size();
    }
    void calcOutputSums(int neuronsNextLayer) {
        outputSums.clear();
        outputSums.resize(neuronsNextLayer);
        for (int i = 0; i < inputNeurons.size(); i++) {
            inputNeurons[i].setWeights(neuronsNextLayer);
        }
        for (int i = 0; i < neuronsNextLayer; i++) {
            for (int j = 0; j < inputNeurons.size(); j++) {
                outputSums[i] += inputNeurons[j].outputs[i];
            }
        }
    }
    std::vector<InputNeuron> getNeurons() {
        return inputNeurons;
    }
    float getOutputSum(int index) {
        return outputSums[index];
    }
    std::vector<float> getOutputSum() {
        return outputSums;
    }
private:
    std::vector<float> outputSums;
    std::vector<InputNeuron> inputNeurons;
    int amount = 0;
};
#endif // CLASSES_H