//
// Created by khadimou on 31/01/2020.
//

#ifndef DETECTION_NEURONMATH_H
#define DETECTION_NEURONMATH_H

typedef unsigned u32;
typedef unsigned char byte;
typedef unsigned long long u64;

#define INDEX(x, y, w) (((x) * (w)) + (y))

class calcul{
public:
    int convolve(byte *m,u64 mh,u64 mw,int *f,u64 fh,u64 fw);
};

#endif //DETECTION_NEURONMATH_H
