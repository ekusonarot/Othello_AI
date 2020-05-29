#ifndef NEURALNETWORK_HPP
#define NEURALNETWORK_HPP

#include <fstream>
#include <iostream>

const int IN_NUM = 128;
const int HID_1_NUM = 64;
const int HID_2_NUM = 64;
const int OUT_NUM = 1;

const int ETA = 0.1;

class NN {
    double w1[HID_1_NUM][IN_NUM+1];
    double z1[HID_1_NUM];
    double w2[HID_2_NUM][HID_1_NUM+1];
    double z2[HID_2_NUM];
    double w3[OUT_NUM][HID_2_NUM+1];
    double z3[OUT_NUM];
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
        std::cout << "file not opened" << std::endl;
        system("pause");
    }else {
        for (int i=0; i < HID_1_NUM; i++) {
            for (int j=0; j<IN_NUM+1; j++) {
                openfile >> w1[i][j];
            }
        }
        for (int i=0; i < HID_2_NUM; i++) {
            for (int j=0; j<HID_1_NUM+1; j++) {
                openfile >> w2[i][j];
            }
        }
        for (int i=0; i < OUT_NUM; i++) {
            for (int j=0; j<HID_2_NUM+1; j++) {
                openfile >> w3[i][j];
            }
        }
    }
}

inline void NN::saveWeight() {
    std::ofstream openfile("weight");
    if (!openfile){
        std::cout << "file not opened" << std::endl;
        system("pause");
    }else {
        for (int i=0; i < HID_1_NUM; i++) {
            for (int j=0; j<IN_NUM+1; j++) {
                openfile << w1[i][j] << ' ';
            }
        }
        for (int i=0; i < HID_2_NUM; i++) {
            for (int j=0; j<HID_1_NUM+1; j++) {
                openfile << w2[i][j] << ' ';
            }
        }
        for (int i=0; i < OUT_NUM; i++) {
            for (int j=0; j<HID_2_NUM+1; j++) {
                openfile << w3[i][j] << ' ';
            }
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
    //第1層
    for (i=0; i<HID_1_NUM; i++) {
        z1[i] = 0;
        for (j=0; j<IN_NUM; j++) {
            z1[i] +=  w1[i][j] * Input[j];
        }
        //バイアスユニット
        z1[i] += w1[i][j];
        z1[i] = relu(z1[i]);
    }
    //第2層
    for (i=0; i<HID_2_NUM; i++) {
        z2[i] = 0;
        for (j=0; j<HID_1_NUM; j++) {
            z2[i] +=  w2[i][j] * z1[j];
        }
        //バイアスユニット
        z2[i] += w2[i][j];
        z2[i] = relu(z2[i]);
    }
    //第3層
    for (i=0; i<OUT_NUM; i++) {
        z3[i] = 0;
        for (j=0; j<HID_2_NUM; j++) {
            z3[i] +=  w3[i][j] * z2[j];
        }
        //バイアスユニット
        z3[i] += w3[i][j];
        z3[i] = relu(z3[i]);
    }
    return z3[i];
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
}

#endif // NEURALNETWORK_HPP