//
// Created by khadimou on 30/01/2020.
//

#ifndef DETECTION_PPMIMG_H
#define DETECTION_PPMIMG_H

#include "filtre.h"

class ppm
{
public:
    ppm(){};
    virtual void ppm_open(const char* fname)  = 0;
    virtual void save_ppm(ppm& img,std::string fname) =0;
    virtual ~ppm(){};
public:
    int w,h,t;
    unsigned char *px;
};

class handleppm: public ppm
{
public:
    handleppm(){};
    void ppm_open(const char *fname) ;
    void save_ppm(ppm& img,std::string fname);
    ~handleppm(){
        delete [] px;
    }
};


#endif //DETECTION_PPMIMG_H
