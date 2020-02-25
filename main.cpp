#include "filtre.h"
#include "pgmimg.h"
#include "ppmimg.h"
#include "trainer.h"
#include "test.h"
#include <stdio.h>
#include <dirent.h>
#include <regex.h>

int main(int argc,char **argv)
{
    if(argc<2){
        std::cerr << "Usage: " << argv[0] << "[ppm image is missing] " << std::endl;
        return -1;
    }
    auto img = handleppm();

    /*auto imagepgm = handlepgm();

    imagepgm.pgm_open(argv[1]);
    imagepgm.p_out = new unsigned char[imagepgm.height*imagepgm.width];*/

    //imagepgm.pgm_sobel(imagepgm.px,imagepgm.p_out,imagepgm.height,imagepgm.width,100,"sobel");
    //imagepgm.pgm_apply_prewitt_filter(imagepgm.px,imagepgm.p_out,imagepgm.height,imagepgm.width,100,"prewitt");

    //imagepgm.pgm_apply_kirsch_filter(imagepgm.px,imagepgm.p_out,imagepgm.height,imagepgm.width,"kirsch");
    auto nn = train();
    auto check = test();

    char * chemin = argv[1];

    struct dirent ** liste = NULL;

    int nb_fichier = scandir(chemin,&liste,NULL,alphasort);

    if( nb_fichier < 0)
    {
        perror("scandir");
        return 1;
    }

    int i;


    for(i=2; i<nb_fichier;i++)
    {
        char path[512];
        snprintf(path, 512, "%s/%s", chemin, liste[i]->d_name);
        char *tum = path;
        img.ppm_open(tum);
        std::cout << "Resolution: " << img.h*img.w << "Pixels, "<< img.h*img.w / 1000000 <<" MPixels\n";
        nn.trainer(2500,1000,img);
        check.output_test(nn,2500,1000,img);
    }

    return 0;
}