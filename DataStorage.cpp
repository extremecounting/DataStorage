// DataStorage.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "json.hpp"
#include "Constants.h"
#include "Utilities.h"
#include "InputLayer.h"
#include "HiddenLayer.h"
#include "OutputLayer.h"
#include "Debug.h"

#include <iostream>
#include <random>
#include <fstream>


using json = nlohmann::json;


int main()
{
    json data;
    std::ofstream file(inputLayerPath);
    data["inputNeurons"] = {};
    if (file.is_open()) {
        file << data.dump(2); // pretty print with indentation of 4 spaces
        file.close();
        std::cout << "JSON data has been written to file\n";
    } else {
        std::cerr << "Unable to open file\n";
        return 1;
    }
    
    InputLayer inputLayer;
    HiddenLayer hiddenLayer;
    HiddenLayer hiddenLayer2;
    OutputLayer outputLayer;

    inputLayer.createNeurons(randomInputs(8)); // creates an input layer with 8 random inputs as values
    hiddenLayer.createNeurons(emptyValues(16));
    hiddenLayer2.createNeurons(emptyValues(16));
    outputLayer.createNeurons(emptyValues(10));
    
    hiddenLayer.connectInputLayer(inputLayer); // hiddenLayer1 -> inputLayer
    hiddenLayer2.connectHiddenLayer(hiddenLayer); // hiddenLayer2 -> hiddenLayer1
    outputLayer.connectHiddenLayer(hiddenLayer2); // outputLayer -> hiddenLayer2

    displayInLayer(inputLayer);
    displayHidLayer(hiddenLayer);
    displayHidLayer(hiddenLayer2);
    displayOutLayer(outputLayer);

    std::vector<float> costs = outputLayer.getCostFunc(randomInputs(10));
    
    for (int i = 0; i < costs.size(); i++) {
        std::cout << costs[i] << "\n";
    }
    inputLayer.saveData();
    return 0;
}