#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>

std::vector<double> ReadFile(std::string File, int mode, int name_of_ax){ //mode = 1 --> h,vx,vy; mode = 2 --> coords

    std::vector<double> coordsx;
    std::vector<double> coordsy;
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

        if(mode == 1){
            fin.close();
            return param;
        }

        while (!fin.eof()) {
            fin >> point;
            coordsx.push_back(point);

            fin >> point;
            coordsy.push_back(point);
        }
    }

    fin.close();

    if(name_of_ax == 1){
        return coordsx;
    }
    else{
        return coordsy;
    }
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

        std::vector<double> param = ReadFile(argv[1],1,0); //параметры системы
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

        X_per = ReadFile(argv[1],2,1);
        Y_per =  ReadFile(argv[1],2,2);

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