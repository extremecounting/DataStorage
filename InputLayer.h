#pragma once
#ifndef CLASSES_H // Include guard to prevent double inclusion
#define CLASSES_H

#include "Utilities.h"
#include "json.hpp"
#include <vector>
#include <random>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

class InputNeuron {
public:
    InputNeuron(const float value) : value(value) {};
    InputNeuron(const float value, std::vector<float> weights, std::vector<float> outputs) : value(value), weights(weights), outputs(outputs) {};
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
    void saveData() {
        json data;
        data["inputNeurons"].push_back(1);
        //data["inputNeurons"].push_back({value, {weights}, {outputs}});
        std::ofstream file(inputLayerPath);
        if (file.is_open()) {
            std::cout << "Test";
            file.close();
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
    void saveData() {
        for (int i = 0; i < inputNeurons.size(); i++) {
            inputNeurons[i].saveData();
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