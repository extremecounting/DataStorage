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
    std::vector<float> getCostFunc(const std::vector<float>& correctResult) {
        std::vector<float> costs;
        int least = std::min(outputNeurons.size(), correctResult.size());
        for (int i = 0; i < least; i++) {
            float error = outputNeurons[i].value - correctResult[i];
            float cost = 0.5 * std::pow(error, 2);
            costs.push_back(cost);
        }
        return costs;
    }
    void backpropagae(const std::vector<float>& correctResult, float laerningRate) {
        int least = std::min(outputNeurons.size(), correctResult.size());
        for (int i = 0; i < least; i++) {
            float error = outputNeurons[i].value - correctResult[i];
            float gradient = error * sigmoidD(outputNeurons[i].value);
            for (int j =  0; j < outputNeurons[i].weights.size(); j++) { //__HIDDEN NEURONS__
                outputNeurons[i]. -= learningRate * gradient * outputNeurons[i].outputs[j];
            }

        }
    }
private:
    std::vector<OutputNeuron> outputNeurons;
    int amount = 0;
    float outputSum;
};

#endif // CLASSES_H