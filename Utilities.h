#pragma once
#ifndef CLASSES_H4 // Include guard to prevent double inclusion
#define CLASSES_H4
#include "InputLayer.h"
#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <fstream>

using json = nlohmann::json;

void addElementJson(std::string path, std::string name, float element) {
    std::ifstream readFile(path);
    json data;

    if (readFile.is_open()) {
        readFile >> data;
        readFile.close();
    } else {
        std::cerr << "Can't open file!";
        return;
    }

    std::ofstream writeFile(path);
    data[name].push_back(element);
    writeFile << data.dump(2);
    writeFile.close();
}

void addElementJson(std::string path, std::string name, std::vector<float> elements) {
    std::ifstream readFile(path);
    json data;

    if (readFile.is_open()) {
        readFile >> data;
        readFile.close();
    } else {
        std::cerr << "Can't open file!";
        return;
    }

    std::ofstream writeFile(path);
    data[name].push_back(elements);
    writeFile << data.dump(2);
    writeFile.close();
}

void addNeuronJson(InputNeuron neuron) {
    std::ifstream readFile(inputLayerPath);
    json data;

    if (readFile.is_open()) {
        readFile >> data;
        readFile.close();
    } else {
        std::cerr << "Can't open file!";
        return;
    }

    //data.size();
    std::cout << ">>" << data.size() << "<<";

    std::ofstream writeFile(inputLayerPath);
    writeFile << data.dump(2);
    writeFile.close();
    return;
}

void getInputNeuronJson(int index, std::string name) {
    std::ifstream readFile(inputLayerPath);
    json data;

    if (readFile.is_open()) {
        readFile >> data;
        readFile.close();
    } else {
        std::cerr << "Can't open file!";
        return;
    }
    std::cout << ">" << data[name] << "<";
    //data["N" + index]
    //InputNeuron neuron = 
    return;
}

float getRandom() {
    return ((float)(std::rand() % 10000) - 5000) / 10000;
}
float sigmoid(float value) {
    return (float)1.0 / (1.0 + std::exp(-value));
}
float sigmoidD(float input) {
    return (sigmoid(input) * (1-sigmoid(input)));
}
//creates the desired amount of random floats
std::vector<float> randomInputs(int length) {
    std::vector<float> inputs;
    for (int i = 0; i < length; i++) {
        inputs.push_back((float)(std::rand() % 1000) / 1000);
    }
    return inputs;
}

std::vector<float> emptyValues(int length) {
    std::vector<float> values;
    for (int i = 0; i < length; i++) {
        values.push_back(0.0f);
    }
    return values;
}

#endif // CLASSES_H