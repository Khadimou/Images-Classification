//
// Created by khadimou on 13/02/2020.
//
#include "trainer.h"
#include <math.h>

float train::relu(float x) {
    if(x>0){
        return x;
    } else{
        return 0;
    }
}

float train::d_relu(float x) {
    if(x>0){
        return 1;
    } else{
        return 0;
    }
}

float train::sigmoid(float x)
{
    return 1.0 / (1.0 + exp(-x));
}

std::vector<float> train::softmax(std::vector<float> x) {
    auto somme = 0.;
    std::vector<float> proba(x.size());
    for(auto i=0;i<x.size();i++){
        somme += exp(x[i]);
        proba[i] = exp(x[i])/somme;
        //std::cout << proba[i] << " ";
    }
    return proba;
}

void train::init(int n_w,int n_h) {

    float** w0 = new float* [n_w];
    weights = new float* [n_w];

    float *h = new float[n_h];
    m_h = new float[n_h];

    for (int i = 0; i < n_w; i++) {
        w0[i] = new float[n_h];
        weights[i] = new float[n_h];
        for (int j = 0; j < n_h; j++) {
            w0[i][j] = (2.0 * rand())/ RAND_MAX - 1;
            //w0[i][j] =(sqrt(-2.0 * log((float) rand() / RAND_MAX))) * (cos(6.28318530718 * (float) rand() / RAND_MAX));
            //std::cout << w0[i][j] << " ";
            weights[i][j] = w0[i][j];
        }
    }

    for (int i = 0; i < n_h; i++) {
        h[i] = (2.0 * rand()) / RAND_MAX - 1;
        //h[i] = (sqrt(-2.0 * log((float) rand() / RAND_MAX))) * (cos(6.28318530718 * (float) rand() / RAND_MAX));
        m_h[i] = h[i];
        //std::cout << m_h[i] << " ";
    }
    delete [] h;
    for(int i = 0; i < n_w; ++i) {
        delete [] w0[i];
    }
    delete [] w0;
}

void train::forming_input_weights(int n_h,int n_w,const byte *pixel) {

    float** lw0 = new float* [n];

    m_lw0 = new float* [n];

    for(int k=0;k<n;k++){
        lw0[k] = new float[n_w];
        m_lw0[k] = new float[n_w];
        for (int i = 0; i < n_h; i++){
            somme = 0.0;
            for (int j = 0; j < n_w; j++) {
                somme += pixel[k] * weights[j][i];
            }

                lw0[k][i] = relu(somme);
                //std::cout << lw0[k][i] << " ";
                m_lw0[k][i] = lw0[k][i];
        }
    }
    for(int i = 0; i < n; ++i) {
        delete [] lw0[i];
    }
    delete [] lw0;
}

void train::forming_layer_weights(int n_h) {
    float* lh= new float [n];
    float* lh_d= new float [n];
    float** lw0_d = new float* [n];
    lw_d = new float* [n];
    m_lhd= new float [n];
    std::vector<float> squash(n);
    // forming lh_d
    for (int j = 0; j < n; j++)
    {
        auto s = 0.0;

        for (int k = 0; k < n_h; k++) {
            s += (m_lw0[j][k] * m_h[k]);
        }

            lh[j] = relu(s);
            squash[j] = lh[j];
            auto layer_squashed = softmax(squash);
            //std::cout << layer_squashed[j] << " ";
            err += fabs(layer_squashed[j] - output[1]);

            lh_d[j] = (lh[j] - output[1]) * d_relu(lh[j]);
            m_lhd[j] = lh_d[j];
    }
    // forming lw_d
    for (int j = 0; j < n; j++) {
        lw0_d[j] = new float [n_h];
        lw_d[j] = new float [n_h];
        for (int k = 0; k < n_h; k++) {
            lw0_d[j][k] = lh_d[j] * m_h[k] * d_relu(m_lw0[j][k]);
            lw_d[j][k] = lw0_d[j][k];
            //std::cout << lw0_d[j][k] << " ";
        }
    }
    delete [] lh;
    delete [] lh_d;
    for(int i = 0; i < n; ++i) {
        delete [] lw0_d[i];
    }
    delete [] lw0_d;
}

void train::updating_weights(int n_h,int n_w,byte *pixel) {
    //Updating w0
    for (int j = 0; j < n_w; j++)
    {
        for (int k = 0; k < n_h; k++)
        {
            auto s = 0.0;

            for (int l = 0; l < n; l++)
                s += (pixel[j] * lw_d[l][k]);

            weights[j][k] -= (lr * s);
            //std::cout << weights[j][k] << " ";
        }
    }

    //Updating h
    for (int j = 0; j < n_h; j++)
    {
        auto s = 0.0;

        for (int k = 0; k < n; k++)
            s += (m_lw0[k][j] * m_lhd[k]);

        m_h[j] -= (lr * s);
    }
}

void train::trainer(int n_w, int n_h,ppm& img) {
    // initialisation
    int retrains = 0;
    // back prop
    for (auto i = 0;; i++) {

        init(n_w, n_h);
        forming_input_weights(n_h, n_w, img.px);
        forming_layer_weights(n_h);
        updating_weights(n_h, n_w, img.px);


            //std::cout << err << " ";
            float err_n = err / (float) n;

            i = 0;

            //Roll around untill error is acceptable
                if (err_n > 0.1) {
                    retrains++;
                    init(n_w, n_h);
                }


                //Mean absolute error
                printf("retrains: %d, err: %lf\n", retrains, err_n);
                /*for(int i=0;i <n_w;i++){
                    delete [] weights[i];
                }
                delete [] weights;*/
                delete[] m_lhd;
                for (int i = 0; i < n; ++i) {
                    delete[] lw_d[i];
                    delete[] m_lw0[i];
                }
                delete[] lw_d;
                delete[] m_lw0;
                //delete [] m_h;
                break;

    }

}

