//
// Created by khadimou on 20/02/2020.
//

#ifndef DETECTION_TEST_H
#define DETECTION_TEST_H

#include "trainer.h"
#include "ppmimg.h"
#include <algorithm>

class test{
public:
    void output_test(train& input,int n_w,int n_h,const ppm& img);
    std::string output_test_char(std::string res);
    std::string get_res(){return result;}
    void save_weights(train &t,std::string fname,int n_h,int n_w);
    void run_test(std::string fname,int n_w,int n_h,const ppm& img);
private:
    std::string result;
};
#endif //DETECTION_TEST_H
