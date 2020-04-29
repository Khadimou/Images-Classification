#include "filtre.h"
#include "pgmimg.h"
#include "ppmimg.h"
#include "trainer.h"
#include "test.h"
#include <stdio.h>
#include <dirent.h>
#include <mpich/mpi.h>

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
    int nproc,rank;
    std::string current_test_char = "CANCER DETECTED !!!\n";
    int bad_test_classifications = 0,total_test_classifications=0;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&nproc);

    for(i=2; i<nb_fichier;i++)
    {
        char path[512];
        snprintf(path, 512, "%s/%s", chemin, liste[i]->d_name);
        char *tum = path;
        img.ppm_open(tum);
        std::cout << "Resolution: " << img.h*img.w << "Pixels, "<< img.h*img.w / 1000000 <<" MPixels\n";
        //nn.trainer(100,100,img);
        //check.output_test(nn,100,100,img);
        check.run_test("weights",100,100,img);
        if (current_test_char != check.output_test_char(check.get_res()))
            bad_test_classifications++;

        total_test_classifications++;
    }
    //Percentage of bad test classifications
    std::cout << "bad test classifications " << bad_test_classifications << "\n";
    std::cout << "total classifications " << total_test_classifications << "\n";
    auto pbtc = (bad_test_classifications * 100) / total_test_classifications;
    std::cout << "pourcentage de mauvaises classifications " << pbtc << "%" << std::endl;

    MPI_Finalize();

    return 0;
}