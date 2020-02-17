// Created by khadimou on 13/02/2020.
//

#ifndef DETECTION_TRAINER_H
#define DETECTION_TRAINER_H

#include <random>
#include <string>
#include "ppmimg.h"

class train
{
public:
    float relu(float x);
    float d_relu(float x);
    void init(int n_w,int n_h); // parameters : input layer and hidden layer
    void forming_input_weights(int n_h,int n_w,const byte *pixel);
    void forming_layer_weights(int n_h);
    void updating_weights(int n_h,int n_w,byte *pixel);
    void trainer(int n_w,int n_h,ppm& img);

private:
    float somme,err = 0.,lr = 1.0; //learning rate = 1
    bool output[2]= {0,1};
    int n = 25; //nombre d'entrée
    float* m_h,*m_lhd;
    float** m_lw0;
    float** lw_d;
    float** weights;
};

#endif //DETECTION_TRAINER_H
