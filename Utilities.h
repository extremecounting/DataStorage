#pragma once
#ifndef CLASSES_H4 // Include guard to prevent double inclusion
#define CLASSES_H4
#include <cmath>
#include <iostream>
#include <random>
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