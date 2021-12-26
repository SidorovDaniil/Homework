#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <typeinfo>

std::vector<double> ReadFile(std::string File){
    double x;
    std::vector<double> coords;
    std::vector<std::string> points;

    std::ifstream fin;
    fin.open(File);

    if (fin.is_open()){
//        std::string str;

        while (!fin.eof()) {
//            str = "";
//            fin >> str;
            fin >> x;
            coords.push_back(x);
//            std::cout << "X = " << typeid(x).name() << std::endl;
        }
    }

    fin.close();

//    for (int i; i< points.size(); i++){
//
//        std::string b = points[i];
//        double a = strtod(b.c_str(), nullptr);
//        coords.push_back(a);
//    }

    return coords;
}

std::vector<double> XorY(std::vector<double> coords,int name_of_axis){

    std::vector<double> axis;

    for (int i; i< coords.size()/2; i++){

        if(name_of_axis == 1){              // 1 is equal x
            axis.push_back(coords[2*i]);
        }
        else{                               // 2,3... is equal y
            axis.push_back(coords[2*i+1]);
        }
    }
    return axis;
}

double recurs(std::vector<double> X, double n){
    if (n == 0) {
        return 0;
    }
    else {
        return 2 * X[n-1] - recurs(X, n - 1);
    }
}

//Функция, возвращающая координату Y параболы в различных точках X
std::vector<double> coords(std::vector<double> X,double vx, double vy, double h,double g,double n, std::vector<double> recX){
    std::vector<double> Y;

    for(int i = 0; i < X.size(); i++){
        double a = h + (X[i]-recurs(recX,n))*vy/vx - pow((X[i]-recurs(recX,n)),2)*g/(2*pow(vx,2));
        Y.push_back(a);
    }
    return Y;
}



int main(int argc,char** argv) {

    if (argc == 2) {
//        std::cout << "1st argument: " << argv[1] << std::endl;

        std::vector<double> ALL = ReadFile(argv[1]);

        double h = ALL[0];
        double vx = ALL[1];
        double vy = ALL[2];
        double g = 9.81;

//        std::cout << "h = " << h << " vx = " << vx << " vy = " << vy << std::endl;
        ALL.erase(ALL.begin() + 0);
        ALL.erase(ALL.begin() + 0);
        ALL.erase(ALL.begin() + 0);

        double way = 1;//начальное направление движения

        double n = 0;//счетчик для рекурсии
        double n_p = 0;// Номер перегородки от которой мы отразились

        std::vector<double> Y_true;// Y координата мячика
        std::vector<double> Y_per;//Y координата перегородки
        std::vector<double> X_per;//X координата перегородки
        std::vector<double> X_rec;//X координата перегородок, от которых мячик отразися

        X_per = XorY(ALL, 1);
        Y_per = XorY(ALL, 2);

//        for (int i = 0; i<X_per.size();i++){
//            std::cout << "X_per= " << X_per[i] << "Y_per = " << Y_per[i] << std::endl;
//        }

        for (int i = 0; i < X_per.size(); i++) {
//            std:: cout <<"coords X and Y is (" << X_per[i] << ", " << coords(X_per,vx,vy,h,g,n,X_rec)[i]<< ")" <<std::endl;
            Y_true.push_back(coords(X_per, vx, vy, h, g, n, X_rec)[i]);
        }

        //Первое столкновение
        for (int i = 0; i < X_per.size(); i++) {
            if (Y_true[i] < Y_per[i]) {
                n_p = i;
                way = 0;
                n++;
                X_rec.push_back(X_per[i]);
                vx = -vx;
                break;
            }
        }

        if (way == 1) {
//            std::cout << "n_p = " << n_p << " Y(n_p) = " << Y_true[n_p] << " way is " << way << " X_rec " << X_rec[n_p] << std::endl;
            std::cout << X_per.size(); //ans
            return 0;
        }

//        std::cout << "n_p = " << n_p << " Y(n_p) = " << Y_true[n_p] << " way is " << way << " X_rec " << X_rec[n_p] << std::endl;
//        std::cout << "new vx";
//        std::cout << "new Left = 0 and rght = 1";
        while (true) {
            if (way == 0) {
                Y_true = coords(X_per, vx, vy, h, g, n, X_rec);
                for (int i = n_p - 1; i >= 0; i--) {

                    if (Y_true[i] <= Y_per[i]) {
//                        std::cout << "dvgalis vpravo";
//                        std::cout << "Coords of parabola Y " << Y_true[i] << " coords of peregorodok is" << Y_per[i] <<std::endl;
                        n_p = i;
                        way = 1;
                        n++;
                        X_rec.push_back(X_per[i]);
                        vx = -vx;
                        break;
                    }
                }

                if (Y_true[n_p] < 0) {
//                    std::cout << "n_p = " << n_p << " Y(n_p) = " << Y_true[n_p] << " way is " << way << " X_rec " << X_rec[n_p] << std::endl;
                    std::cout << n_p + 1; //ans
                    return 0;
                }

                if (way == 0) {
//                    std::cout << "n_p = " << n_p << " Y(n_p) = " << Y_true[n_p] << " way is " << way << " X_rec " << X_rec[n_p] << std::endl;
                    std::cout << 0; //ans
                    return 0;
                }
            }

            if (way == 1) {
                Y_true = coords(X_per, vx, vy, h, g, n, X_rec);
                for (int i = n_p + 1; i < X_per.size(); i++) {

                    if (Y_true[i] <= Y_per[i]) {
//                        std::cout << "dvgalis vpravo";
//                        std::cout << "Coords of parabola Y " << Y_true[i] << " coords of peregorodok is" << Y_per[i] <<std::endl;
                        n_p = i;
                        way = 0;
                        n++;
                        X_rec.push_back(X_per[i]);
                        vx = -vx;
                        break;
                    }
                }

                if (Y_true[n_p] < 0) {
//                    std::cout << "n_p = " << n_p << " Y(n_p) = " << Y_true[n_p] << " way is " << way << " X_rec " << X_rec[n_p] << std::endl;
                    std::cout << n_p; //ans
                    return 0;
                }

                if (way == 1) {
//                    std::cout << "n_p = " << n_p << " Y(n_p) = " << Y_true[n_p] << " way is " << way << " X_rec " << X_rec[n_p] << std::endl;
                    std::cout << X_per.size(); //ans
                    return 0;
                }
            }
        }

//    } else {
//        std::cerr << "No file" << std::endl;
//        return 1;
//    }
//    std::cout << "n_p = " << n_p << " Y(n_p) = " << Y_true[n_p] << " way is " << way << " X_rec " << X_rec[n_p] << std::endl;
    }
}