#pragma once
#ifndef CLASSES_H7
#define CLASSES_H7

#include "InputLayer.h"
#include "HiddenLayer.h"
#include "OutputLayer.h"
#include "Constants.h"
#include "json.hpp"
#include <vector>
#include <random>
#include <fstream>
#include <iostream>

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

void addNeuronJson(InputNeuron neuron, int index) {
    //read file
    std::ifstream readFile(inputLayerPath);
    json data;

    if (readFile.is_open()) {
        readFile >> data;
        readFile.close();
    } else {
        std::cerr << "Can't open file!";
        return;
    }
    data["N" + index].push_back(neuron.value);
    data["N" + index].push_back(neuron.weights);
    data["N" + index].push_back(neuron.outputs);
    
    //data.size();
    //std::cout << ">>" << data.size() << "<<";
    //write
    std::ofstream writeFile(inputLayerPath);
    writeFile << data.dump(2);
    writeFile.close();
    return;
}

void storeInputLayer(InputLayer inputLayer) {
    json data;
    for (int i = 0; i < inputLayer.getNeurons().size(); i++) { // value, {weights}, {outputs}
        data["N" + std::to_string(i)].push_back(inputLayer.getNeurons()[i].value);
        data["N" + std::to_string(i)].push_back(inputLayer.getNeurons()[i].weights);
        data["N" + std::to_string(i)].push_back(inputLayer.getNeurons()[i].outputs);
    }
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

void storeHiddenLayer(HiddenLayer hiddenLayer, int index) {
    //read file
    std::ifstream readFile(hiddenLayerPath);
    json data;

    if (readFile.is_open()) {
        readFile >> data;
        readFile.close();
    } else {
        std::cerr << "Can't open file!";
        return;
    }
    std::string name;
    
    for (int i = 0; i < hiddenLayer.getNeurons().size(); i++) { // value, {weights}, {outputs}, bias
        name = "N" + std::to_string(index) + "." + std::to_string(i);
        data[name].push_back(hiddenLayer.getNeurons()[i].value);
        data[name].push_back(hiddenLayer.getNeurons()[i].weights);
        data[name].push_back(hiddenLayer.getNeurons()[i].outputs);
        data[name].push_back(hiddenLayer.getNeurons()[i].bias);
    }
    std::ofstream writeFile(hiddenLayerPath);
    writeFile << data.dump(2);
    writeFile.close();
    return;

}

void storeOutputLayer(OutputLayer outputLayer) {
    json data;
    for (int i = 0; i < outputLayer.getNeurons().size(); i++) { // value, output, bias
        data["N" + std::to_string(i)].push_back(outputLayer.getNeurons()[i].value);
        data["N" + std::to_string(i)].push_back(outputLayer.getNeurons()[i].output);
        data["N" + std::to_string(i)].push_back(outputLayer.getNeurons()[i].bias);
    }
    std::ofstream writeFile(outputLayerPath);
    writeFile << data.dump(2);
    writeFile.close();
    return;
}

#endif