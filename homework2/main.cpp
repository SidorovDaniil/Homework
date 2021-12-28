#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>

std::vector<double> ReadFile(std::string File, int mode){ //mode = 1 --> h,vx,vy; mode = 2 --> coords
    std::vector<double> coords;
    std::vector<double> param;
    std::ifstream fin;
    fin.open(File);
    if (fin.is_open()){
        double point;
        double p;

        if(!fin.eof()){
            for(int i = 0; i < 3; i++){
                fin >> p;
                param.push_back(p);
            }
        }

        while (!fin.eof()) {

            if(mode == 1){
                fin.close();
                return param;
            }

            fin >> point;
            coords.push_back(point);
        }
    }
    fin.close();
    return coords;
}

std::vector<double> XorY(std::vector<double> coords,int name_of_axis){

    std::vector<double> axis;

    for (int i = 0; i< coords.size()/2; i++){
        if(name_of_axis == 1){              // 1 is equal x
            axis.push_back(coords[2*i]);
        }
        else{                               // 2,3... is equal y
            axis.push_back(coords[2*i+1]);
        }
    }
    return axis;
}
double recurs(std::vector<double> X, int n){
    if (n == 0) {
        return 0;
    }
    else {
        return 2 * X[n-1] - recurs(X, n - 1);
    }
}
//Функция, возвращающая координату Y параболы в различных точках X
std::vector<double> coords(std::vector<double> X,double vx, double vy, double h,double g,int n, std::vector<double> recX){

    std::vector<double> Y;
    double b = recurs(recX,n);

    for(int i = 0; i < X.size(); i++){
        double a = h + (X[i] - b) * vy / vx - (X[i] - b) * (X[i] - b) * g / (2 * vx * vx);
        Y.push_back(a);
    }
    return Y;
}

int main(int argc,char** argv) {

    if (argc == 2) {
//        std::cout << "1st argument: " << argv[1] << std::endl;

        std::vector<double> param = ReadFile(argv[1],1);
        std::vector<double> ALL = ReadFile(argv[1],2);

        std::vector<double> Y_true;// Y координата мячика
        std::vector<double> Y_per;//Y координата перегородки
        std::vector<double> X_per;//X координата перегородки
        std::vector<double> X_rec;//X координата перегородок, от которых мячик отразися
        
        double h = param[0];
        double vx = param[1];
        double vy = param[2];
        double g = 9.81;

        int n = 0;//счетчик для рекурсии
        int n_p = 0;// Номер перегородки от которой мы отразились

        X_per = XorY(ALL, 1);
        Y_per = XorY(ALL, 2);
        Y_true = coords(X_per, vx, vy, h, g, n, X_rec);

        //Первое столкновение
        for (int i = 0; i < X_per.size(); i++) {
            if (Y_true[i] < Y_per[i]) {
                n_p = i;
                n++;
                X_rec.push_back(X_per[i]);
                vx = -vx;
                break;
            }
        }

        if (vx > 0) {
            std::cout << X_per.size(); //ans
            return 0;
        }

        while (true) {
            if (vx < 0) {

                Y_true = coords(X_per, vx, vy, h, g, n, X_rec);

                for (int i = n_p - 1; i >= 0; i--) {
                    if (Y_true[i] <= Y_per[i]) {
                        n_p = i;
                        n++;
                        X_rec.push_back(X_per[i]);
                        vx = -vx;
                        break;
                    }
                }

                if (Y_true[n_p] < 0) {
                    std::cout << n_p + 1; //ans
                    return 0;
                }

                if (vx < 0) {
                    std::cout << 0; //ans
                    return 0;
                }
            }

            if (vx > 0) {

                Y_true = coords(X_per, vx, vy, h, g, n, X_rec);

                for (int i = n_p + 1; i < X_per.size(); i++) {
                    if (Y_true[i] <= Y_per[i]) {
                        n_p = i;
                        n++;
                        X_rec.push_back(X_per[i]);
                        vx = -vx;
                        break;
                    }
                }

                if (Y_true[n_p] < 0) {
                    std::cout << n_p; //ans
                    return 0;
                }

                if (vx > 0) {
                    std::cout << X_per.size(); //ans
                    return 0;
                }
            }
        }
    }
}