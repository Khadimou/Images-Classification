//
// Created by khadimou on 31/01/2020.
//
#include "neuronmath.h"


int calcul::convolve(byte *m, u64 mh, u64 mw, int *f, u64 fh, u64 fw) {
    auto r =0;

    for(u64 i =0;i<fh;i++){
        for(u64 j=0;j<fw;j++){
            r += m[INDEX(i,j,mw)] * f[INDEX(i,j,fw)];
        }
    }
    return r;
}

