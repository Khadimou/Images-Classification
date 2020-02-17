//
// Created by khadimou on 20/01/2020.
//

#ifndef NEURALNETWORKAI_FILTRE_H
#define NEURALNETWORKAI_FILTRE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <streambuf>
#include "ppmimg.h"
#include "neuronmath.h"
#include "pgmimg.h"

class Filter
{
public :
    Filter(){};
    Filter(int w,int h,byte *px);
    virtual void rgbtogray() = 0;
    virtual ~Filter(){};
protected:
    int m_t,m_w,m_h;
    byte *m_px;
};

class filtre: public Filter
{
public:
    filtre(){};
    filtre(int w,int h,byte *px);
    void rgbtogray() ;
    ~filtre(){};
};

#endif //NEURALNETWORKAI_FILTRE_H
