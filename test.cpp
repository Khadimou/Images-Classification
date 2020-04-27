//
// Created by khadimou on 20/02/2020.
//
#include <iomanip>
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


    s = 0.0;
    for(auto i=0;i < n_h;i++){
        s += (l[i] * input.get_hidden_weights()[i]);
    }
    //std::cout << "s= " <<s << "\n";
    _s = input.sigmoid(s);

    printf("\nOutput: (%lf) %.0lf \n", _s, nearbyint(_s));
    if(nearbyint(_s) == 1){
        printf("CANCER DETECTED !!!\n");
        output_test_char("CANCER DETECTED !!!\n");
        save_weights(input,"./weights",n_h,n_w);
    } else{
        printf("NO CANCER\n");
        output_test_char("NO CANCER\n");
    }
    delete [] l;
    for(int i=0;i <n_w;i++){
        delete [] input.get_weights()[i];
    }
    delete [] input.get_weights();
    delete [] input.get_hidden_weights();
}

void test::save_weights(train &t,std::string fname,int n_h,int n_w) {
    std::ofstream file(fname.c_str(),std::ios::out | std::ios::binary | std::ios::trunc);
    if(file){
        for(auto i=0;i<n_h;i++) {
            for (auto j = 0; j < n_w; j++) {
                file << t.get_weights()[i][j] << " ";
            }
            file << "\n";
        }
        file << "\n";
        for(auto i=0;i<n_h;i++) {
            file << t.get_hidden_weights()[i] << " ";
        }
        file.close();
    }
}

std::istream& ignoreline(std::ifstream& in, std::ifstream::pos_type& pos)
{
    pos = in.tellg();
    return in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string getLastLine(std::ifstream& in) {
    std::ifstream::pos_type pos = in.tellg();

    std::ifstream::pos_type lastPos;
    while (in >> std::ws && ignoreline(in, lastPos))
        pos = lastPos;

    in.clear();
    in.seekg(pos);

    std::string line;
    std::getline(in, line);
    return line;
}

void split(const std::string& str, std::vector<float>& cont, char delim = ' ')
{
    std::stringstream ss(str);
    std::string token;
    int i =0;
    while (std::getline(ss, token, delim)) {
        cont[i] = std::stof(token);
        i++;
    }
}

/* on charge le fichier des poids du test qui a donné le résultat voulu et on teste le réseau
 * avec ces valeurs pour vérifier que l'on a les bons résultats */
void test::run_test(std::string fname,int n_w,int n_h,const ppm& img) {
    std::ifstream file_weights(fname.c_str(),std::ios::in);
    train t;
    std::string poids;
    if (file_weights)
    {
        std::vector<float> stock_poids;
        float s,_s;
        float *l = new float[n_h];
        int iter =0;
        while ( std::getline(file_weights,poids))
        {
            //std::cout << poids << "\n";
            while(iter<n_h*n_w) {
                std::vector<float> tab_poids(n_h * n_w);
                split(poids, tab_poids, ' ');
                stock_poids.push_back(tab_poids[iter]);
                std::cout << stock_poids[iter] << " ";
                iter++;
            }
            std::cout << "\n";
        }
        for(auto i=0;i<n_h;i++){
            s = 0.;

            for(auto j=0;j<n_w;j++){
                s += img.px[j] * stock_poids[j];
            }

            l[i] = t.sigmoid(s);
            //std::cout << l[i] << " \n";
        }

        s = 0.0;
        std::string hidden_weights = getLastLine(file_weights); //récupérer les hidden weights
        //std::cout << hidden_weights << " ";
        for (auto i = 0; i < n_h; i++) {
            s += (l[i] * atof(hidden_weights.c_str()));
            //std::cout << atof(hidden_weights.c_str()) << " ";
        }

        //std::cout << "s= " <<s << "\n";
        _s = t.sigmoid(s);

        //printf("\nOutput: (%lf) %.0lf \n", _s, nearbyint(_s));
        /*if(nearbyint(_s) == 1){
            printf("CANCER DETECTED !!!\n");
            output_test_char("CANCER DETECTED !!!\n");
        } else{
            printf("NO CANCER\n");
            output_test_char("NO CANCER\n");
        }*/
        file_weights.close();
    }else{
        std::cout << "Unable to open file";
    }
}

std::string test::output_test_char(std::string res) {
    result = res;
    return res;
}
