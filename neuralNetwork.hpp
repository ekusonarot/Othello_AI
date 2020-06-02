#ifndef NEURALNETWORK_HPP
#define NEURALNETWORK_HPP

#include <fstream>
#include <iostream>
#include <vector>
#include <random>
#include <cassert>
#include <string>
#include <sstream>
#include "CPULayers.hpp"

static const int IN_NUM = 128;
static const int HID_1_NUM = 64;
static const int HID_2_NUM = 64;
static const int OUT_NUM = 1;

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<float> unif(-1.0f, 1.0f);


const int ETA = 0.1;

class NN {
    std::vector<float> layer1_weights;
    std::vector<float> layer1_biases;
	
    std::vector<float> layer2_weights;
    std::vector<float> layer2_biases;

    std::vector<float> layer3_weights;
    std::vector<float> layer3_biases;

    double relu(double);
    double relu_prime(double);
public:
    NN();
    double eval(int*);
    double learn(int*,double*);
    void saveWeight();
};

inline NN::NN() {

    std::ifstream openfile("weight");

    if (!openfile) {
        for (int i = 0; i < IN_NUM * HID_1_NUM; i++) {
            layer1_weights.push_back(unif(gen));
        }
        for (int i = 0; i < HID_1_NUM; i++) {
            layer1_biases.push_back(unif(gen));
        }

        for (int i = 0; i < HID_1_NUM * HID_2_NUM; i++) {
            layer2_weights.push_back(unif(gen));
        }
        for (int i = 0; i < HID_2_NUM; i++) {
            layer2_biases.push_back(unif(gen));
        }

        for (int i = 0; i < HID_2_NUM * OUT_NUM; i++) {
            layer3_weights.push_back(unif(gen));
        }
        for (int i = 0; i < OUT_NUM; i++) {
            layer3_biases.push_back(unif(gen));
        }
    } else {
        std::cout << "Found file\n";
        std::string line;
        size_t count = 0;
        while(getline(openfile, line)) {
            std::stringstream iss(line);
            float weight;
            std::vector<float> weights;
            while(iss >> weight) {
                weights.emplace_back(weight);
            }
            if (count == 0) {
                layer1_weights = std::move(weights);
            } else if (count == 1) {
                layer1_biases = std::move(weights);
            } else if (count == 2) {
                layer2_weights = std::move(weights);
            } else if (count == 3) {
                layer2_biases = std::move(weights);
            } else if (count == 4) {
                layer3_weights = std::move(weights);
            } else if (count == 5) {
                layer3_biases = std::move(weights);
            }      
            count++;
            assert(count <= 6);
        }
    }

    assert(layer1_weights.size() == IN_NUM    * HID_1_NUM);
    assert(layer2_weights.size() == HID_1_NUM * HID_2_NUM);
    assert(layer3_weights.size() == HID_2_NUM * OUT_NUM);
    assert(layer1_biases.size() == HID_1_NUM);
    assert(layer2_biases.size() == HID_2_NUM);
    assert(layer3_biases.size() == OUT_NUM);
}

inline void NN::saveWeight() {
    std::ofstream openfile("weight");
    if (!openfile){
        std::cout << "file not opened" << std::endl;
        system("pause");
    }else {
        for (int i = 0; i < IN_NUM * HID_1_NUM; i++) {
            openfile << layer1_weights[i] << ' ';
        }
        openfile << std::endl;
        for (int i = 0; i < HID_1_NUM; i++) {
            openfile << layer1_biases[i] << ' ';
        }
        openfile << std::endl;
        for (int i = 0; i < HID_1_NUM * HID_2_NUM; i++) {
            openfile << layer2_weights[i] << ' ';
        }
        openfile << std::endl;
        for (int i = 0; i < HID_2_NUM; i++) {
            openfile << layer2_biases[i] << ' ';
        }
        openfile << std::endl;
        for (int i = 0; i < HID_2_NUM * OUT_NUM; i++) {
            openfile << layer3_weights[i] << ' ';
        }
        openfile << std::endl;
        for (int i = 0; i < OUT_NUM; i++) {
            openfile << layer3_biases[i] << ' ';
        }
    }
}

inline double NN::relu(double x) {
    if (0 < x) return x;
    return 0;
}

inline double NN::relu_prime(double x) {
    if (0 < x) return 1;
    return 0;
}

/*
    INPUT: 長さ128の配列
*/
inline double NN::eval(int* Input) {
    int i,j;
    std::vector<float> features;
    for (int i = 0; i < IN_NUM; ++i) {
        features.push_back(Input[i]);
    }

    //第1層
    std::vector<float> layer1_output(HID_1_NUM);
    FullyConnect::Forward(IN_NUM, HID_1_NUM, features, layer1_weights, layer1_biases, layer1_output, true);

    //第2層
    std::vector<float> layer2_output(HID_2_NUM);
    FullyConnect::Forward(HID_1_NUM, HID_2_NUM, layer1_output, layer2_weights, layer2_biases, layer2_output, true);

    //第3層
    std::vector<float> layer3_output(OUT_NUM);
    FullyConnect::Forward(HID_2_NUM, OUT_NUM, layer2_output, layer3_weights, layer3_biases, layer3_output, false);

    return layer3_output[i];
}


/*
    double w1[HID_1_NUM][IN_NUM+1];
    double z1[HID_1_NUM];
    double w2[HID_2_NUM][HID_1_NUM+1];
    double z2[HID_2_NUM];
    double w3[OUT_NUM][HID_2_NUM+1];
    double z3[OUT_NUM];
*/
inline double NN::learn(int* Input,double* Toutput) {
    /*
    /  使用 pytotch 訓練
    /  Using pytotch to train the network. The file is at train.py. The dataload is not complate.
    /*


/*
    double delta_w3[OUT_NUM]={0};
    double delta_w2[HID_2_NUM]={0};
    double delta_w1[HID_1_NUM]={0};

    eval(Input);

    double error = 0;
    for (int i=0; i<OUT_NUM; i++) {
        error = (z3[i] - Toutput[i])*(z3[i] - Toutput[i]);
    }
	int j=0;
    // w3重み更新
    for (int i=0; i<OUT_NUM; i++) {
        delta_w3[i] = relu_prime(z3[i])*(z3[i]-Toutput[i]);
        for (j=0; j<HID_2_NUM; j++) {
            w3[i][j] += ETA * delta_w3[i] * z2[j];
        }
        //バイアスユニット
        w3[i][j] += ETA * delta_w3[i];
    }

    // w2重み更新
    for (int i=0; i<HID_2_NUM; i++) {
        for (int j=0; j<OUT_NUM; j++) {
            delta_w2[i] += delta_w3[j]*w3[i][j]*relu_prime(z2[i]);
        }
        for (int j=0; j<HID_1_NUM; j++) {
            w2[j][i] += ETA * delta_w2[i] * z1[j];
        }
        //バイアスユニット
        w2[i][j] += ETA * delta_w2[i];
    }

    // w1重み更新
    for (int i=0; i<HID_1_NUM; i++) {
        for (int j=0; j<HID_2_NUM; j++) {
            delta_w1[i] += delta_w2[j]*w2[i][j]*relu_prime(z1[i]);
        }
        for (int j=0; j<IN_NUM; j++) {
            w1[j][i] += ETA * delta_w1[i] * Input[j];
        }
        //バイアスユニット
        w1[i][j] += ETA * delta_w1[i];
    }

    return error;
*/
	return 0.0f;
}

#endif // NEURALNETWORK_HPP
