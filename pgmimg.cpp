//
// Created by khadimou on 23/01/2020.
//
#include "pgmimg.h"
#include <cmath>

void handlepgm::pgm_open(const char *fname)
{
    std::ifstream file(fname, std::ios::binary);

    if(file.fail())
    {
        std::cout << "Error file is not opened" << " ";
    }
    std::string line;
    // 1ere ligne
    getline(file, line);
    bool binary = true;
    if(line=="P5" )
    {
        binary=true;
    }
    else if(line=="P2" )
    {
        binary=false;
    }
    else
    {
        std::cout << "Bad File" << " ";
    }
    // on saut le commentaire eventuel
    getline(file, line);
    if(line[0]=='#')
    {
        getline(file, line);
    }
    // on obtient les dimensions
    std::istringstream is(line);
    is >> this->width >> this->height;
    //std::cout << "hauteur= " << width << " ";
    // la valeur max
    file >> this->maxvalue;
    //std::cout << "maxval = " << this->maxvalue << " ";
    // on lis les données
    this->px=new unsigned char [this->width*this->height];
    if (binary)
    {
//We need to read a binary PGM file
        file.read(reinterpret_cast<char *>(this->px), this->width * this->height);
    }
    else
    {
//We need to read in an ASCII file
        std::copy(std::istreambuf_iterator<char>(file),
                  std::istreambuf_iterator<char>(),
                  this->px);
    }
}

void handlepgm::save_pgm(PGMImage& img,std::string fname) {
    std::ofstream fd(fname, std::ios_base::out
                               |std::ios_base::binary
                               |std::ios_base::trunc);
    if(fd)
    {
        fd << "P5\n" << " ";
        fd << this->width << " " << this->height << "\n";
        fd << this->maxvalue << "\n";
        fd << this->px << "\n";

        fd.close();
    }

}

void handlepgm::pgm_sobel(byte *img_in, byte *img_out, unsigned long long h, unsigned long long w, float threshold,std::string fname) {
    int matrice1[9]={-1, 0, 1, -2, 0, 2, 1, 0, 1};
    int matrice2[9]={-1, -2, -1, 0, 0, 0, 1, 2, 1};
    calcul c;
    std::ofstream fd(fname, std::ios_base::out
                              |std::ios_base::binary
                              |std::ios_base::trunc);

    for(unsigned long long i=0;i<h-3;i++) {
        for (unsigned long long j = 0; j < w - 3; j++) {
            auto gx = c.convolve(&img_in[INDEX(i, j, w)], h, w, matrice1, 3, 3);
            auto gy = c.convolve(&img_in[INDEX(i, j, w)], h, w, matrice2, 3, 3);

            auto mag = sqrt((gx * gx) + (gy * gy));

            img_out[INDEX(i, j, w)] = mag;
        }
    }
    if(fd)
    {
        fd << "P5\n" << " ";
        fd << this->width << " " << this->height << "\n";
        fd << this->maxvalue << "\n";
        fd << img_out << "\n";

        for(auto i=0;i<h*w;i++) {
            fd.write(reinterpret_cast<char *>(img_out), w * h);
        }

        fd.close();
    }
}

void handlepgm::pgm_apply_prewitt_filter(byte *img_in, byte *img_out, u64 h, u64 w, float threshold,std::string fname)
{
    int gx, gy;
    int f1[9] = { 1, 0, -1, 1, 0, -1,  1,  0, -1 }; //3x3 matrix
    int f2[9] = { 1, 1,  1, 0, 0,  0, -1, -1, -1 }; //3x3 matrix
    calcul c;

    std::ofstream fd(fname, std::ios_base::out
                              |std::ios_base::binary
                              |std::ios_base::trunc);
    for (u64 i = 0; i < h - 3; i++) {
        for (u64 j = 0; j < w - 3; j++) {
            gx = c.convolve(&img_in[INDEX(i, j, w)], h, w, f1, 3, 3);
            gy = c.convolve(&img_in[INDEX(i, j, w)], h, w, f2, 3, 3);

            double mag = sqrt((gx * gx) + (gy * gy));

            img_out[INDEX(i, j, w)] = (mag > threshold) ? 255 : mag;
        }
    }
    if(fd)
    {
        fd << "P5\n" << " ";
        fd << w << " " << h << "\n";
        fd << this->maxvalue << "\n";
        fd << img_out << "\n";

        for(auto i=0;i<h*w;i++) {
            fd.write(reinterpret_cast<char *>(img_out), w * h);
        }
        fd.close();
    }
}

//Rotate the initial matrix by 45° (8 entries)
void handlepgm::pgm_apply_kirsch_filter(byte *img_in, byte *img_out, u64 h, u64 w,std::string fname) {
    int max_g;
    int g[8] = {0};
    int f[8][9] = {
            {5,  5,  5,
                    -3, 0, -3,
                    -3, -3, -3},

            {5,  5,  -3,
                    5,  0, -3,
                    -3, -3, -3},

            {5,  -3, -3,
                    5,  0, -3,
                    5,  -3, -3},

            {-3, -3, -3,
                    5,  0, -3,
                    5,  5,  -3},

            {-3, -3, -3,
                    -3, 0, -3,
                    5,  5,  5},

            {-3, -3, -3,
                    -3, 0, 5,
                    -3, 5,  5},

            {-3, -3, 5,
                    -3, 0, 5,
                    -3, -3, 5},

            {-3, 5,  5,
                    -3, 0, 5,
                    -3, -3, -3}};
    calcul c;

    for (u64 i = 0; i < h - 3; i++) {
        for (u64 j = 0; j < w - 3; j++) {
            for (u64 k = 0; k < 8; k++){
                g[k] = c.convolve(&img_in[INDEX(i, j, w)], h, w, f[k], 3, 3);
            }

            max_g = g[0];

            for (u64 k = 1; k < 8; k++) {
                max_g = std::max(max_g, g[k]);
            }

            img_out[INDEX(i, j, w)] = max_g >> 2;
        }
    }
    //
    std::ofstream fd(fname, std::ios_base::out
                            | std::ios_base::binary
                            | std::ios_base::trunc);
    if (fd) {
        fd << "P5\n" << " ";
        fd << w << " " << h << "\n";
        fd << this->maxvalue << "\n";
        fd << img_out << "\n";

        for (auto i = 0; i < h * w; i++) {
            fd.write(reinterpret_cast<char *>(img_out), w * h);
        }

        fd.close();
    }
}

