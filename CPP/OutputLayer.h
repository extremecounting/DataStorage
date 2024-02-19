#pragma once
#ifndef CLASSES_H3 // Include guard to prevent double inclusion
#define CLASSES_H3

#include <vector>
#include <random>
#include <cmath>

class OutputNeuron {
public:
    OutputNeuron(const float value) : value(value) {
        bias = getRandom();
        output = sigmoid(value + bias);
    }
    float value;
    float output;
    float bias;
};

class OutputLayer {
public:
    OutputLayer(const std::vector<OutputNeuron> outputNeurons) : outputNeurons(outputNeurons) {
        amount = outputNeurons.size();
        calcOutputSum();
    };
    OutputLayer() {
        outputSum = 0;
    };
    void connectHiddenLayer(HiddenLayer& layer) {
        amount = outputNeurons.size();
        layer.calcOutputSums(amount);
        for (int i = 0; i < amount; i++) {
            setNeuronValue(i, layer.getOutputSum(i));
        }
    }
    void setNeuronValue(int index, float value) {
        outputNeurons[index] = OutputNeuron(value);
    }
    void createNeurons(const std::vector<float> values) {
        for (float value : values) {
            outputNeurons.push_back(OutputNeuron(value));
        }
        amount = outputNeurons.size();
    }
    void calcOutputSum() {
        outputSum = 0;
        for (OutputNeuron neuron : outputNeurons) {
            outputSum += neuron.output;
        }
    }
    std::vector<OutputNeuron> getNeurons() {
        return outputNeurons;
    }
    std::vector<float> getCostFunc(std::vector<float> correctResult) {
        std::vector<float> costs;
        int least = std::min(outputNeurons.size(), correctResult.size());
        for (int i = 0; i < least; i++) {
            //costs.push_back(std::exp(outputNeurons[i] - correctResult[i]), 2);
        }
        return costs;
    }
private:
    std::vector<OutputNeuron> outputNeurons;
    int amount = 0;
    float outputSum;
};

#endif // CLASSES_H