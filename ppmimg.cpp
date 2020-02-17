//
// Created by khadimou on 30/01/2020.
//
#include "ppmimg.h"
#include "pgmimg.h"

void handleppm::ppm_open(const char* fname) {

    std::ifstream fd(fname, std::ios::binary|std::ios::in);

    if(fd.fail())
    {
        std::cout << "Error file is not opened" << " ";
    }
    std::string ligne;
    // 1ere ligne
    getline(fd, ligne);
    bool binary = true;
    if(ligne=="P6" )
    {
        binary=true;
    }
    else if(ligne=="P3" )
    {
        binary=false;
    }
    else{
        std::cout << "Bad File" << " ";
    }
    // on saut le commentaire eventuel
    getline(fd, ligne);
    if(ligne[0]=='#')
    {
        getline(fd, ligne);
    }

    // on obtient les dimensions

    std::istringstream iss(ligne);

    iss >> this->w >> this->h ;
    fd >> this->t;
    this->px = new unsigned char[this->h*this->w*3];//h lines & w columns & 3 values per pixel(RGB)
    if (binary)
    {
//We need to read a binary PPM file
        fd.read(reinterpret_cast<char *>(this->px), this->w * this->h);
    }
    else
    {
//We need to read in an ASCII file
        std::copy(std::istreambuf_iterator<char>(fd),
                  std::istreambuf_iterator<char>(),
                  this->px);
    }

}

void handleppm::save_ppm(ppm& img,std::string fname) {

    std::ofstream fd(fname, std::ios_base::out
                            |std::ios_base::binary
                            |std::ios_base::trunc);
    if(fd)
    {
        fd << "P6\n" << " ";
        fd << this->w << " " << this->h << "\n";
        fd << this->t << "\n";
        fd << this->px << "\n";

        for(auto i=0;i<h*w;i++) {
            fd.write(reinterpret_cast<char *>(this->px), this->w * this->h);
        }

        fd.close();
    }
}

