#pragma once
#ifndef CLASSES_H5 // Include guard to prevent double inclusion
#define CLASSES_H5
#include <cmath>
#include <iostream>
#include <random>

void displayInLayer(InputLayer layer) {
    int incr = 0;
    for (InputNeuron inputNeuron : layer.getNeurons()) {
        incr++;
        std::cout << "Neuron " << incr << ": " << "\n";
        if (inputNeuron.outputs.size() < 1) {
            std::cout << "EMPTY \n";
        }
        std::cout << "VALUE: \n";
        std::cout << inputNeuron.value << " \n";
        std::cout << "WEIGHTS: \n";
        for (float weight : inputNeuron.weights) {
            std::cout << " >" << weight << "< ";
        }
        std::cout << "\n";
        std::cout << "OUTPUTS: \n";
        for (double output : inputNeuron.outputs) {
            std::cout << " >" << output << "< ";
        }
        std::cout << "\n";
    }

    for (double sum : layer.getOutputSum()) {
        std::cout << "Sum: " << sum << "\n";
    }
    return;
}

void displayHidLayer(HiddenLayer layer) {
    int incr = 0;
    for (HiddenNeuron hiddenNeuron : layer.getNeurons()) {
        incr++;
        std::cout << "Neuron " << incr << ": " << "\n";
        if (hiddenNeuron.outputs.size() < 1) {
            std::cout << "EMPTY \n";
        }
        std::cout << "VALUE: \n";
        std::cout << hiddenNeuron.value << " \n";
        std::cout << "WEIGHTS: \n";
        for (float weight : hiddenNeuron.weights) {
            std::cout << " >" << weight << "< ";
        }
        std::cout << "\n";
        std::cout << "OUTPUTS: \n";
        for (double output : hiddenNeuron.outputs) {
            std::cout << " >" << output << "< ";
        }
        std::cout << "\n";
    }

    for (double sum : layer.getOutputSum()) {
        std::cout << "Sum: " << sum << "\n";
    }
    return;
}
void displayOutLayer(OutputLayer layer) {
    int incr = 0;
    for (OutputNeuron outputNeuron : layer.getNeurons()) {
        incr++;
        std::cout << "Neuron " << incr << ": " << "\n";
        std::cout << "VALUE: \n";
        std::cout << outputNeuron.value << " \n";
        std::cout << "\n";
        std::cout << "OUTPUT: \n";
        std::cout << " >" << outputNeuron.output << "< ";
        std::cout << "\n";
    }
    return;
}
#endif // CLASSES_H