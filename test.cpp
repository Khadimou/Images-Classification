//
// Created by khadimou on 20/02/2020.
//
#include "test.h"

void test::output_test(train& input,int n_w,int n_h,const ppm& img) {
    float s,_s;
    float *l = new float[n_h];

    for(auto i=0;i<n_h;i++){
        s = 0.;

        for(auto j=0;j<n_w;j++){
            //std::cout << input.get_weights()[j][i] << "\n";
            s += img.px[j] * input.get_weights()[j][i];
        }

        l[i] = input.sigmoid(s);
        //std::cout << l[i] << " \n";
    }

    for(int i=0;i <n_w;i++){
        delete [] input.get_weights()[i];
    }
    delete [] input.get_weights();

    s = 0.0;
    for(auto i=0;i < n_h;i++){
        s += (l[i] * input.get_hidden_weights()[i]);
    }
    //std::cout << "s= " <<s << "\n";
    delete [] input.get_hidden_weights();
    _s = input.sigmoid(s);

    printf("\nOutput: (%lf) %.0lf \n\nPress enter to continue ...\n", _s, nearbyint(_s));
    if(nearbyint(_s) == 1){
        printf("CANCER DETECTED !!!\n");
    } else{
        printf("NO CANCER\n");
    }
    delete [] l;
}
