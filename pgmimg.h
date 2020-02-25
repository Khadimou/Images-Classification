//
// Created by khadimou on 23/01/2020.
//

#ifndef DETECTION_PGMIMG_H
#define DETECTION_PGMIMG_H

#include "filtre.h"

class PGMImage
{
public :
    PGMImage(){};
    virtual void pgm_open(const char *fname) = 0;
    virtual void save_pgm(PGMImage& img,std::string fname) = 0;
    virtual ~PGMImage(){};
    virtual void pgm_sobel(byte *img_in,byte *img_out,unsigned long long h,unsigned long long w,float threshold,std::string fname) = 0;
    virtual void pgm_apply_prewitt_filter(byte *img_in, byte *img_out, u64 h, u64 w, float threshold,std::string fname) = 0;
    virtual void pgm_apply_kirsch_filter(byte *img_in, byte *img_out, u64 h, u64 w,std::string fname) = 0;

protected:
    int width,height,maxvalue;
    unsigned char *px;
    byte *p_out  ;
};

class handlepgm: public PGMImage
{
public:
    handlepgm(){};
    void pgm_open(const char *fname) ;
    void save_pgm(PGMImage& img, std::string fname);
    void pgm_apply_prewitt_filter(byte *img_in, byte *img_out, u64 h, u64 w, float threshold,std::string fname);
    void pgm_sobel(byte *img_in,byte *img_out,unsigned long long h,unsigned long long w,float threshold,std::string fname);
    void pgm_apply_kirsch_filter(byte *img_in, byte *img_out, u64 h, u64 w,std::string fname);
    ~handlepgm(){
        delete [] px;
    }
};

#endif //DETECTION_PGMIMG_H
