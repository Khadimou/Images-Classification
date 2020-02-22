//
// Created by khadimou on 20/02/2020.
//

#ifndef DETECTION_TEST_H
#define DETECTION_TEST_H

#include "trainer.h"
#include "ppmimg.h"

class test{
public:
    void output_test(train& input,int n_w,int n_h,const ppm& img);
};
#endif //DETECTION_TEST_H
