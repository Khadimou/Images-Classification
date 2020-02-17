#include "filtre.h"
#include "pgmimg.h"
#include "ppmimg.h"
#include "trainer.h"

int main(int argc,char **argv)
{
    if(argc<2){
        std::cerr << "Usage: " << argv[0] << "[ppm image is missing] " << std::endl;
        return -1;
    }
    auto img = handleppm();
    img.ppm_open(argv[1]);

    /*auto imagepgm = handlepgm();

    imagepgm.pgm_open(argv[1]);
    imagepgm.p_out = new unsigned char[imagepgm.height*imagepgm.width];*/

    std::cout << "Resolution: " << img.h*img.w << "Pixels, "<< img.h*img.w / 1000000 <<" MPixels\n";

    //imagepgm.pgm_sobel(imagepgm.px,imagepgm.p_out,imagepgm.height,imagepgm.width,100,"sobel");
    //imagepgm.pgm_apply_prewitt_filter(imagepgm.px,imagepgm.p_out,imagepgm.height,imagepgm.width,100,"prewitt");

    //imagepgm.pgm_apply_kirsch_filter(imagepgm.px,imagepgm.p_out,imagepgm.height,imagepgm.width,"kirsch");
    auto nn = train();
    nn.trainer(2500,2500,img);

    return 0;
}