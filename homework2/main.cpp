#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>

std::vector<double> ReadFile(std::string path){

    std::vector<double> coords;
    std::vector<std::string> points;

    std::ifstream fin;
    fin.open(path);

    if (fin.is_open()){
        std::string str;

        while (!fin.eof()) {
            str = "";
            fin >> str;
            points.push_back(str);
        }
    }

    fin.close();

    for (int i; i< points.size(); i++){

        std::string b = points[i];
        double a = strtod(b.c_str(), nullptr);
        coords.push_back(a);
    }

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
std::vector<double> coords(std::vector<double> X,double vx, double vy, double h,double g,int n, std::vector<double> recX){
    std::vector<double> Y;

    for(int i = 0; i < X.size(); i++){
        double a = h + pow(-1,n)*(X[i]-recurs(recX,n))*vy/vx - pow((X[i]-recurs(recX,n)),2)*g/(2*pow(vx,2));
        Y.push_back(a);
    }
    return Y;
}



int main(int argc,char** argv) {

    std::string path = "in.txt";
    std::vector<double> ALL = ReadFile(path);

    double h = ALL[0];
    double vx = ALL[1];
    double vy = ALL[2];
    double g = 9.81;

//    std::cout << "h = " << h << " vx = " << vx << " vy = " << vy << std::endl;
    ALL.erase(ALL.begin() + 0);
    ALL.erase(ALL.begin() + 0);
    ALL.erase(ALL.begin() + 0);

    std::string way = "Right";//начальное направление движения

    int n = 0;//счетчик для рекурсии
    int n_p = 0;// Номер перегородки от которой мы отразились

    std::vector<double> Y_true;// Y координата мячика
    std::vector<double> Y_per;//Y координата перегородки
    std::vector<double> X_per;//X координата перегородки
    std::vector<double> X_rec;//X координата перегородок, от которых мячик отразися

    X_per = XorY(ALL,1);
    Y_per = XorY(ALL,2);

//    for (int i = 0; i<X_per.size();i++){
//        std::cout << "X_per= " << X_per[i] << "Y_per = " << Y_per[i] << std::endl;
//    }

    for(int i = 0; i < X_per.size(); i++){
//        std:: cout <<"coords X and Y is (" << X_per[i] << ", " << coords(X_per,vx,vy,h,g,n,X_rec)[i]<< ")" <<std::endl;
        Y_true.push_back(coords(X_per,vx,vy,h,g,n,X_rec)[i]);
    }

//Первое столкновение
    for(int i = 0; i<X_per.size(); i++){
        if(Y_true[i] < Y_per[i]){
            n_p = i;
            way = "Left";
            n++;
            X_rec.push_back(X_per[i]);
            break;
        }
    }

    if(way == "Right"){
        std::cout << "<" << X_per.size() << ">";
        return 0;
    }

//    std::cout << "n_p = " << n_p << " Y(n_p) = " << Y_true[n_p] << " way is " << way << " X_rec " << X_rec[n_p] << std::endl;

    while(true){
        if(way == "Left"){
            Y_true = coords(X_per,vx,vy,h,g,n,X_rec);
            for(int i = n_p - 1; i >= 0; i--){

                if (Y_true[i] <= Y_per[i]){
//                    std::cout << "dvgalis vpravo";
//                    std::cout << "Coords of parabola Y " << Y_true[i] << " coords of peregorodok is" << Y_per[i] <<std::endl;
                    n_p = i;
                    way = "Right";
                    n++;
                    X_rec.push_back(X_per[i]);
                    break;
                }
            }

            if(Y_true[n_p] < 0){
                std::cout << "<" << n_p+1 << ">";
                return 0;
            }

            if(way == "Left"){
                std::cout << "<" << 0 << ">";
                return 0;
            }
        }

        if(way == "Right"){
            Y_true = coords(X_per,vx,vy,h,g,n,X_rec);
            for(int i = n_p + 1 ; i < X_per.size(); i++){

                if (Y_true[i] <= Y_per[i]){
//                    std::cout << "dvgalis vpravo";
//                    std::cout << "Coords of parabola Y " << Y_true[i] << " coords of peregorodok is" << Y_per[i] <<std::endl;
                    n_p = i;
                    way = "Left";
                    n++;
                    X_rec.push_back(X_per[i]);
                    break;
                }
            }

            if(Y_true[n_p] < 0){
                std::cout << "<" << n_p << ">";
                return 0;
            }

            if(way == "Right"){
                std::cout << "<" << X_per.size() << ">";
                return 0;
            }
        }
    }
//    std::cout << "n_p = " << n_p << " Y(n_p) = " << Y_true[n_p] << " way is " << way << " X_rec " << X_rec[n_p] << std::endl;
}
